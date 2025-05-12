//
// Created by matei on 07-Apr-25.
//

#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <string>

class MediaItem {
protected:
    std::string title;
    int duration;
    std::string url;

public:
    MediaItem(std::string title, int duration, std::string url);
    virtual std::string toString() const{
        return title+','+std::to_string(duration)+','+url;
    }
    friend std::ostream &operator<<(std::ostream &out, const MediaItem &item) {
        out<<item.toString();
        return out;
    }

    const std::string &getTitle() const;

    int getDuration() const;

    const std::string &getUrl() const;
};

class Song : public MediaItem {
private:
    std::string artist;

public:
    Song(std::string title, int duration, std::string url, std::string artist);
    std::string toString() const override{
        return "Song"+','+MediaItem::toString()+','+artist+",NA,NA";
    }
};

class Movie : public MediaItem {
private:
    std::string director;
    int numberOfActors;
public:
    Movie(std::string title, int duration, std::string url, std::string director, int numberOfActors);
    std::string toString() const override {
        return "Movie"+','+MediaItem::toString()+",NA,"+std::to_string(numberOfActors)+','+director;
    }
};

#endif //MEDIAITEM_H
