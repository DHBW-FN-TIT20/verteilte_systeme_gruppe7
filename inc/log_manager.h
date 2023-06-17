/**************************************************************************************************
 * @file    log_manager.h
 * @author  Christoph Koßlowski, Lukas Adrion, Thibault Rey, Ralf Ehli, Philipp Thümler
 * @date    10-June-2023
 * @brief   Prototype for class LogManger
 *************************************************************************************************/

#pragma once

/**************************************************************************************************
 * Include Header Files
 *************************************************************************************************/
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <iomanip>

/**************************************************************************************************
 * Public - Class prototype
 **************************************************************************************************/

class LogManager {
  private:
    /* private member variables */
    std::ofstream mFile;
    std::mutex mLogFileMutex;

  protected:
    /* protected member functions */
    /**
     * @brief 
     * 
     */
    void close(void);

  public:
    /**
     * @brief Get the current timestamp and convert it into a readable string
     * 
     * @return std::string 
     */
    std::string getTimestampString(void) const;

    /* public member functions */
    /**
     * @brief Default constructor for class LogManager
     * 
     * @param filename Name of log file
     */
    LogManager(const std::string& filename);

    /**
     * @brief Default destructor for class LogManager
     * 
     */
    ~LogManager();

    /**
     * @brief Add an entry to the log
     * 
     * @param logMessage Message to be added to log file
     */
    void addLogEntry(const std::string& logMessage);
};
