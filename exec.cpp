#include <iostream>
#include <thread>
#include <sstream>
#include <exception>
#include <unistd.h>
#include <chrono>
#include <vector>
// std::ostream &operator<<(std::ostream &os, const thread obj){

// }

void func(){
    std::cout << "\nRUNNING BY THREAD" << "[ " 
    << std::this_thread::get_id() << " ]"
    << std::endl;
}

int main(){
    
    std::cout << "START THREAD" << std::endl;
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << cores << std::endl;

    try{
        int n;
        std::cin >> n;
        std::vector<std::thread> threads;
        for (int i = 0; i < n; ++i) {
            threads.emplace_back(func);
        }
        for (auto& t : threads) {
            t.join();
        }
    }
    catch(std::system_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "FINISH THREAD" << std::endl;
    
    return 0;
}