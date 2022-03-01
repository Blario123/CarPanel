//
// Created by Blair on 02/10/2021.
//

#include "../include/Dial.h"

//<editor-fold desc="Dial">
Dial::Dial(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent), QObject(), mx(0), my(0) {
	outer = new DialOuter(this);
	needle = new DialNeedle(this);
	increments = new DialIncrements(this);
	connect(this, SIGNAL(positionChanged(qreal,qreal)), outer, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), needle, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), increments, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(incrementsChanged(qreal,qreal)), increments, SLOT(setIncrements(qreal,qreal)));
}

void Dial::setPosition(qreal x, qreal y) {
	emit positionChanged(x, y);
}

void Dial::setIncrements(qreal major, qreal minor) {
	emit incrementsChanged(major, minor);
}

QRectF Dial::boundingRect() const {
	return {};
}

QPainterPath Dial::shape() const {
//	QPainterPath path;
//	path.addEllipse(mx, my, mradius * 2, mradius * 2);
//	path.translate(-mradius, -mradius);
	return QGraphicsItem::shape();
}

void Dial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

void Dial::setRev(qreal value) {
	emit valueChanged(value);
}

Dial::~Dial() = default;
//</editor-fold>

//<editor-fold desc="DialOuter">
DialOuter::DialOuter(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent), QObject(), mx(0), my(0) {

}

DialOuter::~DialOuter() = default;

QRectF DialOuter::boundingRect() const {
	return {};
}

QPainterPath DialOuter::shape() const {
	QPainterPath path;
	path.addEllipse(mx, my, radius * 2, radius * 2);
	path.translate(-radius, -radius);
	return path;
}

void DialOuter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	qDebug() << "paint";
	painter->setPen(QPen(QBrush(0xc0c0c0), 3));
	painter->drawPath(shape());
}

void DialOuter::setRadius(qreal r) {
	radius = r;
	this->update();
}

void DialOuter::setPosition(qreal x, qreal y) {
	this->mx = x;
	this->my = y;
}
//</editor-fold>

//<editor-fold desc="DialText">
DialText::DialText(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent), QObject() {

}

DialText::~DialText() = default;

QRectF DialText::boundingRect() const {
	return {};
}

QPainterPath DialText::shape() const {
	return QGraphicsItem::shape();
}

void DialText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}
//</editor-fold>

//<editor-fold desc="DialIncrements">
DialIncrements::DialIncrements(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent), QObject(), mx(0), my(0) {

}

DialIncrements::~DialIncrements() = default;

QRectF DialIncrements::boundingRect() const {
	return {};
}

QPainterPath DialIncrements::shape() const {
	return QGraphicsItem::shape();
}

void DialIncrements::setPosition(qreal x, qreal y) {
	this->mx = x;
	this->my = y;
}

void DialIncrements::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

void DialIncrements::setIncrements(qreal major, qreal minor) {

}
//</editor-fold>

//<editor-fold desc="DialNeedle">
DialNeedle::DialNeedle(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent), QObject(), mx(0), my(0) {

}

DialNeedle::~DialNeedle() = default;

QRectF DialNeedle::boundingRect() const {
	return {};
}

QPainterPath DialNeedle::shape() const {
	QPainterPath path;
	path.lineTo(mradius * sin(qDegreesToRadians((mangle/100)-130)), mradius * -cos(qDegreesToRadians((mangle/100)-130)));
	path.translate(mx, my);
	return path;
}

void DialNeedle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(Qt::white);
	painter->setPen(Qt::white);
	painter->drawPath(shape());
}

void DialNeedle::setPosition(qreal x, qreal y) {
	this->mx = x;
	this->my = y;
}

void DialNeedle::setAngle(qreal angle) {
	this->mangle = angle;
	update();
}
//</editor-fold>
