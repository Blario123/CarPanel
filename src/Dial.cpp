//
// Created by Blair on 02/10/2021.
//

#include <include/DialNeedle.h>
#include "../include/Dial.h"

Dial::Dial(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent), QObject() {
//	setPen(QPen(QBrush(0xC0C0C0), 10));
//	setBrush(QColor(Qt::black));
outer = new DialOuter(this);
needle = new DialNeedle(this);
}

void Dial::setPosition(int x, int y) {
	this->mX = x;
	this->mY = y;
	this->update();
}

QRectF Dial::boundingRect() const {
	return QRectF(0, 0, 100, 100);
}

QPainterPath Dial::shape() const {
	QPainterPath path;
	path.addPath(outer->shape());
	path.addPath(needle->shape());
	path.addEllipse(mX, mY, mRadius, mRadius);
	return path;
}

void Dial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}

Dial::~Dial() = default;
