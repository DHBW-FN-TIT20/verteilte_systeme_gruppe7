/**
 *************************************************************************************************
 * @file    request_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    28-May-2023
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
#include "T_Request.h"

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
    std::string encode(T_Request request) const;
};
