//
// Created by Blair on 07/10/2021.
//

#include <iostream>
#include "include/DialOuter.h"

DialOuter::DialOuter(double dx, double dy, QWidget *parent) : QWidget(parent) {
	this->x = dx;
	this->y = dy;
}

DialOuter::~DialOuter() = default;

void DialOuter::paintEvent(QPaintEvent *event) {
	QPoint center(this->x + (radius/2), this->y + (radius/2));
	
	QPainter increments(this);
	
	increments.setRenderHint(QPainter::Antialiasing);

	increments.setPen(QPen(QBrush(Qt::white), 5));
	increments.setBrush(Qt::white);
	increments.drawPoint(center);
}

void DialOuter::setMajorIncrements(int maj) {
	
	this->update();
}

void DialOuter::setMinorIncrements(int min) {
	
	this->update();
}
