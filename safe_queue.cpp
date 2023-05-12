//
// Created by tomso on 11/05/2023.
//
#include <thread>
#include "safe_queue.h"
#include <algorithm>
using namespace std;

//template <typename T>
void sort_and_print(vector<int> v)
{
    sort(v.begin(), v.end());
    for (auto e:v)
        cout<<e<< " ";
    cout<<endl;
}

int main(){
    vector<vector<int>> nums = {{3,5,6,43,2,1}, {7,5,32,8,9}, {3,4,61,}};
    vector<thread> t;

    for (int i=0; i<1;i++)
    {
        t.emplace_back(sort_and_print,nums[i]);
    }
    for (int i=0; i<1;i++)
    {
        t[i].join();
    }

//    SafeQueue<int> q{};
//
//    q.push(1);
//    q.push(3);
//    q.push(7);
//    q.push(20);
//    q.push(4);
//    q.print();
//    q.pop();
//    std::cout<<std::endl;
//    q.print();


    return 1;
};