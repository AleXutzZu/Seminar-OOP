//
// Created by AleXutzZu on 12/05/2025.
//

#include "MediaItemService.h"
#include <iostream>
#include <algorithm>

MediaItemService::MediaItemService(MediaItemRepo &repo) : repository(repo) {}

void MediaItemService::addSong(std::string title, int duration, std::string url, std::string artist) {
    Song *song = new Song(title, duration, url, artist);

    try {
        repository.add(song);
        UndoAdd *undoOp = new UndoAdd(song, repository);

        operations.push(undoOp);

    } catch (std::invalid_argument &e) {
        //TODO : Change later to log files
        std::cerr << "Error: " << e.what() << '\n';
        delete song;
        throw;
    }
}

void
MediaItemService::addMovie(std::string title, int duration, std::string url, std::string director, int numberOfActors) {
    Movie *movie = new Movie(title, duration, url, director, numberOfActors);
    try {
        repository.add(movie);
        UndoAdd *undoOp = new UndoAdd(movie, repository);

        operations.push(undoOp);

    } catch (std::invalid_argument &e) {
        //TODO : Change later to log files
        std::cerr << "Error: " << e.what() << '\n';
        delete movie;
        throw;
    }
}

const std::vector<MediaItem *> &MediaItemService::getAllMediaItems() const {
    return repository.getItems();
}

std::vector<MediaItem *> MediaItemService::getAllSortedByArtist() const {
    std::vector<MediaItem *> items = repository.getItems();

    std::sort(items.begin(), items.end(), [](MediaItem *lhs, MediaItem *rhs) -> bool {
        Song *lhs_song = dynamic_cast<Song *>(lhs);
        Movie *lhs_movie = dynamic_cast<Movie *>(lhs);

        Song *rhs_song = dynamic_cast<Song *>(rhs);
        Movie *rhs_movie = dynamic_cast<Movie *>(rhs);

        std::string lhs_string = (lhs_song == nullptr ? lhs_movie->getDirector() : lhs_song->getArtist());
        std::string rhs_string(rhs_song == nullptr ? rhs_movie->getDirector() : rhs_song->getArtist());

        return lhs_string < rhs_string;
    });

    return items;
}

std::vector<MediaItem *> MediaItemService::getAllSortedByDuration() const {
    std::vector<MediaItem *> items = repository.getItems();

    std::sort(items.begin(), items.end(), [](MediaItem *lhs, MediaItem *rhs) -> bool {

        return lhs->getDuration() < rhs->getDuration();
    });

    return items;
}

void MediaItemService::remove(std::string title) {
    try {
        MediaItem *deleted = repository.remove(title);
        UndoRemove *undoOp = new UndoRemove(deleted, repository);
        operations.push(undoOp);
    } catch (std::invalid_argument &e) {
        //TODO : Change later to log files
        std::cerr << "Error: " << e.what() << '\n';
        throw;
    }
}

void MediaItemService::undo() {
    if (operations.empty()) throw std::runtime_error("Cannot undo operations");

    UndoAction *top = operations.top();
    operations.pop();

    top->executeUndo();
    delete top;
}

MediaItemService::~MediaItemService() {
    while (!operations.empty()) {
        UndoAction *top = operations.top();
        operations.pop();

        if (dynamic_cast<UndoRemove *>(top) != nullptr) {
            delete top->getItem();
        }
        delete top;
    }
}
