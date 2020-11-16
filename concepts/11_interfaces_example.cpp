/* 
 ---INTERFACES EXAMPLE ---	
*/

/*
    Let's suppose that we have already written a library which provides us a TCP connection class.
    This class, that we call here 'TCPClient', allows us to send a buffer of bytes that are stored in a std::string over a TCP connection.
    Now we need to model a TCP message class, so that we can fill the several messages to be sent.
*/

#include <stdio.h>
#include <string>

/*  
    CASE 1: pure inheritance
        in this case we're going to extend a BasicMsg class so that every subclass can edit the base-class data
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
    ~BasicMsg() = default;

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

struct IntMsg : public BasicMsg   // this is the message where the content to be sent is of type 'int'
{
    void setData(const int data) { data_ = std::to_string(data); }
};

struct StringMsg : public BasicMsg   // this is the message where the content to be sent is of type 'std::string'
{
    void setData(const std::string& data) { data_ = data; }
};

/* Here we are using pure inheritance: all subclasses directly set an attribute of BasicMsg and they return the data */
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
/*  Now we're going to follow a different approach, declaring an encode function which returns a std::string representing the encoded msg */
struct BasicMsg
{
    virtual std::string encode() const = 0;  // pure virtual --> no matter the details, but EVERY XxxMsg MUST implement an encode() method which returns
                                             // the std::string with the message enconding
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

/* Here we are using inheritance to create an interface: do you want to be a message? Simply expose an encode() method which returns a std::string  */
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
