/*
 * Mutex-based Single-Producer Multiple-Consumer (SPMC) Ring Buffer
 *
 * Same interface as the lock-free version, but uses std::mutex +
 * std::condition_variable for thread safety.  Simpler to reason about;
 * trades peak throughput for correctness clarity.
 *
 * - push() locks, writes, notifies one waiting consumer.
 * - pop()  locks, reads,  notifies the producer (if it were waiting).
 * - Condition variables let threads sleep instead of spinning.
 */

#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <iostream>
#include <cassert>

class SPMCRingBuffer {
public:
    explicit SPMCRingBuffer(size_t capacity)
        : buf_(capacity), capacity_(capacity), head_(0), tail_(0), count_(0) {}

    // ── Single producer ──────────────────────────────────────────────
    bool push(int value) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (count_ == capacity_) return false;

        buf_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++count_;
        cv_not_empty_.notify_one();   // wake one waiting consumer
        return true;
    }

    // ── Multiple consumers ───────────────────────────────────────────
    bool pop(int& value) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (count_ == 0) return false;

        value = buf_[head_];
        head_ = (head_ + 1) % capacity_;
        --count_;
        cv_not_full_.notify_one();    // wake producer if it was waiting
        return true;
    }

    // Blocking variants (useful when you want threads to sleep
    // instead of spin-retrying)

    void push_wait(int value) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_not_full_.wait(lock, [&] { return count_ < capacity_; });

        buf_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
        ++count_;
        cv_not_empty_.notify_one();
    }

    void pop_wait(int& value) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_not_empty_.wait(lock, [&] { return count_ > 0; });

        value = buf_[head_];
        head_ = (head_ + 1) % capacity_;
        --count_;
        cv_not_full_.notify_one();
    }

    // ── Observers ────────────────────────────────────────────────────
    size_t size()  const { std::lock_guard<std::mutex> lock(mtx_); return count_; }
    bool   empty() const { return size() == 0; }
    bool   full()  const { return size() == capacity_; }

private:
    std::vector<int>        buf_;
    const size_t            capacity_;
    size_t                  head_;
    size_t                  tail_;
    size_t                  count_;

    mutable std::mutex      mtx_;
    std::condition_variable cv_not_empty_;   // consumers wait on this
    std::condition_variable cv_not_full_;    // producer waits on this
};

// ─── Multi-threaded test ─────────────────────────────────────────────
int main() {
    constexpr size_t CAPACITY      = 1024;
    constexpr int    NUM_ITEMS     = 1'000'000;
    constexpr int    NUM_CONSUMERS = 4;

    SPMCRingBuffer rb(CAPACITY);

    std::vector<long long> consumer_sums(NUM_CONSUMERS, 0);
    std::vector<int>       consumer_counts(NUM_CONSUMERS, 0);

    std::atomic<bool> done{false};

    // ── Launch consumers ──
    std::vector<std::thread> consumers;
    for (int c = 0; c < NUM_CONSUMERS; ++c) {
        consumers.emplace_back([&, c]() {
            long long sum = 0;
            int       cnt = 0;
            int       val;
            while (true) {
                if (rb.pop(val)) {
                    sum += val;
                    ++cnt;
                } else if (done.load(std::memory_order_acquire)) {
                    // Producer finished — drain remaining items.
                    while (rb.pop(val)) { sum += val; ++cnt; }
                    break;
                } else {
                    std::this_thread::yield();
                }
            }
            consumer_sums[c]   = sum;
            consumer_counts[c] = cnt;
        });
    }

    // ── Producer ──
    for (int i = 0; i < NUM_ITEMS; ++i)
        while (!rb.push(i)) { std::this_thread::yield(); }

    done.store(true, std::memory_order_release);

    for (auto& t : consumers) t.join();

    // ── Verify ──
    int       total_count = 0;
    long long total_sum   = 0;
    for (int c = 0; c < NUM_CONSUMERS; ++c) {
        total_count += consumer_counts[c];
        total_sum   += consumer_sums[c];
        std::cout << "  consumer " << c << ": " << consumer_counts[c] << " items\n";
    }

    long long expected_sum = static_cast<long long>(NUM_ITEMS - 1) * NUM_ITEMS / 2;
    std::cout << "Total items consumed: " << total_count
              << " (expected " << NUM_ITEMS << ")\n"
              << "Total sum:            " << total_sum
              << " (expected " << expected_sum << ")\n";

    assert(total_count == NUM_ITEMS);
    assert(total_sum   == expected_sum);

    std::cout << "All multi-threaded (mutex) tests passed!\n";
    return 0;
}
