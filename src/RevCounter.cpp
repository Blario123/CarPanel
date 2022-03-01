//
// Created by Blair on 02/10/2021.
//

#include "../include/RevCounter.h"

RevCounter::RevCounter(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	dial = new Dial(this);
	dial->setPosition(325, 375);
//	dial->outer->setIncrements(9, 3);
//	dial->outer->setText(9, {"0", "10", "20", "30", "40", "50", "60", "70", "80"}, 15);
}

QRectF RevCounter::boundingRect() const {
	return QRectF();
}

QPainterPath RevCounter::shape() const {
	return QGraphicsItem::shape();
}

void RevCounter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

RevCounter::~RevCounter() = default;

void RevCounter::setRev(qreal value) {
	dial->setRev(value);
}
