#include "filelogger.h"

FileLogger::FileLogger()
{
    std::string name = PATH;
    output  = new std::fstream(PATH, std::ios::app);
 // output->open("./logging.txt", std::ios::out | std::ios::app);
    type = 2;
}

FileLogger::FileLogger(std::string filename){
    output  = new std::fstream(filename);
 //output->open(filename,std::ios::in | std::ios::app);
     if(!output)
              std::cerr << "Error of writing logs of program\n";
    //output.open(filename, std::ios::out | std::ios::in | std::ios::app);
     type = 2;
}

void FileLogger::write(const std::string& change){
    *output << "HII\n";
    *output << change << '\n';
}

FileLogger::~FileLogger(){
    output->close();


    //delete output;
}

