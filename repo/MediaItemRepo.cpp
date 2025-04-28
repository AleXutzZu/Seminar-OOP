//
// Created by matei on 07-Apr-25.
//

#include "MediaItemRepo.h"

void MediaItemRepo::add(MediaItem* item) {
    items.push_back(item);
}

MediaItemRepo::~MediaItemRepo() {
    for (size_t i = 0; i < items.size(); i++) {
        delete items[i];
    }
}
