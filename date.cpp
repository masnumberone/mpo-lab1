#include "date.h"

Date::Date() {
    year = 1998;
    mounth = 1;
    day = 1;
    hour = 12;
    minute = 0;
}

Date::Date(int _year, int _mounth, int _day, int _hour, int _minute) {
    year = _year;
    mounth = _mounth;
    day = _day;
    hour = _hour;
    minute = _minute;
}

Date::Date(std::string date, std::string time) {
    // временное решение

    year = 1998;
    mounth = 1;
    day = 1;
    hour = 12;
    minute = 0;

}

std::string Date::getTime() {
    std::string outHour, outMinute;

    if (hour < 10) outHour = "0";
    outHour += std::to_string(hour);

    if (minute < 10) outMinute = "0";
    outMinute += std::to_string(minute);
    return outHour + ":" + outMinute;
}

std::string Date::getDate() {
    std::string outMounth, outDay;

    if (mounth < 10) outMounth = "0";
    outMounth += std::to_string(mounth);

    if (day < 10) outDay = "0";
    outDay += std::to_string(day);
    return outDay + "." + outMounth + "." + std::to_string(year);
}

bool Date::setTime(std::string& str) {
    bool checkFormat = false;
    for (char c : str) {
        if (c == ':') checkFormat = true;
    }
    if (!checkFormat) return false;
    hour = std::stoi(str.substr(0, 2));
    minute = std::stoi(str.substr(3, 2));
    if ((hour >= 0) && (hour < 24) && (minute >= 0) && (minute < 60)) return true;
    hour = 0;
    minute = 0;
    return false;
}

bool Date::setDate(std::string& str) {
    int countPoint = 0;
    for (char c : str) {
        if (c == '.') countPoint++;
    }
    if (countPoint < 2) return false;
    day = std::stoi(str.substr(0,2));
    mounth = std::stoi(str.substr(3,2));
    year = std::stoi(str.substr(6,4));

    //грубая проверка, поправить!
    if ((day>0) && (day <= 31) && (mounth > 0) && (mounth <= 12) && (year > 1926 )) return true;
    day = 1;
    mounth = 1;
    year = 1980;
    return false;
}