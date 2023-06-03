/**************************************************************************************************
 * @file    message_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    03-June-2023
 * @brief   
 **************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
#include "nlohmann/json.hpp"

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
class MessageParser {
  public:
    template <typename T>
    T decodeObject(const std::string& objectString);

    template <typename T>
    std::string encodeObject(const T& object);
};
