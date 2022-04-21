/**
 * @file consumer-producer.cpp
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Compile with:
// g++ -pthread -I /usr/lib/boost_1_79_0 src/consumer-producer.cpp -o cons-prod -lrt

#include <mutex>
#include <queue>
#include <condition_variable>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

template<typename T>
class TSQueue
{
 private:
  mutable std::mutex       mut;
  std::queue<T>           data;
  std::condition_variable cond;

 public:
  TSQueue()
  {}

  void push(T value)
  {
    printf("QUEUE push\n");
    printf ("mutex %p, data %p, cond %p\n", &mut, data, &cond);
    std::lock_guard<std::mutex> lk(mut);
    printf("BRET \n");
    std::cout << value << std::endl;
    data.push(std::move(value));
    printf("BRET pushed\n");
    cond.notify_one();
  }

  void wait_and_pop(T& value)
  {
    printf("QUEUE pop1\n");
    printf ("mutex %p, data %p, cond %p\n", &mut, data, &cond);
    std::unique_lock<std::mutex> lk(mut);
    cond.wait(lk, [this]{return !data.empty();});
    printf("BRET finished waiting pop1\n");
    value = std::move(data.front());
    data.pop();
  }

  std::shared_ptr<T> wait_and_pop()
  {
    printf("QUEUE pop2\n");
    std::unique_lock<std::mutex> lk(mut);
    cond.wait(lk, [this]{return !data.empty();});
    std::shared_ptr<T> res(
      std::make_shared<T>(std::move(data.front()))
    );
    data.pop();
    return res;
  }

  bool try_pop(T& value)
  {
    printf("QUEUE pop3\n");
    std::lock_guard<std::mutex> lk(mut);
    if (data.empty())
      return false;
    value = std::move(data.front());
    data.pop();
    return true;
  }

  std::shared_ptr<T> try_pop()
  {
    printf("QUEUE pop4\n");
    std::lock_guard<std::mutex> lk(mut);
    if (data.empty())
      return std::shared_ptr<T>();
    std::shared_ptr<T> res(
      std::make_shared<T>(std::move(data.front()))
    );
    data.pop();
    return true;
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data.empty();
  }
};

template<typename T>
class Producer
{
private:
  TSQueue<T> *queue;

public:
  Producer(TSQueue<T> *queue)
  {
    this->queue = queue;
  }

  void operator()() const
  {
    using namespace std::chrono_literals;
    int i = 0;
    do {
      T val;
      printf("Going to push\n");
      queue->push(val);
      printf("New val pushed\n");
      std::this_thread::sleep_for(500ms);
    } while(++i < 10);
  }
};

static std::atomic_bool live{false};

template<typename T>
class Consumer
{
private:
  TSQueue<T> *queue;

public:
  Consumer(TSQueue<T> *queue)
  {
    this->queue = queue;
    live = true;
  }

  void operator()() const
  {
    do {
      T val;
      printf("Going to pop\n");
      queue->wait_and_pop(val);
      printf("New val popped and %s\n", live ? "living" : "diying");
    } while (live);
  }
};

// TODO
namespace shared_config {
  const size_t size = 1024; /**< Size of the shared memory area */
  const int perm = 0666;    /**< Memory permisions (read and write) */
  const key_t key = 24568;  /**< Shared memory key */

}

int main(int argc, char *argv[])
{
  using namespace boost::interprocess;

  if (argc == 1) { // Parent process
    printf("BRET init consumer\n");
    // Remove shared memory on construction and destruction
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create a shared memory object.
    shared_memory_object shm(create_only, "MySharedMemory", read_write);

    // Set size
    shm.truncate(1024);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);
    printf("PARENT region starts at %p, size %ld\n", region.get_address(), region.get_size());

    // Get address and build the class in the shared region
    char *mem = static_cast<char*>(region.get_address());

    TSQueue<int> *q = new(mem) TSQueue<int>;

    Consumer<int> cons(q);
    std::thread tcons(cons);
    //Launch child process
    std::string s(argv[0]); s += " child ";
    if(0 != std::system(s.c_str()))
        return 1;
    
    live = false; // Will work???
    printf("Pushing\n");
    //q->push(0);
    tcons.join();
  } else {
    printf("BRET init producer\n");
    // Open already created shared memory object.
    shared_memory_object shm (open_only, "MySharedMemory", read_write);

    // Map the whole shared memory in this process
    mapped_region region(shm, read_write);
    printf("CHILD region starts at %p, size %ld\n", region.get_address(), region.get_size());

    // Cast the memory given that there is a TSQueue<int> there
    TSQueue<int> *q = static_cast<TSQueue<int>*>(region.get_address());

    Producer<int> prod(q);
    std::thread tprod(prod);

    tprod.join();
    printf("Prod finished\n");
  }

  return 0;
}