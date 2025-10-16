#pragma once
#include <functional>

namespace platform {

// class representing a runnable task for the thread pool
class Runnable {
public:
    virtual void run() = 0; // pure virtual function to be implemented by derived classes
    virtual ~Runnable() {}  // virtual destructor
};

// a basic implementation of Runnable that wraps a std::function
class RunnableFunction : public Runnable {
public:
    RunnableFunction(std::function<void()> func) : m_func(func) {}
    void run() override { m_func(); }
private:
    std::function<void()> m_func;
};

}   // namespace platform