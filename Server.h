/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_


#include "commands.h"
#include "CLI.h"
#include <thread>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};

class Socket_IO : public DefaultIO{
    int clientID;
public:
    Socket_IO(int clientID) {
        this->clientID = clientID;
    }

    string read() override {
        char buff = 0;
        string str = "";
        while(true){
            //recv(clientID, &buff, sizeof(char), 0);
            ::read(clientID,&buff,sizeof(char));
            if(buff == '\n'){
                break;
            }
            str += buff;
        }
        return str;
    }

    void write(string text) override {
        ::send(clientID, text.c_str(), text.length(), 0);
    }
    void write(float f) override {
        string str = to_string(f);
        write(str);
    }
    void read(float* f) override {
    string s = read();
    *f = stof(s);
    }
};


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
	public:
    virtual void handle(int clientID){
        Socket_IO s(clientID);
        CLI cli = CLI(&s);
        cli.start();
    }
};


// implement on Server.cpp
class Server {
	std::thread* t; // the thread to run the start() method in
    int fd;
    sockaddr_in server;
    sockaddr_in client;
    bool isStop;

public:
	Server(int port) throw (const char*);
	virtual ~Server();
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
