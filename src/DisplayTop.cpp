//
// Created by Blair on 06/10/2021.
//

#include <QFile>
#include "include/DisplayTop.h"

DisplayTop::DisplayTop(QWidget *parent) : QWidget(parent) {
	
	if (setStyle() != 0) {
		qDebug() << "Error opening stylesheet.";
	}
	
	layout = new QHBoxLayout(this);
	time = new QLabel();
	spacer = new QSpacerItem(300, 0);
	
	time->setText("00:00");
	
	layout->addSpacerItem(spacer);
	layout->addWidget(time);
	
	this->setLayout(layout);
}

DisplayTop::~DisplayTop() = default;

void DisplayTop::setTime(QDateTime dateTime) {
	time->setText(dateTime.toUTC().toString(Qt::ISODate));
	update();
}

int DisplayTop::setStyle() {
	QFile file(":/resources/DisplayTop.qss");
	if (file.open(QFile::ReadOnly)) {
		setStyleSheet(QString::fromUtf8(file.readAll()));
		return 0;
	} else {
		return 1;
	}
}
