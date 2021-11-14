//
// Created by Blair on 21/10/2021.
//

#include "include/DialNeedle.h"

DialNeedle::DialNeedle(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	center.setX(0);
	center.setY(0);
}

DialNeedle::~DialNeedle() = default;

void DialNeedle::setSpeed(int speed) {
	this->angle = speed;
}

void DialNeedle::setRadius(int radius) {
	this->needleRadius = radius;
}

QRectF DialNeedle::boundingRect() const {
	return QRectF();
}

QPainterPath DialNeedle::shape() const {
	QPainterPath path;
	path.lineTo(needleRadius * sin(qDegreesToRadians(angle)), needleRadius * -cos(qDegreesToRadians(angle)));
	path.translate(center.x(), center.y());
	return path;
}

void DialNeedle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

