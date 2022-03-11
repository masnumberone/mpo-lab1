#include <string>
#include <iostream>
#include "date.h"

struct Telecast {
    std::string channel;
    std::string program;
    Date startTime;

    Telecast(std::string, std::string, Date);                       //channel, program, startTime
    friend std::ostream& operator<<(std::ostream&, Telecast);
};
