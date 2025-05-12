//
// Created by AleXutzZu on 12/05/2025.
//

#ifndef SEMINAR_OOP_USERINTERFACE_H
#define SEMINAR_OOP_USERINTERFACE_H

#include "../service/MediaItemService.h"
#include <iostream>
#include <numeric>

class UserInterface {
private:
    MediaItemService &service;

public:
    UserInterface(MediaItemService &srv);

    template<typename T>
    T parseInput(const std::string &input);
};

template<typename T>
T UserInterface::parseInput(const std::string &input) {
    T result;
    while (true) {
        std::cout << input << '\n';
        std::cin >> result;
        if (std::cin.good()) break;
        std::cout << "Your input is invalid!\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
        std::cin.clear();
    }
    return result;
}


#endif //SEMINAR_OOP_USERINTERFACE_H
