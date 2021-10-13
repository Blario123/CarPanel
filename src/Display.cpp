//
// Created by Blair on 01/10/2021.
//

#include "../include/Display.h"

#include <QFile>
#include <QLabel>
#include <QVBoxLayout>

Display::Display(QWidget *parent) : QWidget(parent) {

    if (setStyle() != 0) {
        qDebug() << "Error opening stylesheet.";
    }
	
    vLayout = new QVBoxLayout(this);
	hLayout = new QHBoxLayout();
	
	top = new DisplayTop();
	
	hSpacer = new QSpacerItem(600, 0);
	displaySpacer = new QSpacerItem(0, 100);
//    label = new QLabel("AAA");
	
//    label->setAlignment(Qt::AlignCenter);
	
	hLayout->addSpacerItem(hSpacer);
//	hLayout->addWidget(label);
	hLayout->addWidget(top);
	
	hLayout->addSpacerItem(hSpacer);
	
	vLayout->addSpacerItem(displaySpacer);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->addLayout(hLayout);
}

Display::~Display() { delete label; }

int Display::setStyle() {
    QFile file(":/resources/Display.qss");
    if (file.open(QFile::ReadOnly)) {
        setStyleSheet(QString::fromUtf8(file.readAll()));
        return 0;
    } else {
        return 1;
    }
}


