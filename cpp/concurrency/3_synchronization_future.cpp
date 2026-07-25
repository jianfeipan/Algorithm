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
template<class F>
auto then(future<long> x, F&& f) {
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

template<class T>
tuple<T> when_all(T&& left, T&& right) {
    return make_tuple(forward<T>(left), forward<T>(right);
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

    temp.then(
        [p_ = move(p)] (auto f_) {
            if(f_.has_exception()) {
                auto ex = f_.get_exception_ptr();
                p_.set_exception(ex);
                rethrow_exception(ex);
            }

            auto value = temp_.get();
            p_.set_value(value); // splited future
            return value; // current future
        }
    )
}



