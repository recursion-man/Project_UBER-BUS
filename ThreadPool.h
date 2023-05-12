//
// Created by tomso on 12/05/2023.
//

#ifndef PROJECT_UBER_THREADPOOL_H
#define PROJECT_UBER_THREADPOOL_H
#include <map>
#include "safe_queue.h"
#include <thread>
enum Location{Jerusalem, TLV, Haifa};
class ThreadPool {
    std::atomic_bool done;
    std::atomic_bool check_match;
    std::vector<std::thread> threads;
    SafeQueue<Request*> requests_queue;
    SafeQueue<PassengerRequest> passenger_requests_queue;
    SafeQueue<DriverRequest> driver_requests_queue;
    std::queue<Driver> ready_drivers;
    std::map< Location, std::queue<Passenger>> destination_queue;
    void worker_thread(){

    }



}




#endif //PROJECT_UBER_THREADPOOL_H
