//
// Created by tomso on 12/05/2023.
//

#include "ThreadPool.h"

void ThreadPool::worker_thread()
{
    while (!done)
    {
        if (check_match)
            checkMatch();
        Request* task;
        if (requests_queue.pop(task))
        {
            task.execute();
        }
        else
        {

        }
    }

}