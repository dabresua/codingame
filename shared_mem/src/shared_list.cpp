#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/managed_heap_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <cstddef>

using namespace boost::interprocess;
typedef vector<int, allocator<int, managed_heap_memory::segment_manager> > 
   MyVector;

int main ()
{
  //We will create a buffer of 1000 bytes to store a list
  managed_heap_memory heap_memory(1000);

  MyVector * shared_vector = heap_memory.construct<MyVector>("MyVector")
                              (heap_memory.get_segment_manager());

  //Obtain handle, that identifies the vector in the buffer
  managed_heap_memory::handle_t vec_handle = heap_memory.get_handle_from_address(shared_vector);

  printf("vector size %ld\n", shared_vector->size());
  for (int i = 0; i < 1000; i++)
  {
    try {
      shared_vector->push_back(i);
    } catch (const bad_alloc &) {
      printf("Memory full at %d\n", i);
      break;
    }
  }
  printf("vector size %ld\n", shared_vector->size());
  
  //Destroy list
  heap_memory.destroy_ptr(shared_vector);

   return 0;
}