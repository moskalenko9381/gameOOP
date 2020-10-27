#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <iostream>
#include <fstream>
#define PATH "/Users/elizaveta/Desktop/logs.txt"

class Logger
{
   Logger* next;
public:
   friend class LoggerHolder;
   virtual ~Logger() = default;
   virtual void write(const std::string& change) = 0;
};

#endif // LOGGER_H
