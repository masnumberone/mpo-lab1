#include "schedule.h"
#include <iostream>
#include <map>

void startProgram() {
    system("clear");
    Schedule tvProgram;
    tvProgram.load();
    tvProgram.sortChannel();
    int key = -1;
    while (key == -1) {
        std::cout << "Выберите действие:" << std::endl
            << "[1] Показать телепрограмму" << std::endl
            << "[2] Показать телепрограмму полностью" << std::endl
            << "[3] Изменить сортировку записей" << std::endl
            << "[4] Добавить новую запись" << std::endl
            << "[5] Изменить определенную запись" << std::endl
            << "[6] Удалить определенную запись" << std::endl
            << "[7] Удалить все записи" << std::endl
            << "[0] Завершить выполнение программы"  << std::endl << std::endl << ">>> ";
        std::cin >> key;

        if (std::cin.get() != '\n') {
            std::cin.clear();
            while (std::cin.get() != '\n');
            key = -1;
            system("clear");
            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
            continue;
        }

        switch (key) {
        case 0: {
            system("clear");
            return;
        }
        case 1: {
            system("clear");

            if (tvProgram.isEmpty()) {
                std::cout << "Список телепрограмм пуст." << std::endl << std::endl;
                key = -1;
                break;
            }

            std::map <int, std::string> channels;
            channels[0] = tvProgram.get(0).channel;
            for (int i = 0; i < tvProgram.size(); i++) {
                std::string channel = tvProgram.get(i).channel;
                bool check = false;
                for (auto it : channels) if (channel == it.second) check = true;
                if (!check) channels[i] = channel;
            }

            while (key != -1) {
                std::cout << "Выберите канал телепрограммы:" << std::endl << std::endl;

                int numberChannels = 1;
                for (auto it : channels) {
                    std::cout << "[" << numberChannels << "] " << it.second << std::endl;
                    numberChannels++;
                }

                std::cout << std::endl << "[0] В главное меню" << std::endl << std::endl << ">>> ";
                std::cin >> key;

                if (std::cin.get() != '\n') {
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                    key = -2;
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    continue;
                }

                if (key == 0) {
                    system("clear");
                    key = -1;
                    break;
                }

                if ((key > 0) && (key < numberChannels)) {

                    std::map<int, std::string> dates;
                    auto it = channels.begin();
                    std::advance(it, key - 1);
                    dates[(*it).first] = tvProgram.get((*it).first).startTime.getDate();
                    std::string channel = (*it).second;
                    for (int i = 0; i < tvProgram.size(); i++) {
                        if (tvProgram.get(i).channel != channel) continue;
                        std::string date = tvProgram.get(i).startTime.getDate();
                        bool check = false;
                        for (auto it : dates) if (date == it.second) check = true;
                        if (!check) dates[i] = date;
                    }
                    system("clear");

                    while (key != -2) {
                        std::cout << "Выберите дату телепрограммы:" << std::endl << std::endl;

                        int numberDates = 1;
                        for (auto it : dates) {
                            std::cout << "[" << numberDates << "] " << it.second << std::endl;
                            numberDates++;
                        }

                        std::cout << std::endl << "[0] В меню выбора канала" << std::endl << std::endl << ">>> ";
                        std::cin >> key;

                        if (std::cin.get() != '\n') {
                            std::cin.clear();
                            while (std::cin.get() != '\n');
                            key = 0;
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                            continue;
                        }

                        if (key == 0) {
                            system("clear");
                            key = -2;
                            break;
                        }

                        if ((key > 0) && (key < numberDates)) {

                            std::map<int, int> telecasts;
                            auto it = dates.begin();
                            std::advance(it, key - 1);
                            telecasts[(*it).first] = 0;
                            std::string dateTmp = (*it).second;
                            for (int i = 0; i < tvProgram.size(); i++) {
                                if (tvProgram.get(i).channel != channel) continue;
                                if (tvProgram.get(i).startTime.getDate() != dateTmp) continue;
                                bool check = false;
                                for (auto it : telecasts) if (i == it.first) check = true;
                                if (!check) telecasts[i] = 0;
                            }
                            system("clear");

                            std::cout << tvProgram.get((*telecasts.begin()).first).channel << " ("
                                << tvProgram.get((*telecasts.begin()).first).startTime.getDate() << "):" << std::endl << std::endl;

                            for (auto it : telecasts) {
                                std::cout << tvProgram.get(it.first).startTime.getTime() << " " << tvProgram.get(it.first).program << std::endl;
                            }

                            std::cout << std::endl << "Для выхода в главное меню, введите любое значение." << std::endl << ">>> ";
                            std::cin >> key;
                            if (std::cin.get() != '\n') {
                                std::cin.clear();
                                while (std::cin.get() != '\n');
                            }
                            key = -3;
                            system("clear");
                            break;

                        }
                        else {
                            key = 0;
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                        }
                    }
                    if (key == -3) key = -1;

                }
                else {
                    key = 0;
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                }
            }
            break;
        }
        case 2: {
            system("clear");

            if (tvProgram.isEmpty()) {
                std::cout << "Список телепрограмм пуст." << std::endl << std::endl;
                key = -1;
                break;
            }

            tvProgram.print();
            std::cout  << std::endl << "Для выхода в главное меню, введите любое значение." << std::endl << ">>> ";
            std::cin >> key;
            if (std::cin.get() != '\n') {
                std::cin.clear();
                while (std::cin.get() != '\n');
            }
            key = -1;
            system("clear");
            break;
        }
        case 3: {
            system("clear");
            if (tvProgram.isEmpty()) {
                std::cout << "Список телепрограмм пуст." << std::endl << std::endl;
                key = -1;
                break;
            }
            while (key != -1) {
                if (tvProgram.isSortedChannel()) std::cout << "Записи отсортированы по каналам." << std::endl;
                else if (tvProgram.isSortedProgram()) std::cout << "Записи отсортированы по программам." << std::endl;
                else if (tvProgram.isSortedTime()) std::cout << "Записи отсортированы по времени." << std::endl;
                else std::cout << "Записи не отсортированы." << std::endl;

                std::cout << std::endl << "Выберите действие:" << std::endl
                    << "[1] Отсортировать по каналам" << std::endl
                    << "[2] Отсортировать по программам" << std::endl
                    << "[3] Отсортировать по времени" << std::endl << std::endl
                    << "[0] В главное меню" << std::endl << ">>> ";
                std::cin >> key;

                if (std::cin.get() != '\n') {
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                    key = -2;
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    continue;
                }

                if (key == 0) {
                    system("clear");
                    key = -1;
                    break;
                }

                if ((key == 1) || (key == 2) || (key == 3)) {
                    int sort = key;
                    key = -2;
                    system("clear");
                    while (key == -2) {
                        if (sort == 1) std::cout << "Сортировка по каналам." << std::endl;
                        if (sort == 2) std::cout << "Сортировка по программам." << std::endl;
                        if (sort == 3) std::cout << "Сортировка по времени." << std::endl;

                        std::cout << std::endl << "Выберите действие:" << std::endl
                            << "[1] Отсортировать в прямом порядке" << std::endl
                            << "[2] Отсортировать в обратном порядке" << std::endl << std::endl
                            << "[0] Выбрать другую сортировку" << std::endl << ">>> ";
                        std::cin >> key;

                        if (std::cin.get() != '\n') {
                            std::cin.clear();
                            while (std::cin.get() != '\n');
                            key = -2;
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                            continue;
                        }
                        
                        if (key == 0) {
                            system("clear");
                            key = -3;
                            break;
                        }

                        if ((key == 1) || (key == 2)) {
                            if (sort == 1) tvProgram.sortChannel(key == 1);
                            if (sort == 2) tvProgram.sortProgram(key == 1);
                            if (sort == 3) tvProgram.sortTime(key == 1);

                            key = -1;
                            system("clear");
                            std::cout << "Записи отсортированны" << std::endl << std::endl;
                        }
                        else {
                            key = -2;
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                        }
                    }
                }
                else {
                    key = 0;
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                }

            }

            //system("clear");
            break;
        }
        case 4: {
            system("clear");
            std::string channel, program, strStartDate, strStartTime;
            Date start, end;

            std::cout << "Ввод параметров записи." << std::endl << std::endl << "Канал: ";
            std::cin >> channel;
            while (std::cin.peek() != '\n')
                channel = channel + (char)std::cin.get();
            std::cout << "Программа: ";
            std::cin >> program;
            while (std::cin.peek() != '\n')
                program = program + (char)std::cin.get();
            std::cout << "Дата начала: ";
            std::cin >> strStartDate;
            while (!start.setDate(strStartDate)) {
                system("clear");
                std::cout << "Дата введена не корректно. Используйте формат ДД.ММ.ГГГГ" << std::endl << std::endl;
                std::cout << "Канал: " << channel << "\nПрограмма: " << program << std::endl;
                std::cout << "Дата начала: ";
                std::cin >> strStartDate;
            }
            std::cout << "Время начала: ";
            std::cin >> strStartTime;
            while (!start.setTime(strStartTime)) {
                system("clear");
                std::cout << "Время введено не корректно. Используйте формат ЧЧ:ММ" << std::endl << std::endl;
                std::cout << "Канал: " << channel << "\nПрограмма: " << program << "\nДата начала: " << strStartDate << std::endl;
                std::cout << "Время начала: ";
                std::cin >> strStartTime;
            }
            system("clear");

            tvProgram.add(channel, program, start);
            std::cout << "Запись успешно добавлена" << std::endl << std::endl;
            if (tvProgram.isSortedChannel()) tvProgram.sortChannel();
            else if (tvProgram.isSortedProgram()) tvProgram.sortProgram();
            else if (tvProgram.isSortedTime()) tvProgram.sortTime();
            tvProgram.save();
            key = -1;
            break;
        }
        case 5: {
            system("clear");
            if (tvProgram.isEmpty()) {
                std::cout << "Список телепрограмм пуст." << std::endl << std::endl;
                key = -1;
                break;
            }
            while (key != -1) {
                key = tvProgram.printIndex();
                if (key == -1) {
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    key = 0;
                    continue;
                }

                if (key == 0) {
                    system("clear");
                    key = -1;
                    break;
                }

                if ((key > 0) && (key <= tvProgram.size())) {
                    system("clear");
                    Telecast tmp = tvProgram.get(key - 1);
                    int number = key;
                    key = -1;
                    while (key == -1) {
                        std::cout << "Выберите параметр, который необходимо изменить:" << std::endl << std::endl
                            << "[1] Канал: " << tmp.channel << std::endl 
                            << "[2] Программа: " << tmp.program << std::endl 
                            << "[3] Время начала: " << tmp.startTime.getTime() << std::endl 
                            << "[4] Дата начала: " << tmp.startTime.getDate() << std::endl << std::endl 
                            << "[0] В главное меню"  << std::endl << std::endl << ">>> ";

                        std::cin >> key;

                        if (std::cin.get() != '\n') {
                            std::cin.clear();
                            while (std::cin.get() != '\n');
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                            key = -1;
                            continue;
                        }

                        if (key == 0) {
                            system("clear");
                            key = -1;
                            break;
                        }

                        if ((key > 0) && (key <= 4)) {
                            system("clear");
                            std::string strBuffer;
                            std::cout << "Ввведите новое значение параметра ";
                            if (key == 1) {
                                std::cout << "\"Канал\":" << std::endl << std::endl << ">>> ";
                                std::cin >> strBuffer;
                                while (std::cin.peek() != '\n')
                                    strBuffer = strBuffer + (char)std::cin.get();
                                tvProgram.setChannel(number - 1, strBuffer);                                
                            }
                            else if (key == 2) {
                                std::cout << "\"Программа\":" << std::endl << std::endl << ">>> ";
                                std::cin >> strBuffer;
                                while (std::cin.peek() != '\n')
                                    strBuffer = strBuffer + (char)std::cin.get();
                                tvProgram.setProgram(number - 1, strBuffer);
                            }
                            else if (key == 3) {
                                std::cout << "\"Время начала\":" << std::endl << std::endl << ">>> ";
                                std::cin >> strBuffer;
                                Date startTime;
                                while (!startTime.setTime(strBuffer)) {
                                    system("clear");
                                    std::cout << "Время введено не корректно. Используйте формат ЧЧ:ММ" << std::endl << std::endl
                                        << "Ввведите новое значение па раметра " << std::endl << "\"Время начала\":" << std::endl << std::endl << ">>> ";
                                    std::cin >> strBuffer;
                                }
                                startTime.setDate(tvProgram.get(number - 1).startTime.getDate());
                                tvProgram.setStartTime(number - 1 , startTime);
                             }

                            else {
                                std::cout << "\"Дата начала\":" << std::endl << std::endl << ">>> ";
                                std::cin >> strBuffer;
                                Date startTime;
                                while (!startTime.setDate(strBuffer)) {
                                    system("clear");
                                    std::cout << "Дата введена не корректно. Используйте формат ДД.ММ.ГГГГ" << std::endl << std::endl
                                        << "Ввведите новое значение параметра " << std::endl << "\"Дата начала\":" << std::endl << std::endl << ">>> ";
                                    std::cin >> strBuffer;
                                }
                                startTime.setTime(tvProgram.get(number - 1).startTime.getTime());
                                tvProgram.setStartTime(number - 1, startTime);
                            }                            
                            system("clear");
                            tvProgram.save();
                            std::cout << "Изменения успешно внесены." << std::endl << std::endl;
                        }
                        else {
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                            key = -1;
                            continue;
                        }
                    }
                    key = -1;
                }
                else {
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    key = 0;
                }               
            }
            key = -1;
            break;
       }
        case 6: {
            system("clear");
            if (tvProgram.isEmpty()) {
                std::cout << "Список телепрограмм пуст." << std::endl << std::endl;
                key = -1;
                break;
            }
            while (key != -1) {
                key = tvProgram.printIndex();
                if (key == -1) {
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    key = 0;
                    continue;
                }

                if (key == 0) {
                    system("clear");
                    key = -1;
                    break;
                }

                if ((key > 0) && (key <= tvProgram.size())) {
                    system("clear");
                    int number = key;
                    key = -1;
                    while (key == -1) {
                        std::cout << "Вы действително желаете удалить выбранную запись?" << std::endl << std::endl
                            << tvProgram.get(number - 1) << std::endl << std::endl
                            << "[1] Да, удалить эту запись" << std::endl 
                            << "[2] Нет, выбрать другую запись" << std::endl << std::endl
                            << "[0] В главное меню"  << std::endl << std::endl << ">>> ";

                        std::cin >> key;
                        if (std::cin.get() != '\n') {
                            std::cin.clear();
                            while (std::cin.get() != '\n');
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                            key = -1;
                            continue;
                        }

                        if (key == 0) {
                            system("clear");
                            key = -1;
                            break;
                        }

                        if (key == 1) {
                            tvProgram.erase(number - 1);
                            system("clear");
                            tvProgram.save();
                            std::cout << "Запись успешно удалена." << std::endl << std::endl;
                            key = -1;
                            break;
                        }
                        else if (key == 2) {
                            system("clear");
                            key = -2;
                            break;
                        }
                        else {
                            system("clear");
                            std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                            key = -1;
                            continue;
                        }
                    }
                }
                else {
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    key = 0;
                }
            }
            key = -1;
            break;
        }
        case 7: {
            system("clear");
            if (tvProgram.isEmpty()) {
                std::cout << "Список телепрограмм пуст." << std::endl << std::endl;
                key = -1;
                break;
            }
            key = -1;

            while (key == -1) {
                std::cout << "Удалить все записи? Я зря всю эту телепрогамму для тебя писал? Ну спасибо." 
                    << std::endl << "Может мы и папку System заодно удалим??" << std::endl << std::endl
                    << "[1] Нет, удалить только все записи" << std::endl 
                    << "[2] Да, удаляй. Буду газетой пользоваться" << std::endl << std::endl
                    << "[0] В главное меню"  << std::endl << std::endl << ">>> ";

                std::cin >> key;
                if (std::cin.get() != '\n') {
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    key = -1;
                    continue;
                }

                if (key == 0) {
                    system("clear");
                    key = -1;
                    break;
                }

                if (key == 1) {
                    tvProgram.clear();
                    system("clear");
                    tvProgram.save();
                    std::cout << "Все записи успешно удалены." << std::endl << std::endl;
                    key = -1;
                    break;
                }
                else if (key == 2) {
                    system("clear");
                    std::cout << "Извини, но газеты уже запрещены)" << std::endl << std::endl;
                    key = -1;
                    break;
                }
                else {
                    system("clear");
                    std::cout << "Ошибка ввода. Введите число повторно." << std::endl;
                    key = -1;
                    continue;
                }
            }
            break;
        }
        default: {
            key = -1;
            system("clear");
            std::cout << "Ошибка ввода. Введите число повторно." << std::endl << std::endl;
            break;
        }
        }
    }
}

int main() {
    startProgram();
    return 1;
}