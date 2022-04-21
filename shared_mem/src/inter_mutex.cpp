#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <thread>
#include <chrono>

typedef struct data_t {
  //Mutex to protect access to the queue
  boost::interprocess::interprocess_mutex mutex;
  int other_data;
  bool owner;
} data_t;

using namespace boost::interprocess;

#define BOOL_PRM(_b) ((_b) ? "true" : "false")

void run(data_t *data, bool own, int times)
{
  using namespace std::chrono_literals;
  while (times > 0) {
    scoped_lock<interprocess_mutex> lock(data->mutex);
    printf("Owner %s, own %s\n", BOOL_PRM(data->owner), BOOL_PRM(own));
    if (data->owner != own) {
      std::this_thread::sleep_for(50ms);
      continue;
    }
    data->other_data++;
    data->owner = !own;
    times--;
    printf("Allowed %s, owner %s, times %d\n", BOOL_PRM(own), BOOL_PRM(data->owner), times);
    std::this_thread::sleep_for(500ms);
  }
}

int main(int argc, char *argv[])
{
  printf("Start of process with ID %d\n", ::getpid());
  if(argc == 1){  //Parent process
    struct shm_remove
    {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    shared_memory_object shm(create_only, "MySharedMemory", read_write);
    shm.truncate(sizeof(data_t));
    mapped_region region(shm, read_write);
    void * addr = region.get_address();
    data_t *data = new(addr) data_t;

    printf("Prev A %d, %s\n", data->other_data, BOOL_PRM(data->owner));

    {
      scoped_lock<interprocess_mutex> lock(data->mutex);
      data->other_data = 0;
      data->owner = true;
    }
    printf("Write A %d, %s\n", data->other_data, BOOL_PRM(data->owner));

    printf("Launching thread A\n");
    run(data, true, 10);
  } else {
    struct shm_remove
    {
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    shared_memory_object shm(open_only, "MySharedMemory", read_write);
    mapped_region region(shm, read_write);
    void * addr = region.get_address();
    data_t *data = static_cast<data_t *>(addr);

     printf("Status B %d, %s\n", data->other_data, BOOL_PRM(data->owner));

    printf("Launching thread B\n");
    run(data, false, 10);
  }

  printf("End of process with ID %d\n", ::getpid());
  return 0;
}