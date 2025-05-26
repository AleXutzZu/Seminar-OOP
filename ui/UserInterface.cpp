//
// Created by AleXutzZu on 12/05/2025.
//

#include <QVBoxLayout>
#include <QFormLayout>
#include "UserInterface.h"

UserInterface::UserInterface(MediaItemService &srv, QWidget *parent) : QWidget(parent), service(srv) {
    initUI();
    connect(addButton, &QPushButton::clicked, this, &UserInterface::addItem);
}

void UserInterface::initUI() {
    // Initialize UI components
    addButton = new QPushButton("Add Item", this);

    removeButton = new QPushButton("Remove Item", this);
    sortButton = new QPushButton("Sort Items", this);
    title = new QLineEdit(this);
    duration = new QLineEdit(this);
    url = new QLineEdit(this);
    artist = new QLineEdit(this);
    director = new QLineEdit(this);
    numberOfActors = new QLineEdit(this);
    type = new QComboBox(this);
    type->addItem("Song");
    type->addItem("Movie");
    table = new QTableWidget(10,5, this);

//    QStringList header;
//    header << "Type" << "Title" << "Duration" << "URL" << "Artist/Director/Actors";

//    table->setHorizontalHeaderLabels(header);
    // Layout setup

    //Make a nice form layout for the fields
    //Below the QTableWidget
    //And below a horizontal layout with the buttons

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Title:", title);
    formLayout->addRow("Duration:", duration);
    formLayout->addRow("URL:", url);
    formLayout->addRow("Artist:", artist);
    formLayout->addRow("Director:", director);
    formLayout->addRow("Number of Actors:", numberOfActors);
    formLayout->addRow("Type:", type);


    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(table);


    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(sortButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(Qt::AlignTop);

    setLayout(mainLayout);
}

void UserInterface::addItem() {
    QString t = type->currentText();
    std::string titleText = title->text().toStdString();
    int durationValue = duration->text().toInt();
    std::string urlText = url->text().toStdString();
    if (t == "Song") {
        std::string artistText = artist->text().toStdString();
        service.addSong(titleText, durationValue, urlText, artistText);

        QTableWidgetItem *typeItem = new QTableWidgetItem(t);
        QTableWidgetItem *titleItem = new QTableWidgetItem(QString::fromStdString(titleText));
        QTableWidgetItem *durationItem = new QTableWidgetItem(QString::number(durationValue));
        QTableWidgetItem *urlItem = new QTableWidgetItem(QString::fromStdString(urlText));
        QTableWidgetItem *artistItem = new QTableWidgetItem(QString::fromStdString(artistText));

        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        table->setItem(rowCount, 0, typeItem);
        table->setItem(rowCount, 1, titleItem);
        table->setItem(rowCount, 2, durationItem);
        table->setItem(rowCount, 3, urlItem);
        table->setItem(rowCount, 4, artistItem);

    } else if (t == "Movie") {
        std::string directorText = director->text().toStdString();
        int numberOfActorsValue = numberOfActors->text().toInt();
        service.addMovie(titleText, durationValue, urlText, directorText, numberOfActorsValue);
    }
}
