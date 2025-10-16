#include "gtest/gtest.h"
#include "FixedThreadPool.h"
#include <iostream>


TEST(FixedThreadPoolTest, DefaultConstructor) {
    platform::FixedThreadPool obj(6);
}

TEST(FixedThreadPoolTest, StartAndShutdown) {
    platform::FixedThreadPool pool(4);
    pool.start();
    pool.shutdown();
}

class IncrementTask : public platform::Runnable {
public:
    IncrementTask(std::atomic<int>& counter) : m_counter(counter) {}
    void run() override {
        m_counter++;
    }
private:
    std::atomic<int>& m_counter;
};

TEST(FixedThreadPoolTest, EnqueueTasks) {
    platform::FixedThreadPool pool(3);
    pool.start();

    std::atomic<int> counter{0};
    const int numTasks = 10;

    for (int i = 0; i < numTasks; ++i) {
        pool.enqueue(std::make_unique<IncrementTask>(counter));
    }

    pool.shutdown();
    EXPECT_EQ(counter.load(), numTasks);
}
