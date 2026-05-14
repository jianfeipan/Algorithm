#include <iostream>
#include <thread>
#include <chrono>

int main(){
    {
        std::thread t([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
        t.join();// without join will call std::terminate() on t
    }
    {
        std::jthread jt([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
        // no need to join, destructor will call join automatically
    }
    {
        std::jthread jt_stop([] (std::stop_token stoken) {
            std::stop_callback cb(stoken, [] {
                std::cout<< "[stop callback] stop reqeusted" << std::endl;
            });

            size_t i = 1;
            while (!stoken.stop_requested()){
                std::cout << "[jthread] looping" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            std::cout << "[jthread] stoped, exit" << std::endl;
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "[main thread] sends stop token to jthread" << std::endl;
        jt_stop.request_stop(); 
    }
    std::cout << "[main thread] jthread destructed" << std::endl;

    std::cout << "[main thread] exit" << std::endl;
    return 0;
}