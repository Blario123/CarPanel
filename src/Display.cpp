//
// Created by Blair on 01/10/2021.
//

#include "../include/Display.h"

//<editor-fold desc="Display">
DisplayMain::DisplayMain(QGraphicsItem *parent) : QObject(), QGraphicsItem(parent) {
	logo = new DisplayLogo(this);
	border = new DisplayBorder(this);
	text = new DisplayText(this);
	time = new DisplayTime(this);
	
	text->setZValue(1);
	
	auto *timer = new QTimer(this);
	
	connect(timer, &QTimer::timeout, logo, &DisplayLogo::hideLogo);
	connect(timer, &QTimer::timeout, text, &DisplayText::showText);
	connect(timer, &QTimer::timeout, border, &DisplayBorder::showBorder);
	connect(timer, &QTimer::timeout, time, &DisplayTime::showTime);
	
	connect(this, SIGNAL(positionChanged(qreal,qreal)), border, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), logo, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), text, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), time, SLOT(setPosition(qreal,qreal)));
	
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
	QFont f("Dubai", QFont::Bold);
	QPointF tempPoint;
	switch(page) {
		case 0:
			displayData->title = "";
			displayData->value = QString::number(round(mSpeed/100));
			displayData->unit = "mph";
			displayData->rangeText = "";
			break;
		case 1:
			displayData->title = "Warning at";
			displayData->value = "---";
			displayData->unit = "mph";
			displayData->rangeText = "";
			break;
		case 2:
			displayData->title = "Oil Temperature";
			displayData->value = QString::number(mOilTemp);
			displayData->unit = "°C";
			displayData->rangeText = "";
			break;
		case 3:
			displayData->title = "Consumption";
			displayData->value = QString::number(mConsumption);
			displayData->unit = "mpg";
			displayData->rangeText = "";
			break;
		case 4:
			displayData->title = "Avg. Consumption";
			displayData->value = QString::number(mConsumptionArr[mValueRange]);
			displayData->unit = "mpg";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		case 5:
			displayData->title = "Range";
			displayData->value = QString::number(mRange);
			displayData->unit = "mi";
			displayData->rangeText = "";
			break;
		case 6:
			displayData->title = "Travelling Time";
			displayData->value = QString::number(mTimeArr[mValueRange]);
			displayData->unit = "hr";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		case 7:
			displayData->title = "Distance";
			displayData->value = QString::number(mDistanceArr[mValueRange]);
			displayData->unit = "mi";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		case 8:
			displayData->title = "Average Speed";
			displayData->value = QString::number(mSpeedArr[mValueRange]);
			displayData->unit = "mph";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		default:
			displayData->title = "";
			displayData->value = "";
			displayData->unit = "";
			displayData->rangeText = "";
			break;
	}
	path.addPath(addText(tempPath, f, 16, 150, 85, displayData->title, true));
	path.addPath(addText(tempPath, f, 55, 190, 250, displayData->value, false));
	path.addPath(addTextNoTranslate(tempPath, f, 15, 200, 250, displayData->unit));
	path.addPath(addTextNoTranslate(tempPath, f, 15, 25, 350, displayData->rangeText));
	path.translate(mX, mY);
	return path;
}

QPainterPath DisplayText::addText(QPainterPath path, QFont f, int pt, qreal x, qreal y, const QString& t, bool o) {
	f.setPointSize(pt);
	path.addText(x, y, f, t);
	path.translate(o?-path.boundingRect().width()/2:-path.boundingRect().width(), 0);
	return path;
}

QPainterPath DisplayText::addTextNoTranslate(QPainterPath path, QFont f, int pt, qreal x, qreal y, const QString& t) {
	f.setPointSize(pt);
	path.addText(x, y, f, t);
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

void DisplayText::setPage(int p) {
	this->page = p;
	update();
}

void DisplayText::setValueRange(int vr) {
	this->mValueRange = vr;
	update();
}

//</editor-fold>

//<editor-fold desc="DisplayTime">
DisplayTime::DisplayTime(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	hide();
	time = QTime::currentTime();
	auto *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &DisplayTime::updateTime);
	timer->start(1000);
}

void DisplayTime::updateTime() {
	time = QTime::currentTime();
	if(time.minute() != oldTime) {
		oldTime = time.minute();
		update();
	}
}

QPainterPath DisplayTime::shape() const {
	QPainterPath path;
	path.addText(225, 30, QFont("Dubai", 15, QFont::DemiBold), time.toString("HH:mm"));
	path.translate(mX, mY);
	return path;
}

void DisplayTime::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen(Qt::white);
	painter->setBrush(Qt::white);
	painter->drawPath(shape());
}

void DisplayTime::showTime() {
	show();
}

void DisplayTime::hideTime() {
	hide();
}

void DisplayTime::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}
//</editor-fold>
