/**************************************************************************************************
 * @file    message_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    06-June-2023
 * @brief   Prototype for class MessageParser.
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>

/* Own Libs / datatypes */
#include "request_type.h"
#include "action_status_type.h"
#include "topic_status_type.h"
#include "subscriber_list_type.h"

/**************************************************************************************************
 * Public - classes
 *************************************************************************************************/
class MessageParser {
  public:
    /**
     * @brief function template for decoding json to different datatypes
     * 
     * @tparam T type to decode json string into
     * @param objectString json string
     * @return T object of type T that holds the respective data from the json string
     */
    template <typename T>
    T decodeObject(const std::string& objectString);

    /**
     * @brief function template to encode different datatypes to json
     * 
     * @tparam T datatype to convert into json
     * @param object object of type T to encode
     * @return std::string json string with the data of the respective object
     */
    template <typename T>
    std::string encodeObject(const T& object);
};
