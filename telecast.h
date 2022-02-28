#include <string>
#include <iostream>
#include "date.h"

struct Telecast {
    std::string channel;
    std::string program;
    Date startTime;
    Date endTime;

    Telecast(std::string, std::string, Date, Date);              //channel, program, startTime, endTime
    friend std::ostream& operator<<(std::ostream&, Telecast);
};
