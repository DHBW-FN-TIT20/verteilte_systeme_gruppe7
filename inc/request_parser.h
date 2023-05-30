/**
 *************************************************************************************************
 * @file    request_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    29-May-2023
 * @brief   Prototype for class RequestParser
 *************************************************************************************************
 */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>
#include <iostream>

/* Own Libs */
#include "request_type.h"

 /*************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class RequestParser {
  public:
    /**
     * @brief Encode the specified request into string
     *
     * @param request The request which schould be encoded to a string
     */
    std::string encode(RequestType request) const;
    /**
     * @brief Decode the specified request string into an object of type T_Request
     *
     * @param requestString The string which should be decoded to an object
     */
    RequestType decode(std::string requestString) const;
};
