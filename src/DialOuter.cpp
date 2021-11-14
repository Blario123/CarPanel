//
// Created by Blair on 07/10/2021.
//

#include "include/DialOuter.h"

double majAngle, minAngle, dA, dAMaj, dAMin;
double majLoop;
bool doLastLine;

DialOuter::DialOuter(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	increment = new QPainterPath();
	incrementText = new QPainterPath();
}

DialOuter::~DialOuter() = default;

void DialOuter::setIncrements(double maj, int min) {
	if (fmod(maj, 1) != 0) {
		majLoop = maj - fmod(maj, 1);
		doLastLine = false;
	} else {
		majLoop = maj;
		doLastLine = true;
	}
	dA = 360 - (startAngle - endAngle);
	dAMaj = dA / (maj - 1);
	dAMin = dAMaj / (min + 1);
	for (int i = 0; i < majLoop; i++) {
		majAngle = startAngle + (i * dAMaj);
		increment->moveTo(mOuterRadius * sin(qDegreesToRadians(majAngle)),
						  mOuterRadius * -cos(qDegreesToRadians(majAngle)));
		increment->lineTo(mRadius * sin(qDegreesToRadians(majAngle)),
						  mRadius * -cos(qDegreesToRadians(majAngle)));
		for (int j = 1; j < min + 1; j++) {
			if (i != majLoop - 1) {
				minAngle = majAngle + (j * dAMin);
				increment->moveTo(mOuterRadius * sin(qDegreesToRadians(minAngle)),
								  mOuterRadius * -cos(qDegreesToRadians(minAngle)));
				increment->lineTo(mMinorRadius * sin(qDegreesToRadians(minAngle)),
								  mMinorRadius * -cos(qDegreesToRadians(minAngle)));
			}
		}
		if (!doLastLine) {
			for (int j = 0; j < 3; ++j) {
				minAngle = majAngle + (j * dAMin);
				increment->moveTo(mOuterRadius * sin(qDegreesToRadians(minAngle)),
								  mOuterRadius * -cos(qDegreesToRadians(minAngle)));
				increment->lineTo(mMinorRadius * sin(qDegreesToRadians(minAngle)),
								  mMinorRadius * -cos(qDegreesToRadians(minAngle)));
			}
		}
	}
	this->update();
}

void DialOuter::setText(int maj, QList<QString> list, int pt) {
	QList<QPainterPath> pathList;
	QPainterPath tempPath;
	QPoint tempPoint;
	
	for (int i = 0; i < list.size(); i++) {
		majAngle = startAngle + (i * dAMaj);
		tempPoint = QPoint(static_cast <int> (mTextRadius * sin(qDegreesToRadians(majAngle))),
						   static_cast <int> (mTextRadius * -cos(qDegreesToRadians(majAngle))));
		tempPath.addText(tempPoint, QFont("CEROM", pt), list[i]);
		tempPath.translate(-tempPath.boundingRect().width() / 2, 0);
		tempPath = QTransform().translate(mTextRadius * sin(qDegreesToRadians(majAngle)),
										  mTextRadius * -cos(qDegreesToRadians(majAngle)))
				.rotate(majAngle)
				.translate(mTextRadius * -sin(qDegreesToRadians(majAngle)),
						   mTextRadius * cos(qDegreesToRadians(majAngle)))
				.map(tempPath);
		pathList << tempPath;
		tempPath.clear();
	}
	
	if (!pathList.isEmpty()) {
		for (int i = 0; i < pathList.size(); i++) {
			incrementText->addPath(pathList[i]);
		}
	}
	pathList.clear();
//	incrementText->translate(mX + (mRadius/2), mY + (mRadius/2));
	this->update();
}

void DialOuter::setRadius(int radius) {
	this->mRadius = radius;
	this->update();
}

void DialOuter::setOuterRadius(int radius) {
	this->mOuterRadius = radius;
	this->update();
}

void DialOuter::setInnerRadius(int radius) {
	this->mMinorRadius = radius;
	this->update();
}

void DialOuter::setTextRadius(int radius) {
	this->mTextRadius = radius;
	this->update();
}

void DialOuter::setX(int x) {
	this->mX = x;
	this->update();
}

void DialOuter::setY(int y) {
	this->mY = y;
	this->update();
}

void DialOuter::setCenter(QPointF center) {
	this->mX = center.x();
	this->mY = center.y();
}

void DialOuter::setPosition(int x, int y) {
	this->mX = x;
	this->mY = y;
	this->update();
}

QRectF DialOuter::boundingRect() const {
	return QRectF();
}

QPainterPath DialOuter::shape() const {
	QPainterPath path;
	increment->translate(mX, mY);
	path.addPath(*increment);
	path.addPath(*incrementText);
	return path;
}

void DialOuter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

