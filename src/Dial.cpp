//
// Created by Blair on 02/10/2021.
//

#include "../include/Dial.h"

#include <utility>

//<editor-fold desc="Dial">
Dial::Dial(QGraphicsItem *parent) : QGraphicsItem(parent), QObject(), mx(0), my(0) {
	outer = new DialOuter(this);
	increments = new DialIncrements(this);
	needle = new DialNeedle(this);
	text = new DialText(this);
	connect(this, SIGNAL(positionChanged(qreal,qreal)), outer, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), needle, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), increments, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(positionChanged(qreal,qreal)), text, SLOT(setPosition(qreal,qreal)));
	connect(this, SIGNAL(incrementsChanged(qreal,qreal)), increments, SLOT(setIncrements(qreal,qreal)));
	connect(this, SIGNAL(incrementsChanged(qreal,qreal)), text, SLOT(setIncrements(qreal,qreal)));
}

void Dial::setPosition(qreal x, qreal y) {
	emit positionChanged(x, y);
	this->mx = x;
	this->my = y;
}

void Dial::setIncrements(qreal major, qreal minor) {
	emit incrementsChanged(major, minor);
}

QRectF Dial::boundingRect() const {
	return {};
}

QPainterPath Dial::shape() const {
	QPainterPath path;
	path.addEllipse(-20, -20, 40, 40);
	path.translate(mx, my);
	return path;
}

void Dial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(QBrush(0x404040));
	painter->setPen(0x404040);
	painter->drawPath(shape());
	QLinearGradient grad;
	grad.setColorAt(0.1, 0xC0C0C0);
	grad.setColorAt(0.4, Qt::black);
	grad.setStart(mx-18, my-18);
	grad.setFinalStop(mx+18, my+18);
	painter->setPen(QPen(grad, 2));
	painter->drawEllipse((int) mx-18, (int) my-18, 36, 36);
}

void Dial::setAngle(qreal value) {
	emit valueChanged(value);
}

Dial::~Dial() = default;
//</editor-fold>

//<editor-fold desc="DialOuter">
DialOuter::DialOuter(QGraphicsItem *parent) : QGraphicsItem(parent), QObject(), mx(0), my(0) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
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
DialText::DialText(QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialText::~DialText() = default;

QRectF DialText::boundingRect() const {
	return {};
}

QPainterPath DialText::shape() const {
	QPainterPath path, tempPath;
	QPointF tempPoint;
	qreal majAngle, dAMaj = 260 / (mText.size() - ((mMajorIncrements == mText.size()) ? 1 : 0.5));
	for(int i = 0; i < mText.size(); i++) {
		majAngle = -130 + (i * dAMaj);
		tempPoint = QPointF(mRadius * sin(qDegreesToRadians(majAngle)), mRadius * -cos(qDegreesToRadians(majAngle)));
		tempPath.addText(tempPoint, QFont("CarPanel", 15), mText[i]);
		tempPath.translate(-tempPath.boundingRect().width() / 2, 0);
		tempPath = QTransform().translate(mRadius * sin(qDegreesToRadians(majAngle)), mRadius * -cos(qDegreesToRadians(majAngle))).rotate(majAngle).translate(mRadius * -sin(qDegreesToRadians(majAngle)), mRadius * cos(qDegreesToRadians(majAngle))).map(tempPath);
		path.addPath(tempPath);
		tempPath.clear();
	}
	path.translate(mX, mY);
	return path;
}

void DialText::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}

void DialText::setText(QList<QString> text) {
	this->mText = text;
}

void DialText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(Qt::white);
	painter->setPen(Qt::white);
	painter->drawPath(shape());
}

void DialText::setIncrements(qreal major, qreal minor) {
	this->mMajorIncrements = major;
}
//</editor-fold>

//<editor-fold desc="DialIncrements">
DialIncrements::DialIncrements(QGraphicsItem *parent) : QGraphicsItem(parent), QObject(), mX(0), mY(0) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialIncrements::~DialIncrements() = default;

QRectF DialIncrements::boundingRect() const {
	return {};
}

QPainterPath DialIncrements::shape() const {
	QPainterPath path;
	qreal dAMajor = 260 / (((doLastLine) ? mMajor : mMajor + 0.5) - 1);
	qreal dAMinor = dAMajor / (mMinor + 1);
	qreal majAngle, minAngle;
	for(int i = 0; i < mMajor; i++) {
		majAngle = -130 + (i * dAMajor);
		path.moveTo(mRadius * sin(qDegreesToRadians(majAngle)), mRadius * -cos(qDegreesToRadians(majAngle)));
		path.lineTo((mRadius - 20) * sin(qDegreesToRadians(majAngle)), (mRadius - 20) * -cos(qDegreesToRadians(majAngle)));
		if(i != mMajor - 1) {
			for(int j = 0; j < mMinor; j++) {
				minAngle = majAngle + ((j + 1) * dAMinor);
				path.moveTo(mRadius * sin(qDegreesToRadians(minAngle)), mRadius * -cos(qDegreesToRadians(minAngle)));
				path.lineTo((mRadius - ((fmod(j, 2) == 0) ? 10 : 15)) * sin(qDegreesToRadians(minAngle)), (mRadius - ((fmod(j, 2) == 0) ? 10 : 15)) * -cos(qDegreesToRadians(minAngle)));
			}
		}
	}
	if(!doLastLine) {
		for(int j = 0; j < mMinor - 1; j++) {
			minAngle = majAngle + ((j + 1) * dAMinor);
			path.moveTo(mRadius * sin(qDegreesToRadians(minAngle)), mRadius * -cos(qDegreesToRadians(minAngle)));
			path.lineTo((mRadius - ((fmod(j, 2) == 0) ? 10 : 15)) * sin(qDegreesToRadians(minAngle)), (mRadius - ((fmod(j, 2) == 0) ? 10 : 15)) * -cos(qDegreesToRadians(minAngle)));
		}
	}
	
	path.translate(mX, mY);
	return path;
}

void DialIncrements::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}

void DialIncrements::setRadius(qreal radius) {
	this->mRadius = radius;
}

void DialIncrements::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen(QPen(QColor(0xC0C0C0), 3));
	painter->drawPath(shape());
}

void DialIncrements::setIncrements(qreal major, qreal minor) {
	this->mMajor = major;
	if(fmod(mMajor, 1) != 0) {
		this->mMajor -= fmod(major, 1);
		this->doLastLine = false;
	} else {
		this->doLastLine = true;
	}
	this->mMinor = minor;
}
//</editor-fold>

//<editor-fold desc="DialNeedle">
DialNeedle::DialNeedle(QGraphicsItem *parent) : QGraphicsItem(parent), QObject(), mX(0), mY(0) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialNeedle::~DialNeedle() = default;

QRectF DialNeedle::boundingRect() const {
	return {};
}

QPainterPath DialNeedle::shape() const {
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.moveTo(10 * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 40)),
				10 * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 40))); //First point, +90 deg point.
	path.lineTo(mRadius * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 129.75)),
				mRadius * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 129.75)));
	path.lineTo(mRadius * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 130.25)),
				mRadius * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 130.25)));
	path.lineTo(10 * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 220)),
				10 * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 220)));
	path.lineTo((40 * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) + 50))) - (10 * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 40))),
				(40 * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) + 50))) - (10 * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 40))));
	path.lineTo((40 * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) + 50))) - (10 * sin(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) - 220))),
				(40 * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) + 50))) - (10 * -cos(qDegreesToRadians(mAngle * ((qreal) 260 / mAngleLimit) -220))));
	path.translate(mX, mY);
	return path;
}

void DialNeedle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush(Qt::white);
	if(0) {
		QLinearGradient grad;
		grad.setColorAt(0.2, Qt::black);
		grad.setColorAt(0.8, Qt::white);
		grad.setStart(mX-mRadius, mY-mRadius);
		grad.setFinalStop(mX+mRadius, mY+mRadius);
		painter->setBrush(QBrush(grad));
	} else {
		painter->setPen(Qt::white);
	}
	painter->drawPath(shape());
}

void DialNeedle::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}

void DialNeedle::setAngle(qreal angle) {
	this->mAngle = angle;
	update();
}

void DialNeedle::setAngleLimit(qreal limit) {
	this->mAngleLimit = limit;
}
//</editor-fold>
