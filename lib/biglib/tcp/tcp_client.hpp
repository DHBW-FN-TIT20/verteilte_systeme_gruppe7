
/**************************************************************************************************
 * @file    tcp_client.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   This file contains the implementation for the tcp client.
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
#include <cstring>
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

class TcpClient : public std::enable_shared_from_this<TcpClient> {
  private:
    io_service mIoContext;
    tcp::socket mSocket;
    T_Endpoint mRemoteEndpoint;
    std::array<char, 4096> mBuffer;
    std::function<void(const std::string)> responseHandler;

  public:
    TcpClient(T_Endpoint endpoint, std::function<void(const std::string)> callback) : mSocket(mIoContext), mRemoteEndpoint(endpoint), responseHandler(callback) {}

    void connect(void) {
      tcp::resolver resolver(mIoContext);
      auto endpoint_iterator = resolver.resolve(mRemoteEndpoint.address, mRemoteEndpoint.port);
      asio::connect(mSocket, endpoint_iterator);
    }

    void sendMessage(const std::string &message) {
      asio::write(mSocket, asio::buffer(message, message.size()));
    }

    std::string waitForSingleResponse(void) {
      asio::streambuf buffer;
      asio::read_until(mSocket, buffer, "\n");

      std::istream is(&buffer);
      std::string response;
      std::getline(is, response);
      return response;
    }

    void continuousReceive(void) {
      auto self(shared_from_this());
      mSocket.async_read_some(asio::buffer(mBuffer), [this, self](asio::error_code ec, std::size_t length) {
        if(!ec) {
          this->responseHandler(std::string(mBuffer.data(), length));
          continuousReceive();
        } else {
          //TODO: Error
        }
      });
    }

    tcp::socket &socket(void) {
      return mSocket;
    }

    void run(void) {
      mIoContext.run();
    }

    void close(void) {
      mSocket.close();
    }

};
