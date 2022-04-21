#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

/**
 * @brief test for using boost library shared_memory_object
 *        Uses a memory region to share info between processes
 *        Compile with:
 *        @code {.bash}
 *            g++ -I /usr/lib/boost_1_79_0 src/main.cpp -o main -lrt
 *        @endcode
 *        @code {.powershell}
 *            g++ -I C:\Users\vagrant\boost_1_79_0\ .\src\main.cpp -o main
 *        @endcode
 * 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

#define REGION_SIZE (4098)
#define REGION_NAME "MySharedMemory"
#define AUX_REG_SIZE (512)
#define AUX_REG_NAME "AuxiliaryRegion"
#define QUEUE_NAME "MyQueue"

using namespace boost::interprocess;

typedef deque<int, allocator<int, managed_shared_memory::segment_manager> > 
   MyQueue;

class SharedClass {
private:
  MyQueue * shared_queue;
  managed_shared_memory segment;
  shared_memory_object shm;
  struct sync_data_t {
    interprocess_mutex mutex;
    int pepe;
  } * sync_data;

public:
  SharedClass();

  ~SharedClass();

  bool try_push(int i);

  bool try_pop(int &val);

  size_t size() const;
};

SharedClass::SharedClass()
{
  // Create a managed shared memory to build objects. This can throw!!!
  segment = managed_shared_memory(open_or_create, REGION_NAME, REGION_SIZE);
  printf("Segment %p\n", &segment);
  std::pair<MyQueue *, std::size_t> rq = segment.find<MyQueue>(QUEUE_NAME);
  if (!rq.first) {
    printf("Creating queue ---\n");
    shared_queue = segment.construct<MyQueue>(QUEUE_NAME)
                  (segment.get_segment_manager());
  } else {
    shared_queue = rq.first;
    printf("Found queue %ld ---\n", rq.second);
  }

  shm = shared_memory_object(open_or_create, AUX_REG_NAME, read_write);
  shm.truncate(sizeof(sync_data_t));
  mapped_region region(shm, read_write);
  void *addr = region.get_address();
  printf("Address of new region %p\n", addr);
  sync_data = new(addr) sync_data_t;

  printf("Queue at %p, sync at %p\n", shared_queue, sync_data);
}

SharedClass::~SharedClass()
{
  // Clean all
  segment.destroy<MyQueue>("MyQueue");
}

bool SharedClass::try_push(int val)
{
  printf("Pushing before %ld\n", shared_queue->size());
  printf("Queue at %p, sync at %p\n", shared_queue, sync_data);
  scoped_lock<interprocess_mutex> lock(sync_data->mutex);
  try {
    // queues cannot grow indefinitely in a limited region
    shared_queue->push_back(std::move(val));
  } catch (const bad_alloc &) {
    return false;
  }
  printf("Pushing after  %ld\n", shared_queue->size());
  // Notify one
  return true;
}

bool SharedClass::try_pop(int &val)
{
  if (shared_queue->empty())
    return false;
  val = shared_queue->front();
  shared_queue->pop_front();
  return val;
}

size_t SharedClass::size() const
{
  return shared_queue->size();
}

int main(int argc, char *argv[])
{

   printf("Start of process with ID %d\n", ::getpid());

   if(argc == 1){  //Parent process
      struct shm_remove
      {
         shm_remove() { shared_memory_object::remove(REGION_NAME);
                        shared_memory_object::remove(AUX_REG_NAME); }
         ~shm_remove(){ shared_memory_object::remove(REGION_NAME);
                        shared_memory_object::remove(AUX_REG_NAME); }
      } remover;

      // Build a dynamic vector on shared memory
      SharedClass sc;

      printf("deque size %ld\n", sc.size());
      int i = 0;
      while(sc.try_push(i++));
      printf("deque size %ld\n", sc.size());
      
      // Launch child process
      std::string s(argv[0]); s += " child ";
      if(0 != std::system(s.c_str()))
         return 1;

      printf("deque size %ld\n", sc.size());
   } else { // Child process
      // Search for a dynamic deque on that memory. Could not find anything!!!
      SharedClass sc;
      
      printf("deque size %ld\n", sc.size());
      int value;
      while(sc.try_pop(value))
        printf("%d, ", value);
      printf("\n");
   }

   printf("End of process with ID %d\n", ::getpid());
   return 0;
}