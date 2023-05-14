//
// Created by tomso on 11/05/2023.
//

#ifndef PROJECT_UBER_SAFE_QUEUE_H
#define PROJECT_UBER_SAFE_QUEUE_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>

template <typename T>
class Node{
public:
    std::atomic<Node<T>*> * m_next;
    T m_data;
    Node(const T& data) : m_data(data), m_next(nullptr){}
    Node():m_data(), m_next(){};
};

// thread-safe queue
template <typename T>
class SafeQueue{
    std::atomic<Node<T>*> m_head;
    std::atomic<Node<T>*> m_tail;
    std::atomic<Node<T>*> m_tail_next;
    Node<T>* null;
    std::atomic_flag not_empty;
public:
    SafeQueue() : m_head(new Node<T>{}), m_tail(m_head.load()), m_tail_next(new Node<T>{}),not_empty(false), null(new Node<T>(9)){}
//    {
////        m_tail_next.store(null);
////        m_tail.load()->m_next=m_tail_next.load();
////        m_head.load()->m_next=m_tail_next.load();
//
//
//    };
   void push(const T& data) {
        Node<T> *new_node = new Node<T>(data);
        while (!(std::atomic_compare_exchange_strong((m_tail.load()->m_next), &null, &new_node))){};

//
//        // if the queue is empty
//        if (m_head.load() == m_tail.load()) {
//            //std::cout << "hh";
//            bool first = !not_empty.test_and_set();
//
//            // if not the first thread in an empty queue
//            if (!first) {
//                while (not_empty.test_and_set());
//            }
//
//                // if the first thread in an empty queue
//            else {
//               m_tail.store(new_node);
//               m_tail.load()->m_next = m_tail_next.load();
//               m_head.load()->m_next=m_tail.load();
//               not_empty.clear();
//                return;
//            }
//        }
        while (!(std::atomic_compare_exchange_strong((m_tail.load()->m_next), &null, &new_node))){};

//        while (!(std::atomic_compare_exchange_strong(&m_tail_next, &null, new_node))){};
//           m_tail.load()->m_next=new_node;
//           m_tail.store(new_node);
//           m_tail.load()->m_next=null;
//           m_tail_next.store(null);
    }

    T  pop()
    {
        if (m_head.load() == m_tail.load()) { return m_head.load()->m_data; };

            Node<T>* expected_head, *expected_next;
        do {
            expected_head = m_head.load();
            expected_next = expected_head->m_next;
        }
        while (!(std::atomic_compare_exchange_strong(&m_head, &expected_head, expected_next)));
        return expected_head->m_data;
    }

    void print (){
        auto i = m_head.load()->m_next;
        while (i != nullptr){
            std::cout << i->m_data<<std::endl;
            i = i->m_next;
        }}

};



#endif //PROJECT_UBER_SAFE_QUEUE_H
