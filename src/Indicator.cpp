#include <QPainter>
#include <QPainterPath>
#include "../include/Indicator.h"

Indicator::Indicator(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {}

void Indicator::toggle() {
	if(mState) {
		mState = false;
	} else {
		mState = true;
	}
	update();
}

QPainterPath Indicator::shape() const {
	QPainterPath path;
	QPolygonF poly;
	QPointF origin(mX + (mSize / 2), mY + (mSize / 2));
	poly << QPointF(origin.x(), origin.y() + mSize / 2)
			<< QPointF(origin.x() + 30, origin.y())
			<< QPointF(origin.x() + 30, origin.y() + 12)
			<< QPointF(origin.x() + mSize, origin.y() + 12)
			<< QPointF(origin.x() + mSize, origin.y() + 52)
			<< QPointF(origin.x() + 30, origin.y() + 52)
			<< QPointF(origin.x() + 30, origin.y() + mSize)
			<< QPointF(origin.x(), origin.y() + (mSize / 2));
	
	poly = QTransform().translate(origin.x(), origin.y()).rotate(mOrientation).translate(-origin.x(), -origin.y()).map(poly);
	if(mOrientation > 0)  {
		poly.translate(0, mSize);
	}
	path.addPolygon(poly);
	return path;
}

void Indicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(QBrush((mState) ? 0x00ff00 : 0x101010));
	painter->drawPath(shape());
}

void Indicator::setPosition(qreal x, qreal y) {
	mX = x;
	mY = y;
	update();
}

void Indicator::toggleOrientation() {
	if(mOrientation == 0) {
		mOrientation = 180;
	}
}
