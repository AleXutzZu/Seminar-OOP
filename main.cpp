#include <fstream>
#include <iostream>
#include "repo/MediaItemRepo.h"
#include "service/MediaItemService.h"

int main() {
    FileRepo repo("../media_entries.csv");
    repo.load();

    MediaItemService service(repo);


    return 0;
}