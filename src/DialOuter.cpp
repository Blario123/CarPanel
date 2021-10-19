//
// Created by Blair on 07/10/2021.
//

#include "include/DialOuter.h"

double majAngle, minAngle, dA, dAMaj, dAMin, textAngle;
double majLoop;
bool lastLine, doLastLine;

DialOuter::DialOuter(int dx, int dy, int majW, int minW, QColor color, int size, QWidget *parent) : QWidget(parent) {
	this->radius = size/2;
	this->x = dx;
	this->y = dy;
	this->outerRadius = this->radius - 50;
	this->textRadius = this->outerRadius + 10;
	this->majorRadius = this->outerRadius - majW;
	this->minorRadius = this->outerRadius - minW;
	this->color = new QColor(color);
	this->center = new QPoint(dx + this->radius, dy + this->radius);
	this->increment = new QPainterPath();
	this->incrementText = new QPainterPath();
	font = new QRawFont(QString(":/resources/CEROM.otf"), 5);
	setContentsMargins(0, 0, 0 ,0);
}

DialOuter::~DialOuter() = default;

void DialOuter::paintEvent(QPaintEvent *event) {
	QPainter increments(this);
	
	increments.setRenderHint(QPainter::Antialiasing);

	increments.translate(center->x(), center->y());
	increments.setPen(QPen(QBrush(*color), 3));
	increments.setBrush(*color);
	increments.drawPath(*increment);
	increments.setPen(QPen(QBrush(*color), 1));
	increments.drawPath(*incrementText);
}

void DialOuter::setIncrements(double maj, int min) {
	if(fmod(maj, 1) != 0) {
		majLoop = maj - fmod(maj, 1);
		doLastLine = false;
	} else {
		majLoop = maj;
		doLastLine = true;
	}
	dA = 360 - (startAngle - endAngle);
	dAMaj = dA/(maj-1);
	dAMin = dAMaj/(min+1);
	for (int i = 0; i < majLoop; i++) {
		majAngle = startAngle + (i * dAMaj);
		increment->moveTo(outerRadius * sin(toDeg(majAngle)), outerRadius * -cos(toDeg(majAngle)));
		increment->lineTo(majorRadius * sin(toDeg(majAngle)), majorRadius * -cos(toDeg(majAngle)));
		for (int j = 1; j < min + 1; j++) {
			if(i != majLoop - 1) {
				minAngle = majAngle + (j * dAMin);
				increment->moveTo(outerRadius * sin(toDeg(minAngle)), outerRadius * -cos(toDeg(minAngle)));
				increment->lineTo(minorRadius * sin(toDeg(minAngle)), minorRadius * -cos(toDeg(minAngle)));
			}
		}
		if(!doLastLine) {
			for (int j = 0; j < 3; ++j) {
				minAngle = majAngle + (j*dAMin);
				increment->moveTo(outerRadius * sin(toDeg(minAngle)), outerRadius * -cos(toDeg(minAngle)));
				increment->lineTo(minorRadius * sin(toDeg(minAngle)), minorRadius * -cos(toDeg(minAngle)));
			}
		}
	}
	this->repaint();
}

void DialOuter::setText(int maj, QList<QString> list, int pt) {
	QList<QPainterPath> pathList;
	QPainterPath tempPath;
	QPoint tempPoint;
	
	for (int i = 0; i < list.size(); i++) {
		majAngle = startAngle + (i * dAMaj);
		tempPoint = QPoint(static_cast <int> (textRadius * sin(toDeg(majAngle))),static_cast <int> (textRadius * -cos(toDeg(majAngle))));
		tempPath.addText(tempPoint, QFont("CEROM", pt), list[i]);
		tempPath.translate(-tempPath.boundingRect().width()/2,0);
		tempPath = QTransform().translate(textRadius * sin(toDeg(majAngle)),textRadius * -cos(toDeg(majAngle)))
							   .rotate(majAngle)
							   .translate(textRadius * -sin(toDeg(majAngle)), textRadius * cos(toDeg(majAngle)))
							   .map(tempPath);
		pathList << tempPath;
		tempPath.clear();
	}
	
	if (!pathList.isEmpty()) {
		for (int i = 0; i < pathList.size(); i++) {
			incrementText->addPath(pathList[i]);
		}
	}
	this->repaint();
}

double DialOuter::toDeg(double angle) {
	double rA = angle*(M_PI/180);
	return rA;
}
