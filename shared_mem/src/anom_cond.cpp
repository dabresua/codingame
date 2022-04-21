#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstdio>
#include <cstring>

struct trace_queue
{
   enum { LineSize = 100 };

   trace_queue()
      :  message_in(false)
   {}

   //Mutex to protect access to the queue
   boost::interprocess::interprocess_mutex      mutex;

   //Condition to wait when the queue is empty
   boost::interprocess::interprocess_condition  cond_empty;

   //Condition to wait when the queue is full
   boost::interprocess::interprocess_condition  cond_full;

   //Items to fill
   char   items[LineSize];

   //Is there any message
   bool message_in;
};

using namespace boost::interprocess;

int main (int argc, char *argv[])
{
  printf("Start of process with ID %d\n", ::getpid());
  if(argc == 1) {  //Parent process
    //Erase previous shared memory and schedule erasure on exit
    struct shm_remove
    {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    //Create a shared memory object.
    shared_memory_object shm
      (create_only, "MySharedMemory", read_write);
    BOOST_TRY{
      //Set size
      shm.truncate(sizeof(trace_queue));

      //Map the whole shared memory in this process
      mapped_region region(shm, read_write);

      //Get the address of the mapped region
      void * addr = region.get_address();

      //Construct the shared structure in memory
      trace_queue * data = new (addr) trace_queue;

      const int NumMsg = 100;

      for(int i = 0; i < NumMsg; ++i){
        scoped_lock<interprocess_mutex> lock(data->mutex);
        if(data->message_in){
          data->cond_full.wait(lock);
        }
        if(i == (NumMsg-1))
          std::sprintf(data->items, "%s", "last message");
        else
          std::sprintf(data->items, "%s_%d", "my_trace", i);

        //Notify to the other process that there is a message
        printf("Notifiying the other\n");
        data->cond_empty.notify_one();

        //Mark message buffer as full
        data->message_in = true;
      }
    }
    BOOST_CATCH(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
    } BOOST_CATCH_END
  } else {
    //Create a shared memory object.
    shared_memory_object shm(open_only, "MySharedMemory", read_write);

    BOOST_TRY{
      //Map the whole shared memory in this process
      mapped_region region(shm, read_write);

      //Get the address of the mapped region
      void * addr = region.get_address();

      //Obtain a pointer to the shared structure
      trace_queue * data = static_cast<trace_queue*>(addr);

      //Print messages until the other process marks the end
      bool end_loop = false;
      do{
        scoped_lock<interprocess_mutex> lock(data->mutex);
        if(!data->message_in){
          data->cond_empty.wait(lock);
        }
        if(std::strcmp(data->items, "last message") == 0){
          end_loop = true;
        }
        else{
          //Print the message
          std::cout << data->items << std::endl;
          //Notify the other process that the buffer is empty
          data->message_in = false;
          data->cond_full.notify_one();
        }
      } while(!end_loop);
    }
    BOOST_CATCH(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
    } BOOST_CATCH_END
  }

  printf("End of process with ID %d\n", ::getpid());
  return 0;
}