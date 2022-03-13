//
// Created by Blair on 01/10/2021.
//

#include "../include/Display.h"

//<editor-fold desc="Display">
Display::Display(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent) {
//	hide();
	logo = new DisplayLogo(this);
	border = new DisplayBorder(this);
	text = new DisplayText(this);
	auto *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, border, &DisplayBorder::showBorder);
	connect(timer, &QTimer::timeout, logo, &DisplayLogo::hideLogo);
	
	connect(this, SIGNAL(positionChanged(qreal,qreal)), border, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), logo, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), text, SLOT(setPosition(qreal,qreal)));
	
	timer->start(2000);
}

QRectF Display::boundingRect() const {
	return {};
}

QPainterPath Display::shape() const {
	return {};
}

void Display::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}

Display::~Display() = default;

void Display::setSpeed(qreal speed) {

}

void Display::showDisplay() {
	show();
}
//</editor-fold>

//<editor-fold desc="DisplayText">
DisplayText::DisplayText(QGraphicsItem *parent) : QGraphicsItem(parent) {

}

QRectF DisplayText::boundingRect() const {
	return QRectF();
}

QPainterPath DisplayText::shape() const {
	return QGraphicsItem::shape();
}

void DisplayText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}
//</editor-fold>
