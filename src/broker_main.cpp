/**************************************************************************************************
 * @file    broker_main.cpp
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    12-June-2023
 * @brief   This file contains the program entry and instantiation for a broker object.
 *          -> Main file for class Broker
 *************************************************************************************************/

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <iostream>
#include <csignal>
#include "broker.h"

/**************************************************************************************************
 * Public - Global variables
 *************************************************************************************************/
Broker* Broker::instance = nullptr;

/**************************************************************************************************
 * Function prototypes
 *************************************************************************************************/

/**************************************************************************************************
 * Program entry point
 *************************************************************************************************/
int main(int argc, char* argv[]) {
  std::vector<std::string> args(argv, argv + argc);
  T_Endpoint serverEndpoint;

  /* get server endpoint */
  auto it = std::find(args.begin(), args.end(), "--server-address");
  if(it != args.end() && ++it != args.end()) {
    serverEndpoint.address = *it;
    it = std::find(args.begin(), args.end(), "--server-port");
    if(it != args.end() && ++it != args.end()) {
      serverEndpoint.port = *it;
    } else {
      throw std::invalid_argument("No server-port found");
    }
  } else {
    throw std::invalid_argument("No server-address found");
  }

  Broker broker(serverEndpoint.address, serverEndpoint.port);

  return 0;
}
