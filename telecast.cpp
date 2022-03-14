#include "telecast.h"

Telecast::Telecast(std::string channel, std::string program, Date startTime) {
    this->channel = channel;
    this->program = program;
    this->startTime = startTime;
}

std::ostream& operator<<(std::ostream& out, Telecast telecast) {
    out << telecast.startTime.getTime() << " (" << telecast.startTime.getDate() << ") " << telecast.channel << ": " << telecast.program  << std::endl;
    return out; 
}