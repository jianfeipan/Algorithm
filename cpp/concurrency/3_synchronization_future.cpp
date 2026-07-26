#include <future>
using namespace std;
/*
NDC London 2017 Sean Parent

No Raw synchronization Primitives
*/

future<long> x = async([] { return fibonacci<long>(1000); });

count << x.get() <<endl; // wait for result, then consume

/*
future:
    blocking on future.get() (wait, wait_for...) problems:
        1. possible deadlock -> not safe
        2. any subsequence no-dependent calculations are blocked
    -> Tip: DON'T call future.get, wait .. premitives  on a same queue.
*/

// -> we need continuation: future.then() 
future<long> x = async([] { return fibonacci<long>(1000); });

future<void> y = x.then([](future<long> f) { count << f.get(); });
//....
y.wait(); // wait for the continuation to finish

// C++ solutions

// with std::async
template<class T, class F>
auto then(future<T> x, F&& f) {
    return async(
        [fut = move(x), f = forward<F>(f)] mutable {
            return f(fut.get());
        }
    );
}

future<long> x = async([] { return fibonacci<long>(1000); });
auto y = then(x, [](long v) { return v*2;});

// C++ 20 coroutines
task<int>  compute() {
    int v =co_wait async_fibonacci(10000);
    co_return v * 2;
}

// C++ 23 sender/ reciever
namespace ex = std::exception;

auto work = ex::just(10000)
          | ex::then([](long x) {return fibonacci(x); })
          | ex::then([](long y) {return y*2; });

ex::sync_wait(move(work));

/*
future VS callback
    callback (completion handler) : async(task, callback)
        bad: they must be known prior to the call
        good: no need to synchronize between invoking and setting
    future: futrue f = async(task); f.ger()
        bad: requires synchronization between invoking ans setting, which is source of bugs
        good: alows setting the continuation after sending the call flights,simpler to compose.
*/


// besides then(), we also wish joins

/*
joins: 
    bad thinking: I have two tasks, I got onr, will wait for the second
        task1 -> future 1 -> result 1 \
        task2 -> future 2 -> result 2 - -> 
        main                         wait |-> do something

    good thinking: I have two tasks, I continute doingsomething, when two res are there, triggers some thing.
        task1 -> future 1 -> result 1 \
        task2 -> future 2 -> result 2 - >
        main | doing things ........     async do something
*/

future<long> x = async([] { return fibonacci<long>(1000); });
future<long> y = async([] { return fibonacci<long>(1000); });

auto done = when_all(move(x), move(y)).then([](auto f1, auto f2) {
    cout << f1.get() * f2.get();
});

done.wait(); // wait it somewhere but before that, other things can be done.

template<class T1, class T2>
future<tuple<T1, T2>> 
when_all(future<T1> t1, future<T2> t2){// sink, should call when_all(move(t))
    struct state {
        atomic<unsigned> remaining{2};
        promise<tuple<T1, T2>> p;
        tuple<T1, T2> val;
        // handle exception
        atomic<bool> has_exception{false};
        exception_ptr first_ex;

    };

    auto s = make_shared<state>();
    auto joined_fut = s->p.get_future();
    


    auto recieve = [s] (auto set_val) {// flexible input of set_val
        return [s, set_val](auto f) mutable { // f could be T 1 or T2
            try {
                set_val(s->val, f.get()); // set to val
            } catch(...) {
                bool excepted = false;
                if (s->has_exception.compare_exchange_strong(expected, true, memory_order_acq_rel)) {
                    s->first_ex = current_exception();
                }
            }

            if (s->remaining.fetch_sub(1, memory_order_acq_rel) == 1) { 
                // we need acq_rel to make a memory barrier to make "set to val" visible by "move val to promise" 
                
                if (s->has_exception.load(memory_order_acquire)) {
                    s->p.set_exception(s->first_ex);
                } else {
                    s->p.set_value(move(s->val)); // move val to promise
                }
            }
        };
    };

    move(t1).then(recieve([](auto& tup, T1 v){ get<0>(tup) = move(v); }));
    move(t2).then(recieve([](auto& tup, T2 v){ get<1>(tup) = move(v); }));
    
    return joined_fut;
}


// apart join, we also wich split, to consume one result to different branches
future<long> x = async([] { return fibonacci<long>(1000); });

auto x2 = split(x);
auto y1 = x.then([]  (future<long> f) {return f.get() * 20; });
auto y2 = x2.then([] (future<long> f) {return f.get() * 200; });

// split
template<typename T>
future<T> split(future<T>& f) {
    auto temp = move(f);

    promise<T> p;
    f = p.get_future(); // replace the original future by a new one bind to the promise

    return temp.then(   // split will return a future with the original.get() as value.
        [p_ = move(p)] (auto f_) {
            if(f_.has_exception()) {
                auto ex = f_.get_exception_ptr();
                p_.set_exception(ex);
                rethrow_exception(ex);
            }

            auto value = temp_.get();
            p_.set_value(value); // "duplicate" the value to the promise
            return value;
        }
    )
}




