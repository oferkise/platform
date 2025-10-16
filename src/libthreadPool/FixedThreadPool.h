#pragma once
#include "ThreadPool.h"
#include <memory>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace platform {

// A fixed-size thread pool implementation
class FixedThreadPool : public ThreadPool {
public:
    explicit FixedThreadPool(size_t numThreads);
    ~FixedThreadPool();

    void start() override;
    void enqueue(std::unique_ptr<Runnable> task) override;
    void shutdown() override;

private:
    void worker();

    std::vector<std::thread> m_workers;
    std::queue<std::unique_ptr<Runnable>> m_tasks;
    std::mutex m_queueMutex;
    std::condition_variable m_condition;
    bool m_stop;
};

} // namespace platform