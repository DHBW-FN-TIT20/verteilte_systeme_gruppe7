/**
 *************************************************************************************************
 * @file    request_parser.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    28-May-2023
 * @brief   
 *************************************************************************************************
 */

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
/* C++ Libs */
#include <string>

#include "../inc/global/T_Request.h"

using std::string;

 /*************************************************************************************************
 * Public - Class prototype
 *************************************************************************************************/

class REQUEST_PARSER {
  public:
    /**
     * @brief Encode the specified request into string
     *
     * @param request The request which schould be encoded to a string
     */
    string encode(T_Request request) const;
};
