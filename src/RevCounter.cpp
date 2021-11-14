//
// Created by Blair on 02/10/2021.
//

#include "../include/RevCounter.h"

RevCounter::RevCounter(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	dial = new Dial(this);
//	dial->outer->setIncrements(9, 3);
//	dial->outer->setText(9, {"0", "10", "20", "30", "40", "50", "60", "70", "80"}, 15);
}

QRectF RevCounter::boundingRect() const {
	return QRectF();
}

QPainterPath RevCounter::shape() const {
	QPainterPath path;
	path.addPath(dial->shape());
	return path;
}

void RevCounter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen(Qt::white);
	painter->drawPath(shape());
}

RevCounter::~RevCounter() = default;
