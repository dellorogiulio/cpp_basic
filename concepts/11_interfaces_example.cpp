/* 
 ---INTERFACES EXAMPLE ---	
*/

/*
    Consider the case in which we would model a TCP message class. We have an already written library which provides us a TCP connection class.
    This class, that we will call here 'TCPClient', allows us to send a buffer of bytes that are stored in a std::string. 
*/

#include <stdio.h>
#include <string>

/*  
    CASE 1: pure inheritance
        in this case we intend to extend a BasicMsg class and edit the base-class data from the subclass
*/

struct TCPClient
{
    // ...
    void send(const std::string&)
    {
        /* magic TCP stuff */
    }
};

namespace first_try
{
struct BasicMsg
{
   protected:
    std::string data_;

   public:
    std::string data() const { return data_; }
};

void sendData(const BasicMsg& msg)
{
    TCPClient tcp_client;
    tcp_client.send(msg.data());
}

struct IntMsg : public BasicMsg
{
    void setData(const int data) { data_ = std::to_string(data); }
};

struct StringMsg : public BasicMsg
{
    void setData(const std::string& data) { data_ = data; }
};

/* Here we are use pure inheritance: all subclasses directly set an attribute of BasicMsg and it returns the data */
/* In this case, we encode the data into a std::string everytime the data changes */

void sendToTcp()
{
    IntMsg int_msg;
    StringMsg string_msg;
    int_msg.setData(1);
    string_msg.setData("ciao");
    sendData(int_msg);
    sendData(string_msg);
}

}  // namespace first_try

namespace second_try
{
/*  Now we try to declare an encode function which should return a std::string representing the encoded msg */
struct BasicMsg
{
    virtual std::string encode() const = 0;
};

class IntMsg : public BasicMsg
{
    int data_;

   public:
    void setData(const int data) { data_ = data; }
    std::string encode() const override { return std::to_string(data_); }
};

struct StringMsg : public BasicMsg
{
    std::string data_;

   public:
    void setData(const std::string& data) { data_ = data; }
    std::string encode() const override { return data_; }
};

void sendData(const BasicMsg& msg)
{
    TCPClient tcp_client;
    tcp_client.send(msg.encode());
}

/* Here we are use inheritance to create an interface: do you want to be a message? Simply expose a encode method which returns a std::string  */
/* In this case, we encode only once before sending to the tcp connection */

void sendToTcp()
{
    IntMsg int_msg;
    StringMsg string_msg;
    int_msg.setData(1);
    string_msg.setData("ciao");
    sendData(int_msg);
    sendData(string_msg);
}

}  // namespace second_try

/* 
    Which method is the best? It depends. Both are correct and functional but they work in a very different way. 
    In the first case, for example, BasicMsg is de-facto a StringMsg and we could potentially use directly a BasicMsg without problem
    In the second case, you cannot use directly a BasicMsg: you must extend it, define an encode method and use that class.
*/
int main()
{
    first_try::sendToTcp();
    second_try::sendToTcp();
}
