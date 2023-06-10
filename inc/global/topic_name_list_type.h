/**************************************************************************************************
  * @file    action_enum.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    01-June-2023
  * @brief   
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <vector>
#include <string>

/**************************************************************************************************
 * Public - typedefs / structs / enums
 *************************************************************************************************/
struct T_TopicNameList {
  std::vector<std::string> TopicNameList;

  std::string toString() {
    std::string result;
    for(size_t i = 0; i < TopicNameList.size(); i++) {
      result += TopicNameList.at(i);
      result += (i != TopicNameList.size() - 1) ? ", " : ";";
    }
    return result;
  }
};
