#include <string>

struct Date {
    int year;
    int mounth;
    int day;
    int hour;
    int minute;

    Date();
    Date(int, int, int, int, int);                            // конструктор (int) ГОД, МЕСЯЦ, ДЕНЬ, ЧАС, МИНУТА
    Date(std::string, std::string);                           // конструктор (string) ДАТА, ВРЕМЯ
    std::string getTime();
    std::string getDate();
    bool setTime(std::string);
    bool setDate(std::string);

    friend bool operator<(Date, Date);
    friend bool operator>(Date, Date);
};