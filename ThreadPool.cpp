//
// Created by tomso on 12/05/2023.
//

#include "ThreadPool.h"

std::string LocationToString(Location location)
{
    switch (location) {

        case TLV: return "Tel Aviv";

        case Jerusalem: return "Jerusalem";

        case Haifa: return "Haifa";

        default: return "cancelled";
    }
}

void ThreadPool::worker_thread()
{
    while (!done)
    {
        if (check_match)
            Match();
        Request* request;
        if (requests_queue.pop(request))
        {
            request->Execute();
        }
        else {
            std::this_thread::yield();
        }
    }
}

void notifyPasengers(Queue<Passenger*> *queue, Driver* driver)
{
    for (int i=0; i< ThreadPool::RideSize; i++)
    {
        Passenger* passenger;
        queue->pop(passenger);
        passenger->Message(driver->getAddress());
    }
}

void ThreadPool::addPassenger(Passenger* passenger)
{
    destination_queue[passenger->location1]->push(passenger);
    if ((destination_queue[passenger->location1]->size() %  RideSize) == 0)
    {
        ready_location.push(passenger->location1);
        wlock lk(check_match_mutex);

    }
}


void ThreadPool::addDriver(Driver* driver)
{
    ready_drivers.push(driver);
    wlock lk(check_match_mutex);
    if (checkPassengers()) {
        markCheck();
}
}

void ThreadPool::markCheck(){
    check_match = true;

}

void ThreadPool::Match(){
    Driver *driver;
    Location location;
    wlock lk1(match_mutex);
    wlock lk2(check_match_mutex);
    if (checkDrivers() && checkPassengers()) {
        lk2.unlock();
        ready_drivers.pop(driver);
        ready_location.pop(location);
        lk1.unlock();
        driver->Message(LocationToString(location));
        notifyPasengers(destination_queue[location], driver);
    } else{
        check_match = false;
    }
}


bool ThreadPool::checkDrivers() { return ready_drivers.size()>0;};
bool ThreadPool::checkPassengers(){return !ready_location.empty();};



ThreadPool::ThreadPool(): done(false), check_match(false)
{
    int const thread_count = std::thread::hardware_concurrency();
    for (int i=0; i<thread_count; i++)

        try {
            {
                threads.emplace_back(&ThreadPool::worker_thread, this);
            }
        }catch (...)
        {
            done = true;
            throw;
        }
}

ThreadPool* ThreadPool::getInstance()
{
    if (instance == nullptr) {
        instance = new ThreadPool();
        return instance;
    }
    else  {
        return instance;
    }
}

void ThreadPool::addRequest(Request* request)
{
    requests_queue.push(request);
}