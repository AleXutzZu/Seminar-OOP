//
// Created by AleXutzZu on 12/05/2025.
//

#ifndef SEMINAR_OOP_MEDIAITEMSERVICE_H
#define SEMINAR_OOP_MEDIAITEMSERVICE_H

#include "../repo/MediaItemRepo.h"
#include <stack>

class UndoAction;

class MediaItemService {
private:
    MediaItemRepo &repository;
    std::stack<std::unique_ptr<UndoAction>> operations;
public:
    MediaItemService(MediaItemRepo &repo);

    MediaItemService(const MediaItemService &other) = delete;

    MediaItemService &operator=(const MediaItemService &other) = delete;

    void addSong(std::string title, int duration, std::string url, std::string artist);

    void addMovie(std::string title, int duration, std::string url, std::string director, int numberOfActors);

    const std::vector<std::shared_ptr<MediaItem>> &getAllMediaItems() const;

    std::vector<std::shared_ptr<MediaItem>> getAllSortedByArtist() const;

    std::vector<std::shared_ptr<MediaItem>> getAllSortedByDuration() const;

    void remove(std::string title);

    void undo();

    ~MediaItemService() = default;
};


class UndoAction {
protected:
    std::shared_ptr<MediaItem> item;
    MediaItemRepo &repository;

public:
    UndoAction(std::shared_ptr<MediaItem> item, MediaItemRepo &repo) : repository(repo), item(item) {}

    virtual void executeUndo() = 0;

    virtual ~UndoAction() = default;

    const std::shared_ptr<MediaItem> &getItem() const {
        return item;
    }
};

class UndoAdd : public UndoAction {
public:
    UndoAdd(std::shared_ptr<MediaItem> item, MediaItemRepo &repo) : UndoAction(item, repo) {}

    void executeUndo() override {
        repository.remove(item->getTitle());
    }
};

class UndoRemove : public UndoAction {
public:
    UndoRemove(std::shared_ptr<MediaItem> item, MediaItemRepo &repo) : UndoAction(item, repo) {}

    void executeUndo() override {
        repository.add(item);
    }
};

#endif //SEMINAR_OOP_MEDIAITEMSERVICE_H
