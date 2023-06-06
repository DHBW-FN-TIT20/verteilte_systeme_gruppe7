
/**************************************************************************************************
 * @file    network_handler_interface.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   This file contains the generic network handler interface for flexible network
 *          communication.
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <cstdint>
#include <array>
#include <functional>

/* Own Libs / datatypes */
#include "endpoint_type.h"

/* dependencies */
#include "asio.hpp"

using namespace asio;
using namespace asio::ip;
using asio::ip::tcp;


/**************************************************************************************************
 * Class implementation
 *************************************************************************************************/

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
  private:
    tcp::socket             mSocket;                            /* socket for this connection */
    std::array<char, 1024>  mBuffer;                            /* buffer for incoming data */
    std::function<void(std::shared_ptr<TcpConnection>, const std::string&)> messageHandler;

    /**
     * @brief Default constructor for class TcpConnection.
     * Create a new socket for a client connection.
     * 
     * @param ioContext asio::io_context object
     */
    TcpConnection(asio::io_context &ioContext) : mSocket(ioContext) {}

  public:
    static std::shared_ptr<TcpConnection> create(asio::io_context &ioContext) {
      return std::shared_ptr<TcpConnection>(new TcpConnection(ioContext));
    }

    /**
     * @brief Get the socket used for the respective connection
     * 
     * @return tcp::socket& socket for the respective connection
     */
    tcp::socket &socket() {
      return mSocket;
    }

    /**
     * @brief Entry point for communication between client and server
     * 
     */
    void start(std::function<void(std::shared_ptr<TcpConnection>, const std::string)> callback) {
      messageHandler = callback;
      // read and write data
      startRead();
    }

    void startRead(void) {
      auto self(shared_from_this());
      mSocket.async_read_some(asio::buffer(mBuffer), [this, self](asio::error_code ec, std::size_t length) {
        if(!ec) {
          messageHandler(self, std::string(mBuffer.data(), length));
          startRead();
        } else {
          //TODO: Error
        }
      });
    }

    void sendResponse(const std::string& response) {
      asio::async_write(mSocket, asio::buffer(response), [self = shared_from_this()](const asio::error_code &ec, std::size_t) {
        if(ec) {
          //TODO: Error
        }
      });
    }
};


class TcpServer {
  private:
    io_service mIoContext;
    tcp::endpoint mTcpEndpoint;
    tcp::acceptor mTcpAcceptor;
    std::function<void(std::shared_ptr<TcpConnection>, const std::string)> mMessageHandler;

  public:

    /**
     * @brief Default constructor for class TcpServer
     * 
     * @param endpoint address of the server and port to listen to for client connection requests
     */
    TcpServer(T_Endpoint endpoint, std::function<void(std::shared_ptr<TcpConnection>, const std::string)> callback) : mTcpEndpoint(tcp::endpoint(tcp::v4(), static_cast<uint16_t>(std::stoi(endpoint.port)))), mTcpAcceptor(mIoContext, mTcpEndpoint), mMessageHandler(callback) {}

    /**
     * @brief asynchronously start accepting clients.
     * When a new client is accepted, the connection is beeing handled in an instance of class TcpConnection.
     * 
     */
    void startAccept(void) {
      std::shared_ptr<TcpConnection> newConnection = TcpConnection::create(mIoContext);

      mTcpAcceptor.async_accept(newConnection->socket(), [this, newConnection](const asio::error_code &ec) {
          handleAccept(newConnection, ec);    //possible client accept
          startAccept();                      //start accepting new clients
        });
    }

    void handleAccept(std::shared_ptr<TcpConnection> newConnection, const asio::error_code &ec) {
      if(!ec) {
        newConnection->start(mMessageHandler);       //accept the client -> start connection in instance of class TcpConnection
        std::cout << "Accepted connection: " << newConnection->socket().remote_endpoint() << std::endl;   //display ip and port of client in the terminal
      } else {
        //TODO: Error
      }
    }

    /**
     * @brief start the server and begin accepting clients
     * 
     */
    void run(void) {
      startAccept();
      mIoContext.run();
    }
};


/* example for using the server (don't execute this): */

//#define RUN_TCP_SERVER
#ifdef RUN_TCP_SERVER

/**
 * @brief Callback function to be executed when new data from a client is received
 * 
 * @param message received data string
 */
void messageHandler(const std::string message) {
  std::cout << "message handler: " << message << std::endl;
}


// This will start a simple tcp server that accepts clients on port 8080 and handle the received data with the callback function messageHandler
int main() {
  TcpServer acceptServer({"localhost", "8080"}, messageHandler);      // get instance of TcpServer; set port to listen to to 8080
  acceptServer.run();                                 // start the server -> begin accepting clients

  std::cout << "Server closed" << std::endl;
  return 0;
}

#endif
