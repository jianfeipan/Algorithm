# The Big Three in Multi-threading

The "big three" concurrency problems

---

## 1. Atomicity (avoid Data Race)

An operation is **atomic** if it appears to happen indivisibly — no other thread can observe a partial state.

**Problem:** `x++` is *not* atomic. It compiles to load → add → store. Two threads can interleave and lose an update:

```cpp
int x = 0;                    // shared
// Thread A            Thread B
r1 = x;   // 0
                       r2 = x;   // 0
r1 = r1+1;             r2 = r2+1;
x = r1;   // 1
                       x = r2;   // 1   ← one increment lost
```

**Fix:** atomic RMW or a lock.
```cpp
std::atomic<int> x{0};
x.fetch_add(1, std::memory_order_relaxed);   // single atomic step
```

---

## 2. Visibility (avoid stale reads)

当一个线程修改了共享变量的值，其他线程能否“立即”看到这个修改
禁止编译器乱优化：使用 std::atomic 变量时，编译器被禁止将其长期缓存在寄存器中
硬件层面的缓存一致性（Cache Coherence）：std::atomic 的底层操作会触发 CPU 的缓存一致性协议,硬件会强制让其他核心中对应的缓存行失效（Invalidate）
RFO: Read For Ownership, 当一个核心想要写某个缓存行时，它会向其他核心发送 RFO 请求，要求它们失效该缓存行，从而获得对该缓存行的独占访问权。
    1. Broadcast Invalidation to all cores that have that value's cache line
    2. wait for all cores to acknowledge the invalidation
    3. write the new value


---

## 3. Ordering (memory barrier) 


**Problem:** classic publish pattern without ordering:
```cpp
int data;
std::atomic<bool> ready{false};

// producer
data = 42;
ready.store(true, std::memory_order_relaxed);   // ❌

// consumer
while (!ready.load(std::memory_order_relaxed)) {}
assert(data == 42);   // may fire! store to data can be reordered after ready
```

**Fix:** release/acquire pair establishes a happens-before edge:
```cpp
data = 42;
ready.store(true, std::memory_order_release);   // ✅

while (!ready.load(std::memory_order_acquire)) {}
assert(data == 42);   // guaranteed
```

Memory-order menu (weakest → strongest): `relaxed` < `consume` (deprecated in practice) < `acquire`/`release` < `acq_rel` < `seq_cst`.

### 86 vs ARM
- Diff: how the CPU hardware handles memory reads (loads) and writes (stores).
 - x86: strongly-ordered architecture
  - Loads are not reordered with other loads.
  - Stores are not reordered with other stores.
  - Stores are not reordered with prior loads.
  - The **only reordering** allowed: A store followed by a load to a different memory location can be   
  - reordered (due to local CPU store buffers).
 - ARM: Weak Ordering: To maximize power efficiency and performance, the CPU pipeline is allowed to aggressively reorder almost any memory operation
  - Loads can pass loads.
  - Stores can pass stores.
  - Loads can pass stores.

## Rules of thumb

1. **Default:** `std::mutex` + plain variables. Correct by construction.
2. **Counters / flags:** `std::atomic<T>` with `relaxed` if you don't publish other data through it.
3. **Publishing data through a flag:** `release` on the store, `acquire` on the load.
4. **Multi-variable invariants across threads without locks:** use `seq_cst`, or redesign — you probably want a lock.
5. **Never** reason about "the compiler probably won't reorder this" — it will.

See related files: memory_model.cpp, atomic_cas.cpp, and your current memory_order.cpp.



