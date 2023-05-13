//
// Created by tomso on 12/05/2023.
//

#ifndef UBER_DE_QUEUE_H
#define UBER_DE_QUEUE_H

#include <queue>
#include <shared_mutex>

template <typename T>
class Queue : protected std::queue<T> {
public:
    using wlock = std::unique_lock<std::shared_timed_mutex>;
    using rlock = std::shared_lock<std::shared_timed_mutex>;

public:
    Queue() = default;
    ~Queue() {
        clear();
    }
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;

public:
    bool empty() const {
        rlock lock(mtx_);
        return std::queue<T>::empty();
    }

    size_t size() const {
        rlock lock(mtx_);
        return std::queue<T>::size();
    }

public:
    void clear() {
        wlock lock(mtx_);
        while (!std::queue<T>::empty()) {
            std::queue<T>::pop();
        }
    }

    int push(const T& obj) {
        wlock lock(mtx_);
        std::queue<T>::push(obj);
        return std::queue<T>::size();
    }

    bool pop(T& holder) {
        wlock lock(mtx_);
        if (std::queue<T>::empty()) {
            return false;
        } else {
            holder = std::move(std::queue<T>::front());
            std::queue<T>::pop();
            return true;
        }
    }

private:
    mutable std::shared_timed_mutex mtx_;
};


#endif //UBER_DE_QUEUE_H
