#include "../include/Dial.h"

//<editor-fold desc="Dial">
Dial::Dial(const QString &name,Global::DialType type,QGraphicsItem *parent) : QGraphicsItem(parent),
									QObject(),
									mx(0),
									my(0),
                                    mName(name),
                                    mType(type),
									outer(new DialOuter(name + "::Outer", type, this)),
									needle(new DialNeedle(name + "::Needle", type, this)),
									increments(new DialIncrements(name + "::Increments", type, needle)),
									text(new DialText(name + "::Text", type, needle)) {
	connect(this, &Dial::positionChanged, outer, &DialOuter::setPosition);
	connect(this, &Dial::positionChanged, needle, &DialNeedle::setPosition);
	connect(this, &Dial::positionChanged, increments, &DialIncrements::setPosition);
	connect(this, &Dial::positionChanged, text, &DialText::setPosition);

	connect(this, &Dial::incrementsChanged, increments, &DialIncrements::setIncrements);
	connect(this, &Dial::incrementsChanged, text, &DialText::setIncrements);

    connect(this, &Dial::radiusChanged, needle, &DialNeedle::setRadius);
    connect(this, &Dial::radiusChanged, outer, &DialOuter::setRadius);
    connect(this, &Dial::radiusChanged, increments, &DialIncrements::setRadius);
    connect(this, &Dial::radiusChanged, text, &DialText::setRadius);
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
	return shape().boundingRect();
}

QPainterPath Dial::shape() const {
	QPainterPath path;
    if(mType == Global::DialType::Primary) {
        path.addEllipse(-20, -20, 40, 40);
        path.translate(mx, my);
    }
	return path;
}

void Dial::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(mType == Global::DialType::Primary) {
        painter->setBrush(QBrush(0x404040));
        painter->setPen(0x404040);
        painter->drawPath(shape());
        QLinearGradient grad;
        grad.setColorAt(0.1, 0xC0C0C0);
        grad.setColorAt(0.4, Qt::black);
        grad.setStart(mx - 18, my - 18);
        grad.setFinalStop(mx + 18, my + 18);
        painter->setPen(QPen(grad, 2));
        painter->drawEllipse((int) mx - 18, (int) my - 18, 36, 36);
    }
}

void Dial::setAngle(qreal value) {
	emit valueChanged(value);
}

void Dial::setRadius(qreal value) {
    emit radiusChanged(value);
}

Dial::~Dial() = default;
//</editor-fold>

//<editor-fold desc="DialOuter">
DialOuter::DialOuter(const QString &name,Global::DialType type,QGraphicsItem *parent) : QGraphicsItem(parent), QObject(), mx(0), my(0), mType(type) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialOuter::~DialOuter() = default;

QRectF DialOuter::boundingRect() const {
	return shape().boundingRect();
}

QPainterPath DialOuter::shape() const {
	QPainterPath path;
	path.addEllipse(mx, my, radius * 2, radius * 2);
	path.translate(-radius, -radius);
	return path;
}

void DialOuter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(mType == Global::DialType::Primary) {
        painter->setPen(QPen(QBrush(0xc0c0c0), 3));
        painter->drawPath(shape());
    }
}

void DialOuter::setRadius(const qreal &r) {
	radius = r;
	this->update();
}

void DialOuter::setPosition(const qreal &x, const qreal &y) {
	this->mx = x;
	this->my = y;
	update();
}
//</editor-fold>

//<editor-fold desc="DialText">
DialText::DialText(const QString &name,Global::DialType type,QGraphicsItem *parent) : QGraphicsItem(parent),
											QObject(),
											mX(0),
											mY(0),
                                            mName(name),
											mRadius(235),
											mMajorIncrements(0),
											mText(nullptr),
                                            mType(type) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialText::~DialText() = default;

QRectF DialText::boundingRect() const {
	return shape().boundingRect();
}

QPainterPath DialText::shape() const {
	QPainterPath path, tempPath;
	QPointF tempPoint;
	qreal majAngle, dAMaj = 260 /  ((qreal) mText.size() - ((mMajorIncrements == (qreal) mText.size()) ? 1 : 0.5));
	for(int i = 0; i < mText.size(); i++) {
		majAngle = -130 + (i * dAMaj);
		tempPoint = QPointF(mRadius * sin(qDegreesToRadians(majAngle)), mRadius * -cos(qDegreesToRadians(majAngle)));
		tempPath.addText(tempPoint, QFont("CarPanel", (mType == Global::DialType::Primary) ? 15 : 13), mText[i]);
		tempPath.translate(-tempPath.boundingRect().width() / 2, 0);
		tempPath = QTransform().translate(mRadius * sin(qDegreesToRadians(majAngle)), mRadius * -cos(qDegreesToRadians(majAngle)))
            .rotate(majAngle)
            .translate(mRadius * -sin(qDegreesToRadians(majAngle)), mRadius * cos(qDegreesToRadians(majAngle)))
            .map(tempPath);
		path.addPath(tempPath);
		tempPath.clear();
	}
	path.translate(mX, mY);
	return path;
}

void DialText::setPosition(const qreal &x, const qreal &y) {
	this->mX = x;
	this->mY = y;
}

void DialText::setText(const QList<QString> &text) {
	this->mText = text;
}

void DialText::setRadius(const qreal &radius) {
    this->mRadius = radius * 0.855;
}

void DialText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setBrush((mType == Global::DialType::Primary) ? Qt::white : Qt::lightGray);
	painter->setPen((mType == Global::DialType::Primary) ? Qt::white : Qt::lightGray);
	painter->drawPath(shape());
}

void DialText::setIncrements(const qreal &major) {
	this->mMajorIncrements = major;

}
//</editor-fold>

//<editor-fold desc="DialIncrements">
DialIncrements::DialIncrements(const QString &name,Global::DialType type,QGraphicsItem *parent) : QGraphicsItem(parent),
														QObject(),
														doLastLine(false),
														mX(0),
														mY(0),
														mMajor(0),
														mMinor(0),
														mRadius(225),
                                                        mName(name),
                                                        mType(type) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialIncrements::~DialIncrements() = default;

QRectF DialIncrements::boundingRect() const {
	return shape().boundingRect();
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

void DialIncrements::setPosition(const qreal &x, const qreal &y) {
	this->mX = x;
	this->mY = y;
}

void DialIncrements::setRadius(const qreal &radius) {
	this->mRadius = radius * 0.818;
}

void DialIncrements::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
painter->setPen(QPen(QColor(0xC0C0C0), 3));
    painter->drawPath(shape());
}

void DialIncrements::setIncrements(const qreal &major, const qreal &minor) {
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
DialNeedle::DialNeedle(const QString &name,Global::DialType type,QGraphicsItem *parent) : QGraphicsItem(parent),
												QObject(),
												mX(0),
												mY(0),
												mRadius(225),
												mAngle(0),
                                                mName(name),
												mAngleLimit(0),
                                                mType(type) {
	setFlag(QGraphicsItem::ItemStacksBehindParent);
}

DialNeedle::~DialNeedle() = default;

QRectF DialNeedle::boundingRect() const {
	return shape().boundingRect();
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
    if(mType == Global::DialType::Primary) {
        painter->setBrush(Qt::white);
        painter->setPen(Qt::white);
        painter->drawPath(shape());
    }
}

void DialNeedle::setPosition(const qreal &x, const qreal &y) {
	this->mX = x;
	this->mY = y;
    update();
}

void DialNeedle::setAngle(const qreal &angle) {
	this->mAngle = angle;
	update();
}

void DialNeedle::setAngleLimit(const qreal &limit) {
	this->mAngleLimit = limit;
    update();
}

void DialNeedle::setRadius(const qreal &value) {
    mRadius = value * 0.818;
    update();
}
//</editor-fold>
