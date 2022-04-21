#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

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

#define REGION_SIZE (1000)
#define REGION_NAME "MySharedMemory"

using namespace boost::interprocess;

typedef vector<int, allocator<int, managed_shared_memory::segment_manager> > 
   MyVector;

int main(int argc, char *argv[])
{

   printf("Start of process with ID %d\n", ::getpid());

   if(argc == 1){  //Parent process
      //Remove shared memory on construction and destruction
      struct shm_remove
      {
         shm_remove() { shared_memory_object::remove(REGION_NAME); }
         ~shm_remove(){ shared_memory_object::remove(REGION_NAME); }
      } remover;

      // Create a managed shared memory to build objects. This can throw!!!
      managed_shared_memory segment(create_only, REGION_NAME, REGION_SIZE);

      // Build a dynamic vector on that memory
      MyVector * shared_vector = segment.construct<MyVector>("MyVector")
                                (segment.get_segment_manager());

      printf("vector size %ld\n", shared_vector->size());
      for (int i = 0; i < 1000; i++) {
        try {
          // Vectors cannot grow indefinitely in a limited region
          shared_vector->push_back(i);
        } catch (const bad_alloc &) {
          printf("Memory full at %d\n", i);
          break;
        }
      }
      printf("vector size %ld\n", shared_vector->size());
      
      // Launch child process
      std::string s(argv[0]); s += " child ";
      if(0 != std::system(s.c_str()))
         return 1;

      // Clean all
      segment.destroy<MyVector>("MyVector");
   } else { // Child process
      // Open the managed shared memory to build objects. This can throw!!!
      managed_shared_memory segment(open_only, REGION_NAME);

      // Search for a dynamic vector on that memory. Could not find anything!!!
      std::pair<MyVector *, std::size_t> ret = segment.find<MyVector>("MyVector");
      MyVector *shared_vector = ret.first;
      
      printf("vector size %ld, %ld\n", ret.second, shared_vector->size());
      for (int i = 0; i < shared_vector->size(); i++)
        printf("%d, " ,(*shared_vector)[i]);
      printf("\n");
   }

   printf("End of process with ID %d\n", ::getpid());
   return 0;
}