#include "telecast.h"

Telecast::Telecast(std::string channel, std::string program, Date startTime, Date endTime) {
    this->channel = channel;
    this->program = program;
    this->startTime = startTime;
    this->endTime = endTime;
}

std::ostream& operator<<(std::ostream& out, Telecast telecast) {
    out << telecast.channel << ": " << telecast.program << " (" << telecast.startTime.getTime() << "-" << telecast.endTime.getTime() << ")\n";
    return out; 
}