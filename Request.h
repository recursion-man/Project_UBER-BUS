//
// Created by tomso on 12/05/2023.
//

#ifndef UBER_DE_REQUEST_H
#define UBER_DE_REQUEST_H
#include <string>
#include "Queue.h"
#include "ThreadPool.h"


class Request {
protected:
    std::string address;
    std::string text;
public:
    Request(char * address_path);
    virtual void Execute() = 0;
    std::string getAddress() const;
    void Message() const;

};

class Driver :public Request
{
public:
    Driver(char * address_path): Request(address_path){}
    void Execute() override;
    void Message(std::string);

};


class Passenger :public Request {

public:
    Passenger(char * address_path): Request(address_path){};
    Location location1;
    std::string location;
    std::string text;
    void Execute() override;
    void Message(std::string);

};

#endif //UBER_DE_REQUEST_H
