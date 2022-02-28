#include "schedule.h"

Schedule::Schedule() {
    std::fstream log("log.txt", std::ios_base::app);
    if (log.is_open()) {
        time_t now = time(0);
        log << ctime(&now);
        log.close();
    }
}

Schedule::~Schedule() {
}

void Schedule::add(Telecast telecast) {
    scheduleList.push_back(telecast);
}

void Schedule::add(std::string channel, std::string program, Date startTime, Date endTime) {
    Telecast telecast(channel, program, startTime, endTime);
    scheduleList.push_back(telecast);
}

Telecast Schedule::get(int n) {
    std::list<Telecast>::iterator it = scheduleList.begin();
    
    for (int i = 0; i < n; i++) it++;
    return *it;
}

bool Schedule::load() {
    std::ifstream file("DATA.txt");
    if (!file.is_open()) return false;
    
    std::string channel, program, startDateBuf, startTimeBuf, endDateBuf, endTimeBuf;
    Date startTime, endTime;
    bool strCorrect = false;
    bool fileCorrect = true;
    char separator = 1;

    while(file.peek() != EOF) {
        if (!strCorrect) {
            while ((file.peek() != separator) && (file.peek() != EOF)) file.get();
            if (file.peek() == EOF) {
                file.close();
                if (scheduleList.empty()) return false;
                return fileCorrect;
            }
            if (file.get() != separator) continue;
            strCorrect = true;
        }
        channel = ""; program = ""; startDateBuf = ""; startTimeBuf = ""; endDateBuf = ""; endTimeBuf = "";
        while (file.peek() != separator)
            channel = channel + (char)file.get();
        file.seekg(1, std::ios::cur);
        while (file.peek() != separator)
            program = program + (char)file.get();
        file.seekg(1, std::ios::cur);
        while (file.peek() != separator)
            startDateBuf = startDateBuf + (char)file.get();
        if (!startTime.setDate(startDateBuf)) strCorrect = false;
        file.seekg(1, std::ios::cur);
        while (file.peek() != separator)
            startTimeBuf = startTimeBuf + (char)file.get();
        if (!startTime.setTime(startTimeBuf)) strCorrect = false;
        file.seekg(1, std::ios::cur);
        while (file.peek() != separator)
            endDateBuf = endDateBuf + (char)file.get();
        if (!endTime.setDate(endDateBuf)) strCorrect = false;
        file.seekg(1, std::ios::cur);
        while (file.peek() != separator)
            endTimeBuf = endTimeBuf + (char)file.get();
        if (!endTime.setTime(endTimeBuf)) strCorrect = false;

        if (strCorrect) {
            add(program, channel, startTime, endTime);
            strCorrect = false;
            while (!strCorrect) {
                while (file.peek() != separator) file.get();
                if (file.get() != separator) continue;
                if (file.get() != separator) continue;
                if (file.peek() == EOF) break;
                if (file.get() != '\n') continue;
                strCorrect = true;
            }
        }
        else {
            fileCorrect = false;
            while (!strCorrect) {
                while (file.peek() != separator) file.get();
                if (file.get() != separator) continue;
                if (file.get() != separator) continue;
                if (file.peek() == EOF) break;
                if (file.get() != '\n') continue;
                strCorrect = true;
            }
        }
        strCorrect = false;
    }
    return fileCorrect;
}

bool Schedule::save() {
    std::ofstream file("DATA.txt");
    if (!file.is_open()) return false;

    char separator = 1;
    for (Telecast tmp : scheduleList) {
        file << separator << tmp.channel << separator << tmp.program << separator << tmp.startTime.getDate() << separator 
            << tmp.startTime.getTime() << separator << tmp.endTime.getDate() << separator << tmp.endTime.getTime() << separator << separator << std::endl;
    }
    file.close();
    return true;
}