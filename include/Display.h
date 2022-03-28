//
// Created by Blair on 01/10/2021.
//

#ifndef CARPANEL_DISPLAY_H
#define CARPANEL_DISPLAY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QTimer>
#include <QTime>

class DisplayLogo;
class DisplayBorder;
class DisplayText;
class DisplayTime;

class DisplayMain : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
    explicit DisplayMain(QGraphicsItem *parent = nullptr);
    ~DisplayMain() override = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	DisplayLogo *logo;
	DisplayBorder *border;
	DisplayText *text;
	DisplayTime *time;
private:
public slots:
	void showDisplay();
	void setPosition(qreal, qreal);
signals:
	void positionChanged(qreal, qreal);
};

class DisplayLogo : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayLogo(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), QObject() {};
	~DisplayLogo() override = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override { return QGraphicsItem::shape(); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		QPixmap logo;
		logo.load(":/resources/Logo.png");
		painter->drawPixmap((int) mX + 25, (int) mY + 25, logo);
	}
public slots:
	void hideLogo() {
		hide();
	}
	void showLogo() {
		show();
	}
	void setPosition(qreal x, qreal y) {
		this->mX = x;
		this->mY = y;
	}

private:
	qreal mX = 0, mY = 0;
};

class DisplayBorder : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayBorder(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), QObject() { hide(); };
	~DisplayBorder() override = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override {
		QPainterPath path;
		path.addRect(0, 0, 300, 400);
		path.translate(mX, mY);
		return path;
	}
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		painter->setPen(0x404040);
		painter->drawPath(shape());
	}
private:
	qreal mX = 0, mY = 0;
public slots:
	void showBorder() {
		show();
	}
	void hideBorder() {
		hide();
	}
	void setPosition(qreal x, qreal y) {
		this->mX = x;
		this->mY = y;
	}
};

class DisplayText : public QObject, public QGraphicsItem {

Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayText(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), QObject() {
		hide();
	}
	~DisplayText() override = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
	void showText();
	void hideText();
	void setPosition(qreal, qreal);
	void setSpeed(qreal);
	void setPage(int);
	void setValueRange(int);
private:
	static QPainterPath addText(QPainterPath, QFont, int, qreal, qreal, const QString&, bool) ;
	static QPainterPath addTextNoTranslate(QPainterPath, QFont, int, qreal, qreal, const QString&) ;
	typedef struct pageData {
		QString title, value, unit, rangeText;
	} data;
	
	data *displayData = new data;
	qreal 	mX = 0,
			mY = 0,
			mSpeed = 0,
			mConsumption = 0,
			mTime = 0,
			mOilTemp = 0,
			mWarning,
			mTrip = 0,
			mRange = 0;
	// Arrays for display values. 0: since start, 1: since refuel, 2: long term
	qreal mConsumptionArr[3], mSpeedArr[3], mTimeArr[3], mDistanceArr[3];
	QString rangeTextArr[3] = {"Since Start", "Since Refuel", "Long-term"};
	int page = 0,
		mValueRange = 0;
};

class DisplayTime : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayTime(QGraphicsItem *parent = nullptr);
	~DisplayTime() = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	int oldTime{};
	qreal mX = 0, mY = 0;
	QTime time;
public slots:
	void updateTime();
	void showTime();
	void hideTime();
	void setPosition(qreal, qreal);
signals:
};

#endif // CARPANEL_DISPLAY_H
