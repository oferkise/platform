#pragma once
#include "Runnable.h"
#include <memory>

namespace platform {

// A thread pool interface
class ThreadPool {
public:
    /**     
     * Starts the thread pool and initializes worker threads.
     */
    virtual void start() = 0;
    /**
     * Enqueues a task to be executed by the thread pool.
     * @param task A unique_ptr to a Runnable task. The thread pool takes ownership of the task and will delete it after execution.
     */
    virtual void enqueue(std::unique_ptr<Runnable> task) = 0;
    /**
     * Shuts down the thread pool and joins all worker threads.
     * Ensures that all tasks are completed before shutdown. New tasks will not be accepted after this call.
     */
    virtual void shutdown() = 0;
};

}   // namespace platform