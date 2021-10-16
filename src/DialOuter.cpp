//
// Created by Blair on 07/10/2021.
//

#include <iostream>
#include "include/DialOuter.h"

double majAngle, minAngle;

DialOuter::DialOuter(int dx, int dy, QWidget *parent) : QWidget(parent) {
	this->x = dx;
	this->y = dy;
	center = new QPoint(dx + radius, dy + radius);
	setContentsMargins(0, 0, 0 ,0);
}

DialOuter::~DialOuter() = default;

void DialOuter::paintEvent(QPaintEvent *event) {
	QPainter increments(this);
	
	increment.addEllipse(0, 0, 5, 5);
	
	increments.setRenderHint(QPainter::Antialiasing);

	increments.setPen(QPen(QBrush(Qt::white), 3));
	increments.setBrush(Qt::white);
	increments.translate(center->x(), center->y());
	increments.drawPath(increment);
	increments.drawPath(increment);
}

void DialOuter::setIncrements(int maj, int min) {
	double dA = 360 - (startAngle - endAngle);
	double dAMaj = dA/(maj-1);
	double dAMin = dAMaj/(min+1);
	for (int i = 0; i != maj; i++) {
		majAngle = startAngle + (i * dAMaj);
		increment.moveTo(outerRadius * sin(toDeg(majAngle)), outerRadius * -cos(toDeg(majAngle)));
		increment.lineTo(majorRadius * sin(toDeg(majAngle)), majorRadius * -cos(toDeg(majAngle)));
		if (i != maj-1) {
			for (int j = 1; j < min + 1; j++) {
				minAngle = majAngle + (j * dAMin);
				increment.moveTo(outerRadius * sin(toDeg(minAngle)), outerRadius * -cos(toDeg(minAngle)));
				increment.lineTo(minorRadius * sin(toDeg(minAngle)), minorRadius * -cos(toDeg(minAngle)));
			}
		}
	}
	this->repaint();
}

double DialOuter::toDeg(double angle) {
	double rA = angle*(M_PI/180);
	return rA;
}
