#include "FixedThreadPool.h"
#include "Runnable.h"
#include <iostream> 
#include <memory>

namespace platform {

FixedThreadPool::FixedThreadPool(size_t numThreads) : m_stop(false) 
{
    m_workers.reserve(numThreads);
}

FixedThreadPool::~FixedThreadPool() 
{
    shutdown();
}

void FixedThreadPool::start() 
{
    for (size_t i = 0; i < m_workers.capacity(); ++i) {
        m_workers.emplace_back(&FixedThreadPool::worker, this);
    }
}

void FixedThreadPool::enqueue(std::unique_ptr<Runnable> task) 
{
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        if (m_stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        m_tasks.push(std::move(task));
    }
    m_condition.notify_one();
}

void FixedThreadPool::shutdown() 
{
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_stop = true;
    }
    m_condition.notify_all();
    for (std::thread &worker : m_workers) 
    {
        if (worker.joinable()) {
            worker.join();
        }
    }
    // Clean up remaining tasks
    while (!m_tasks.empty()) 
    {
        m_tasks.pop();
    }
}

void FixedThreadPool::worker() {
    while (true) 
    {
        std::unique_ptr<Runnable> task;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });
            if (m_stop && m_tasks.empty()) 
            {
                return;
            }
            task = std::move(m_tasks.front());
            m_tasks.pop();
        }
        try {
            task->run();
        } catch (const std::exception& e) {
            std::cerr << "Exception in thread pool task: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception in thread pool task" << std::endl;
        }
    }
}

} // namespace platform
