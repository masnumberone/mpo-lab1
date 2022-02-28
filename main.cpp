#include "schedule.h"
#include <iostream>

int main() {
    Schedule tvProgramm;
    tvProgramm.add("1", "news", Date(1990, 10, 1, 12, 0), Date());
    tvProgramm.add("1", "whether", Date(1990, 10, 1, 12, 25), Date());
    tvProgramm.load();
    std::cout << tvProgramm.get(0);
    std::cout << tvProgramm.get(1);
    
    
    return 1;
}