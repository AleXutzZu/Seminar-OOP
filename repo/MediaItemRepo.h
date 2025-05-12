//
// Created by matei on 07-Apr-25.
//

#ifndef MEDIAITEMREPO_H
#define MEDIAITEMREPO_H


#include "../domain/MediaItem.h"
#include <vector>
#include <fstream>

class MediaItemRepo {
protected:
    std::vector<MediaItem *> items;
public:
    void add(MediaItem *);
    void remove(MediaItem *);

    virtual ~MediaItemRepo();

    MediaItemRepo &operator=(const MediaItemRepo &other) = delete;

    MediaItemRepo(const MediaItemRepo &other) = delete;

    MediaItemRepo() = default;
};

class FileRepo : public MediaItemRepo {
private:
    std::string file_path;

    static std::vector<std::string> tokenize(std::string line);

    static unsigned int computeDuration(const std::string &str);

public:
    FileRepo(std::string file_path) : file_path(file_path) {};

    bool save() {
        std::ofstream of(file_path);
        if (!of.is_open()) {
            return false;
        }
        of << "type, title, duration, url, artist, director, numberOfActors";
        for (MediaItem *i: items) {
            of << *i << '\n';
        }
        return true;
    }

    bool load();
};


#endif //MEDIAITEMREPO_H
