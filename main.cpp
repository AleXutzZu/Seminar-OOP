#include "repo/MediaItemRepo.h"
#include "service/MediaItemService.h"
#include "ui/UserInterface.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    FileRepo repo("../media_entries.csv");
    repo.load();

    MediaItemService service(repo);
    QApplication app(argc, argv);

    UserInterface ui(service);
    ui.setMinimumSize({640, 480});
    ui.show();
    return app.exec();
}