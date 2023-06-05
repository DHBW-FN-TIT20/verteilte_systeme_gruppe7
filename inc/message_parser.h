/**************************************************************************************************
 * @file    message_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    05-June-2023
 * @brief   Prototype for class MessageParser.
 **************************************************************************************************

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
#include "nlohmann/json.hpp"

/**************************************************************************************************
 * Public - classes
 *************************************************************************************************/
class MessageParser {
  public:
    template <typename T>
    T decodeObject(const std::string& objectString);

    template <typename T>
    std::string encodeObject(const T& object);
};
