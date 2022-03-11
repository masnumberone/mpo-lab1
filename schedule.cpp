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

void Schedule::add(std::string channel, std::string program, Date startTime) {
    Telecast telecast(channel, program, startTime);
    scheduleList.push_back(telecast);
}

bool Schedule::erase(int n) {
    if (scheduleList.empty()) return false;
    auto it = scheduleList.begin();
    for (int i = 0; i < n; i++) it++;
    scheduleList.erase(it);
    return true;
}

Telecast Schedule::get(int n) {
    std::list<Telecast>::iterator it = scheduleList.begin();
    
    for (int i = 0; i < n; i++) it++;
    return *it;
}

bool Schedule::load() {
    std::ifstream file("DATA.txt");
    if (!file.is_open()) return false;
    
    std::string channel, program, startDateBuf, startTimeBuf;
    Date startTime;
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
        channel = ""; program = ""; startDateBuf = ""; startTimeBuf = "";
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

        if (strCorrect) {
            add(channel, program, startTime);
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

bool Schedule::isSortedChannel() {
    return sorting == 1;
}

bool Schedule::isSortedProgram() {
    return sorting == 2;
}

bool Schedule::isSortedTime() {
    return sorting == 3;
}

void Schedule::print() {
    if (isSortedTime()) {
        std::string date = (*scheduleList.begin()).startTime.getDate();
        std::cout << date << ":" << std::endl;
        for ( Telecast tmp : scheduleList ) {
            if (date != tmp.startTime.getDate()) std::cout << std::endl << tmp.startTime.getDate() << ":" << std::endl;
            std::cout << " " << tmp.startTime.getTime() << " [" << tmp.channel << "] " << tmp.program << std::endl;
            date = tmp.startTime.getDate();
        } 
    }
    else if (isSortedProgram()) {
        // std::string program = (*scheduleList.begin()).program;
        // for (Telecast tmp : scheduleList) {
        //     if (program != tmp.program) std::cout << std::endl << tmp.program << ":" << std::endl;
        //     std::cout << tmp.channel << " " << tmp.startTime.getTime() << "-" << tmp.endTime.getTime() << std::endl;
        //     program = tmp.program;
        // }

        std::string program = (*scheduleList.begin()).program;
        std::cout << program  << ":" << std::endl;
        for (Telecast tmp : scheduleList) {
            if (program != tmp.program) std::cout << std::endl << tmp.program << ":" << std::endl;
            std::cout << "  " << tmp.startTime.getTime() << " (" << tmp.startTime.getDate() << ") " << tmp.channel << std::endl;
            program = tmp.program;
        }
    }
    else if (isSortedChannel()) {
        std::string channel = (*scheduleList.begin()).channel;
        std::string date = (*scheduleList.begin()).startTime.getDate();
        std::cout << channel << ":" << std::endl << "  [" << date << "]" << std::endl;
        for (Telecast tmp : scheduleList) {
            if (channel != tmp.channel) {
                std::cout << std::endl << tmp.channel << ": " << std::endl << "  [" << tmp.startTime.getDate() << "]" << std::endl
                    << "  " << tmp.startTime.getTime() << " " << tmp.program << std::endl;
            }
            else if (date != tmp.startTime.getDate()) {
                std::cout << std::endl << "  [" << tmp.startTime.getDate() << "]" << std::endl << "  " << tmp.startTime.getTime()
                    << " " << tmp.program << std::endl;
            }
            else std::cout << "  " << tmp.startTime.getTime() << " " << tmp.program << std::endl;
            channel = tmp.channel;
            date = tmp.startTime.getDate();
        }
    }
}

bool Schedule::save() {
    std::ofstream file("DATA.txt");
    if (!file.is_open()) return false;

    char separator = 1;
    for (Telecast tmp : scheduleList) {
        file << separator << tmp.channel << separator << tmp.program << separator << tmp.startTime.getDate() << separator 
            << tmp.startTime.getTime() << separator << separator << std::endl;
    }
    file.close();
    return true;
}

void Schedule::sortChannel(bool ascending) {
    sortTime(sortAscending);

    if (ascending) {
        scheduleList.sort([] (Telecast a, Telecast b) {
            return a.channel < b.channel;
        });
    }
    else {
        scheduleList.sort([](Telecast a, Telecast b) {
            return a.channel > b.channel;
            });
    }
    sorting = 1;
}

void Schedule::sortProgram(bool ascending) {
    sortTime(sortAscending);
    if (ascending) {
        scheduleList.sort([](Telecast a, Telecast b) {
            return a.program < b.program;
            });
    }
    else {
        scheduleList.sort([](Telecast a, Telecast b) {
            return a.program > b.program;
            });
    }
    sorting = 2;
}

void Schedule::sortTime(bool ascending) {
    if (ascending) {
        scheduleList.sort([](Telecast a, Telecast b) {
            return a.startTime < b.startTime;
            });
    }
    else {
        scheduleList.sort([](Telecast a, Telecast b) {
            return a.startTime > b.startTime;
            });
    }
    sortAscending = ascending;
    sorting = 3;
}

int Schedule::size() {
    return scheduleList.size();
}

