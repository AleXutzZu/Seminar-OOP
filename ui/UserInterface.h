//
// Created by AleXutzZu on 12/05/2025.
//

#ifndef SEMINAR_OOP_USERINTERFACE_H
#define SEMINAR_OOP_USERINTERFACE_H

#include "../service/MediaItemService.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

class UserInterface : public QWidget {
Q_OBJECT
private:
    MediaItemService &service;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *sortButton;
    QLineEdit *title;
    QLineEdit *duration;
    QLineEdit *url;
    QLineEdit *artist;
    QLineEdit *director;
    QLineEdit *numberOfActors;
    QComboBox *type;
    QTableWidget *table;

    void initUI();

public:
    explicit UserInterface(MediaItemService &srv, QWidget *parent = nullptr);
    public slots:
    void addItem();
};


#endif //SEMINAR_OOP_USERINTERFACE_H
