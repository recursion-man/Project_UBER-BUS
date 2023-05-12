//
// Created by tomso on 12/05/2023.
//

#include "Request.h"
using wlock = std::unique_lock<std::shared_timed_mutex>;


std::string Request::getAddress() const
{
    return address;
}

void Request::Message() const {
    const char *char_add= address.c_str();
    int new_fd = open(char_add, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
    write(new_fd, text, sizeof(text));
}


void Driver::Message( std::string location)  {
    text = location;
    Request::Message();
}

void Driver::Execute() {
    auto uber = ThreadPool::getInstance();
    uber->addDriver(this);

}

void Passenger::Execute()
{
    auto uber = ThreadPool::getInstance();
    uber->addPassenger(this);
}
void Passenger::Message(std::string driver)
{
    text = driver;
    Request::Message();
}
