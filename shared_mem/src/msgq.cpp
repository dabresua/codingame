#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace boost::interprocess;
using namespace std::chrono_literals;

#define MSG_SIZE 80
#define END_MSG "FINISH"

typedef char message_t[MSG_SIZE];

int main (int argc, char *argv[])
{
  printf("Start of process with ID %d\n", ::getpid());
  if(argc == 1) {  //Parent process
    BOOST_TRY{
      //Erase previous message queue
      message_queue::remove("message_queue");

      //Create a message_queue.
      message_queue mq(create_only, "message_queue", 100, sizeof(message_t));

      //Send 100 numbers
      message_t msg;
      for(int i = 0; i < 100; ++i) {
        int n = snprintf(msg, MSG_SIZE, "Prueba 123 %d", i);
        if (n < 1 || n > MSG_SIZE) {
          printf("ERROR FATAL\n");
          return 1;
        }
        mq.send(msg, sizeof(msg), i%2);
      }

      std::this_thread::sleep_for(4000ms);
      int n = snprintf(msg, MSG_SIZE, END_MSG);
      if (n < 1 || n > MSG_SIZE) {
        printf("ERROR FATAL\n");
        return 1;
      }
      mq.send(msg, sizeof(msg), 0);
    }
    BOOST_CATCH(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
    } BOOST_CATCH_END
  } else {
    BOOST_TRY{
      //Open a message queue.
      message_queue mq(open_only, "message_queue");

      unsigned int priority;
      message_queue::size_type recvd_size;

      message_t msg;
      do {
        mq.receive(msg, sizeof(msg), recvd_size, priority);
        printf("Received: %s\n", msg);
      } while (memcmp(msg, END_MSG, sizeof(END_MSG)) != 0);
    }
    BOOST_CATCH(interprocess_exception &ex){
      message_queue::remove("message_queue");
      std::cout << ex.what() << std::endl;
      return 1;
    } BOOST_CATCH_END
    message_queue::remove("message_queue");
  }

  printf("End of process with ID %d\n", ::getpid());
  return 0;
}