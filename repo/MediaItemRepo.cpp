//
// Created by matei on 07-Apr-25.
//

#include "MediaItemRepo.h"
#include <sstream>
#include <iostream>

void MediaItemRepo::add(MediaItem *item) {
    items.push_back(item);
}

bool FileRepo::load() {
    std::ifstream in(file_path);
    if (!in.is_open()) return false;

    std::string line;

    //Jump over the header
    std::getline(in, line);

    while (std::getline(in, line)) {
        std::vector<std::string> tokens = tokenize(line);

        if (tokens.size() != 7) std::cerr << "Invalid media item: " << line << '\n';
        else {
            if (tokens[0] == "Song") {
                Song *song = new Song(tokens[1], computeDuration(tokens[2]), tokens[3], tokens[4]);
                items.push_back(song);
                std::cout << "Created song!" << '\n';
            } else {
                Movie *movie = new Movie(tokens[1], computeDuration(tokens[2]),
                                         tokens[3], tokens[5],
                                         std::stoi(tokens[6]));
                items.push_back(movie);
                std::cout << "Created movie!" << '\n';
            }
        }
    }
    return true;
}

std::vector<std::string> FileRepo::tokenize(std::string line) {
    std::vector<std::string> tokens;

    std::stringstream stream(line);
    std::string token;
    while (std::getline(stream, token, ',')) {
        tokens.push_back(token);
    }
    return tokens;
}

unsigned int FileRepo::computeDuration(const std::string &str) {
    std::stringstream stream(str);
    unsigned int hours, minutes, seconds;
    stream >> hours;

    if (!stream) throw std::invalid_argument("Invalid format: " + str);

    char delimiter;
    stream >> delimiter;

    if (delimiter != ':') throw std::invalid_argument("Invalid format: " + str);

    stream >> minutes;
    stream >> delimiter;

    if (delimiter != ':') throw std::invalid_argument("Invalid format: " + str);
    stream >> seconds;

    unsigned int result = hours * 60 * 60 + minutes * 60 + seconds;
    return result;
}
