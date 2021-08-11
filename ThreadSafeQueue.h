// 使用条件变量版本
#include <memory>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue();

    ThreadSafeQueue(const ThreadSafeQueue &);

    ThreadSafeQueue &operator=(const ThreadSafeQueue &) = delete;

    void push(T new_value);

    bool try_pop(T &value);

    std::shared_ptr<T> try_pop();

    void wait_and_pop(T &value);

    std::shared_ptr<T> wait_and_pop();

    bool empty() const;

};
