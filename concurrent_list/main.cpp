#include <string>
#include <thread>
#include <iostream>

#include "TConcurrentList.h"

using namespace std;

mutex m;

int main(int, char **)
{
    TListConcurrent< string > list;
    const unsigned NB_MESSAGE = 1000u;

    //Consuming thread
    thread consumer([&list, NB_MESSAGE]
    {
        auto i = 0u;
        while (i<NB_MESSAGE)  {
            auto message = list.pop_front();     //blocks until a message is in the list
            lock_guard<mutex> lck(m);            //to avoid mangling cout...
            cout << "Consumer thread:" << 2 << " " << message << endl;
            ++i;
        }
    });
    

    for (auto i = 0u; i < NB_MESSAGE; ++i){
        list.emplace_back("Message from main thread: " + to_string(i) );
    }

    this_thread::sleep_for(chrono::microseconds(500));
    std::unique_lock<std::mutex> lock{m};       //to avoid mangling cout...
    cout << "Main Thread: " << 1 << " DONE" << endl;
    lock.unlock();
    

    consumer.join();
    return 0;
}
