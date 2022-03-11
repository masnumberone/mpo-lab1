#include "telecast.h"

Telecast::Telecast(std::string channel, std::string program, Date startTime) {
    this->channel = channel;
    this->program = program;
    this->startTime = startTime;
}

std::ostream& operator<<(std::ostream& out, Telecast telecast) {
    out << telecast.channel << ": " << telecast.program << " " << telecast.startTime.getTime() << ")\n";
    return out; 
}