//
// Created by AleXutzZu on 12/05/2025.
//

#include "MediaItemService.h"
#include <iostream>
#include <algorithm>

MediaItemService::MediaItemService(MediaItemRepo &repo) : repository(repo) {}

void MediaItemService::addSong(std::string title, int duration, std::string url, std::string artist) {
    std::shared_ptr<Song> song = std::make_shared<Song>(title, duration, url, artist);

    try {
        repository.add(song);
        UndoAdd *undoOp = new UndoAdd(song, repository);

        operations.emplace(undoOp);

    } catch (std::invalid_argument &e) {
        //TODO : Change later to log files
        std::cerr << "Error: " << e.what() << '\n';
        throw;
    }
}

void
MediaItemService::addMovie(std::string title, int duration, std::string url, std::string director, int numberOfActors) {
    auto movie = std::make_shared<Movie>(title, duration, url, director, numberOfActors);
    try {
        repository.add(movie);
        auto undoOp = std::make_unique<UndoAdd>(movie, repository);
        operations.push(std::move(undoOp));
    } catch (std::invalid_argument &e) {
        //TODO : Change later to log files
        std::cerr << "Error: " << e.what() << '\n';
        throw;
    }
}

const std::vector<std::shared_ptr<MediaItem>> &MediaItemService::getAllMediaItems() const {
    return repository.getItems();
}

std::vector<std::shared_ptr<MediaItem>> MediaItemService::getAllSortedByArtist() const {
    std::vector<std::shared_ptr<MediaItem>> items = repository.getItems();

    std::sort(items.begin(), items.end(),
              [](const std::shared_ptr<MediaItem> &lhs, const std::shared_ptr<MediaItem> &rhs) -> bool {
                  try {
                      Song &lhs_song = dynamic_cast<Song &>(*lhs);
                      Song &rhs_song = dynamic_cast<Song &>(*rhs);
                      return lhs_song.getArtist() < rhs_song.getArtist();
                  } catch (const std::bad_cast &e) {}

                  try {
                      Song &lhs_song = dynamic_cast<Song &>(*lhs);
                      Movie &rhs_movie = dynamic_cast<Movie &>(*rhs);
                      return lhs_song.getArtist() < rhs_movie.getDirector();
                  } catch (const std::bad_cast &e) {}

                  try {
                      Movie &lhs_movie = dynamic_cast<Movie &>(*lhs);
                      Song &rhs_song = dynamic_cast<Song &>(*rhs);
                      return lhs_movie.getDirector() < rhs_song.getArtist();
                  } catch (const std::bad_cast &e) {}

                  try {
                      Movie &lhs_movie = dynamic_cast<Movie &>(*lhs);
                      Movie &rhs_movie = dynamic_cast<Movie &>(*rhs);
                      return lhs_movie.getDirector() < rhs_movie.getDirector();
                  } catch (const std::bad_cast &e) {}

                  return true;
              });

    return items;
}

std::vector<std::shared_ptr<MediaItem>> MediaItemService::getAllSortedByDuration() const {
    std::vector<std::shared_ptr<MediaItem>> items = repository.getItems();

    std::sort(items.begin(), items.end(),
              [](const std::shared_ptr<MediaItem> &lhs, const std::shared_ptr<MediaItem> &rhs) -> bool {
                  return lhs->getDuration() < rhs->getDuration();
              });

    return items;
}

void MediaItemService::remove(std::string title) {
    try {
        std::shared_ptr<MediaItem> deleted = repository.remove(title);
        auto undoOp = std::make_unique<UndoRemove>(deleted, repository);
        operations.push(std::move(undoOp));
    } catch (std::invalid_argument &e) {
        //TODO : Change later to log files
        std::cerr << "Error: " << e.what() << '\n';
        throw;
    }
}

void MediaItemService::undo() {
    if (operations.empty()) throw std::runtime_error("Cannot undo operations");

    operations.top()->executeUndo();
    operations.pop();
}