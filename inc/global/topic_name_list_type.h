<<<<<<<< HEAD:inc/global/topic_name_list_type.h
/**************************************************************************************************
  * @file    action_enum.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    01-June-2023
========
/**
  *************************************************************************************************
  * @file    topic_list_type.h
  * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
  * @date    05-June-2023
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_list_type.h
  * @brief   
  ************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <vector>
<<<<<<<< HEAD:inc/global/topic_name_list_type.h
#include <string>
========
#include "topic_type.h"
>>>>>>>> 2381ea8 (:label: update file names to match naming convention):inc/global/topic_list_type.h

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
