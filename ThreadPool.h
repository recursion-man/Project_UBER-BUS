//
// Created by tomso on 12/05/2023.
//

#ifndef PROJECT_UBER_THREADPOOL_H
#define PROJECT_UBER_THREADPOOL_H
#include <map>
#include "safe_queue.h"
#include <thread>
#include "Queue.h"
#include "Request.h"



class Request;
class Passenger;
class Driver;
using wlock = std::unique_lock<std::shared_timed_mutex>;
using rlock = std::shared_lock<std::shared_timed_mutex>;

enum class Location{Jerusalem, TLV, Haifa};


class ThreadPool {

public:
    void addDriver(Driver* driver);
    void addPassenger(Passenger* passenger);
    bool checkDrivers();
    bool checkPassengers();
    void markCheck();
    void Match();
    static ThreadPool* getInstance();
    void addRequest(Request* request);
    static const int RideSize = 60;

private:
    static ThreadPool* instance;
    ThreadPool();
    void worker_thread();
    static std::shared_timed_mutex match_mutex;
    static std::shared_timed_mutex check_match_mutex;
    std::atomic_bool done;
    bool check_match;
    std::vector<std::thread> threads;
    Queue<Request*> requests_queue;
    Queue<Location> ready_location;
    static Queue<Driver*> ready_drivers;
    std::map< Location, Queue<Passenger*>*> destination_queue;
};




#endif //PROJECT_UBER_THREADPOOL_H
