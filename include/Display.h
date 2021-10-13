//
// Created by Blair on 01/10/2021.
//

#ifndef CARPANEL_DISPLAY_H
#define CARPANEL_DISPLAY_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include "../include/DisplayTop.h"

class Display : public QWidget {
   Q_OBJECT

public:
    explicit Display(QWidget *parent = 0);
    ~Display() override;

private:
	DisplayTop *top;
	QSpacerItem *displaySpacer;
	QSpacerItem *hSpacer;
    QVBoxLayout *vLayout;
	QHBoxLayout *hLayout;
    QLabel *label;
    int setStyle();
};

#endif // CARPANEL_DISPLAY_H
