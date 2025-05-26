//
// Created by matei on 07-Apr-25.
//

#include "MediaItemRepo.h"
#include <sstream>
#include <iostream>
#include <algorithm>

void MediaItemRepo::add(const std::shared_ptr<MediaItem> &item) {
    auto iterator = std::find_if(items.begin(), items.end(),
                                 [item](const std::shared_ptr<MediaItem> &value) -> bool {
                                     return value->getTitle() == item->getTitle();
                                 });
    if (iterator != items.end()) throw std::invalid_argument("MediaItem already exists: " + item->getTitle());
    items.push_back(item);
}


std::shared_ptr<MediaItem> MediaItemRepo::remove(std::string title) {
    auto iterator = std::find_if(items.begin(), items.end(),
                                 [title](const std::shared_ptr<MediaItem> &value) -> bool {
                                     return value->getTitle() == title;
                                 });

    if (iterator == items.end()) throw std::invalid_argument("MediaItem not found: " + title);

    std::shared_ptr<MediaItem> ptr = *iterator;
    items.erase(iterator);
    return ptr;
}

const std::vector<std::shared_ptr<MediaItem>> &MediaItemRepo::getItems() const {
    return items;
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
                items.push_back(std::shared_ptr<Song>(song));
                std::cout << "Created song!" << '\n';
            } else {
                auto movie = std::make_shared<Movie>(tokens[1], computeDuration(tokens[2]),
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
