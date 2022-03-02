//
// Created by Blair on 02/10/2021.
//

#include "../include/Speedometer.h"

Speedometer::Speedometer(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	dial = new Dial(this);
	dial->setPosition(1275, 375);
	
//	dial->outer->setTextRadius(250);
//
//
//	dial->outer->setIncrements(8.5,3);
//	dial->outer->setText(9, {"0", "20", "40", "60", "80", "100", "120", "140"}, 15);
//
//	kmDial->setIncrements(13, 3);
//	kmDial->setText(13, {"0", "20", "40", "60", "80", "100", "120", "140", "160", "180", "200", "220", "240"}, 12);
//	kmDial->setRadius(450);
//	kmDial->setOuterRadius(500);
//	kmDial->setTextRadius(510);
//	kmDial->setCenter(QPointF(1250, 100));
}

Speedometer::~Speedometer() = default;

QRectF Speedometer::boundingRect() const {
	return QRectF();
}

QPainterPath Speedometer::shape() const {
	return QGraphicsItem::shape();
}

void Speedometer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

void Speedometer::setSpeed(qreal value) {
	dial->setAngle(value);
}
