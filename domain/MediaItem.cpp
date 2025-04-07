//
// Created by matei on 07-Apr-25.
//

#include "MediaItem.h"

MediaItem::MediaItem(std::string title, int duration, std::string url) : title(title), duration(duration), url(url) {}

Song::Song(std::string title, int duration, std::string url, std::string artist) :MediaItem(title, duration, url), artist(artist) {}

Movie::Movie(std::string title, int duration, std::string url, std::string director, int numberOfActors) : MediaItem(title, duration, url), director(director), numberOfActors(numberOfActors) {}

