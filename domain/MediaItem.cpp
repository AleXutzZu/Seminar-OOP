//
// Created by matei on 07-Apr-25.
//

#include "MediaItem.h"

MediaItem::MediaItem(std::string title, int duration, std::string url) : title(title), duration(duration), url(url) {}

const std::string &MediaItem::getTitle() const {
    return title;
}

int MediaItem::getDuration() const {
    return duration;
}

const std::string &MediaItem::getUrl() const {
    return url;
}

Song::Song(std::string title, int duration, std::string url, std::string artist) :MediaItem(title, duration, url), artist(artist) {}

const std::string &Song::getArtist() const {
    return artist;
}

Movie::Movie(std::string title, int duration, std::string url, std::string director, int numberOfActors) : MediaItem(title, duration, url), director(director), numberOfActors(numberOfActors) {}

const std::string &Movie::getDirector() const {
    return director;
}

int Movie::getNumberOfActors() const {
    return numberOfActors;
}

