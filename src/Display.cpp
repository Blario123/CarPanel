//
// Created by Blair on 01/10/2021.
//

#include "../include/Display.h"

//<editor-fold desc="Display">
DisplayMain::DisplayMain(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent) {
	logo = new DisplayLogo(this);
	border = new DisplayBorder(this);
	text = new DisplayText(this);
	
	text->setZValue(1);
	
	auto *timer = new QTimer(this);
	
	connect(timer, &QTimer::timeout, logo, &DisplayLogo::hideLogo);
	connect(timer, &QTimer::timeout, text, &DisplayText::showText);
	connect(timer, &QTimer::timeout, border, &DisplayBorder::showBorder);
	
	connect(this, SIGNAL(positionChanged(qreal,qreal)), border, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), logo, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), text, SLOT(setPosition(qreal,qreal)));
	
	timer->setSingleShot(true);
	timer->start(2000);
}

QPainterPath DisplayMain::shape() const {
	return {};
}

void DisplayMain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
}

void DisplayMain::setPosition(qreal x, qreal y) {
	emit(positionChanged(x, y));
}

void DisplayMain::showDisplay() {
	show();
}
//</editor-fold>

//<editor-fold desc="DisplayText">
QPainterPath DisplayText::shape() const {
	QPainterPath path, tempPath;
	QString value;
	switch(switchValue) {
		case 0:
			value = QString::number(round(mSpeed/100));
		default:
			value = QString::number(round(mSpeed/100));
	}
	//
	tempPath.addText(250, 250, QFont("CEROM", 30), value);
	tempPath.translate(-tempPath.boundingRect().width(), 0);
	path.addPath(tempPath);
	path.translate(mX, mY);
	return path;
}

void DisplayText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen(Qt::white);
	painter->setBrush(Qt::white);
	painter->drawPath(shape());
}

void DisplayText::showText() {
	show();
}

void DisplayText::hideText() {
	hide();
}

void DisplayText::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}

void DisplayText::setSpeed(qreal speed) {
	this->mSpeed = speed;
}
//</editor-fold>
