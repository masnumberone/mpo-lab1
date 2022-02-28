#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "telecast.h"
#include <list>
#include <fstream>
#include <ctime>

class Schedule {
private:
    std::list<Telecast> scheduleList;

public:
    Schedule();
    ~Schedule();
    void add(Telecast);
    void add(std::string, std::string, Date, Date);                        //
    Telecast get(int);                                                     // номер в списке
    bool load();
    bool save();
    void remove(int);

};


#endif