#include "log_data.hpp"

logData::logData(){
    std::cout<<"logData class active"<<std::endl;
}
logData::~logData(){
    std::cout<<"logData class Disable"<<std::endl;
}
void logData::echoData(int data){
    std::cout<<"data: " << data<< std::endl;
}