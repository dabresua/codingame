#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <sstream>
#include <queue>

using namespace boost::interprocess;

#define MSG_SIZE  1024
#define MSG_NUM   2
#define END_MSG   "FINISH"
#define STOP_MSG  "STOP"
#define START_MSG "START"

/*
Compile in linux using:
g++ -pthread -I /usr/lib/boost_1_79_0 src/shared_chat.cpp -o shared_chat -lrt

Compile in windows using:
g++ -pthread -I C:\Users\vagrant\boost_1_79_0\ .\src\shared_chat.cpp -o shared_chat
*/

typedef char message_t[MSG_SIZE];

class Chat
{
private:
  bool owner:1;
  std::string qname;
  std::queue<std::string> msg_queue;

public:
  boost::scoped_ptr<message_queue> mq;

  Chat(bool owner, std::string name) : msg_queue()
  {
    this->owner = owner;
    qname = name;
    if (owner) {
      //Erase previous message queue
      message_queue::remove(qname.c_str());

      //Create a message_queue.
      mq.reset(new message_queue(create_only, qname.c_str(), MSG_NUM, sizeof(message_t)));
    } else {
      //Open a message queue.
      mq.reset(new message_queue(open_only, qname.c_str()));
    }
  }

public:
  void send(std::string str)
  {
    msg_queue.push(str);
    bool sent = true;
    while (sent && msg_queue.size()) {
      std::string one_msg = msg_queue.front();
      message_t msg;
      snprintf(msg, one_msg.size() + 1 > MSG_SIZE ? MSG_SIZE : one_msg.size() + 1, 
              "%s", one_msg.c_str());
      sent = mq->try_send(msg, sizeof(msg), 0);
      if (sent)
        msg_queue.pop();
      std::cout << "message" << (sent ? " " : " NOT ") << "sent" << std::endl;
    }
    std::cout << "Queue size " << msg_queue.size() << std::endl;
  }

  bool receive()
  {
    unsigned int priority;
    message_queue::size_type recvd_size;
    message_t msg;

    mq->receive(msg, sizeof(msg), recvd_size, priority);
    std::cout << recvd_size << ", " << priority << ": " << msg << std::endl;

    int ret = memcmp(msg, END_MSG, sizeof(END_MSG));
    std::cout << msg << " vs " << END_MSG << " : " << ret << std::endl;
    return ret != 0;
  }
};

template<class T>
void operator<<(Chat &c, const T &val)
{
  std::stringstream ss;
  ss << val;
  c.send(ss.str());
}

int main (int argc, char *argv[])
{
  printf("Start of process with ID %d\n", ::getpid());
  if(argc == 1) {  //Parent process
    BOOST_TRY{
      std::cout << "Creating shared memory" << std::endl;
      Chat chat(true, "MyQueue");

      bool end = false;
      do {
        std::cout << "Finish (f), Stop (s), Start (n), Message (any other)" << std::endl;
        std::string str;
        std::cin >> str;
        std::cout << "Read " << str << std::endl;
        if (str.size() == 1) {
          char option = str[0];
          std::cout << "Option " << option << std::endl;
          switch (option)
          {
          case 'f':
            chat << END_MSG;
            end = true;
            break;
          case 's':
            chat << STOP_MSG;
            break;
          case 'n':
            chat << START_MSG;
            break;        
          default:
            chat << str;
            break;
          }
        } else {
          chat << str;
        }
      } while (!end);
    }
    BOOST_CATCH(interprocess_exception &ex){
      std::cout << ex.what() << std::endl;
      return 1;
    } BOOST_CATCH_END
  } else {
    BOOST_TRY{
      std::cout << "Opening shared memory" << std::endl;
      Chat chat(false, "MyQueue");
      while(chat.receive());
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