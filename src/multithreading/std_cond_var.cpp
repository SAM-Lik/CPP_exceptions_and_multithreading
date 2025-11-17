#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

// Потокобезопасная очередь
class ThreadSafeQueue {
    std::queue<int> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    size_t _size;
    std::condition_variable condition_s;
    //TODO:: добавить ограничение на размер очереди
public:

    ThreadSafeQueue(size_t size): _size(size) { };
    //TODO:: добавить конструктор с инициализацией размера очереди

    void push(int item) {
        //TODO:: метод должен ожидать, если в очереди не осталось места
        // аналогично как pop в случае пустой очереди
        // std::cout<<"Try push elem"<<std::endl;
        std::unique_lock<std::mutex> lock_s(mutex_);
        condition_s.wait(lock_s, [this] { return (_size > queue_.size()); });
        {
        // std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condition_.notify_one();
        }
        // std::cout<<"Push elem ready"<<std::endl;
    }

    int pop() {
        // std::cout<<"Try pop elem"<<std::endl;
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });
        int result = queue_.front();
        queue_.pop();
        condition_s.notify_one();
        // std::cout<<"Pop elem ready"<<std::endl;
        return result;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }
};

void prod(ThreadSafeQueue *q)
{
        for (int i = 0; i < 10; ++i) {
            q->push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
}

void cons(ThreadSafeQueue *q)
{
        for (int i = 0; i < 10; ++i) {
            int value = q->pop();
            std::cout << "Consumed: " << value << std::endl;
        }
}
int main() {
//    ThreadSafeQueue q;
    ThreadSafeQueue q(5);

    //TODO:: добавить несколько потоков производителей и потребителей

    // std::thread producer([&q]{
    //     for (int i = 0; i < 10; ++i) {
    //         q.push(i);
    //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //     }
    // });
    // std::thread consumer([&q]{
    //     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     for (int i = 0; i < 10; ++i) {
    //         int value = q.pop();
    //         std::cout << "Consumed: " << value << std::endl;
    //     }
    // });

    // producer.join();
    // consumer.join();
 
    
    return 0;
}
