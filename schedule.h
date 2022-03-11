#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "telecast.h"
#include <list>
#include <fstream>
#include <ctime>

class Schedule {
private:
    std::list<Telecast> scheduleList;
    int sorting = 0;                                                       // 1 - channel, 2 - program, 3 - time
    bool sortAscending;

public:
    Schedule();
    ~Schedule();
    void add(Telecast);
    void add(std::string, std::string, Date);                              //
    bool erase(int);                                                       // удалить по номеру, начало - 0
    Telecast get(int);                                                     // номер в списке
    bool load();
    bool isSortedChannel();
    bool isSortedProgram();
    bool isSortedTime();
    void print();
    bool save();
    void sortChannel(bool = true);                                          // false - в обратном порядке
    void sortProgram(bool = true);
    void sortTime(bool = true);
    int size();

};


#endif