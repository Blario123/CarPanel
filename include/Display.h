#ifndef CARPANEL_DISPLAY_H
#define CARPANEL_DISPLAY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QTimer>
#include <QTime>
#include <QFont>
#include <QFontMetricsF>
#include <utility>

#include "Global.h"

class DisplayLogo;
class DisplayBorder;
class DisplayText;
class DisplayTime;

class DisplayMain : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
    explicit DisplayMain(const QString &,QGraphicsItem *parent = nullptr);
    ~DisplayMain() override = default;
	[[nodiscard]] QRectF boundingRect() const override { return shape().boundingRect(); };
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	DisplayLogo *logo;
	DisplayBorder *border;
	DisplayText *text;
	DisplayTime *time;
	QTimer *timer;
private:
    QString mName;
public slots:
	[[maybe_unused]] void showDisplay();
	void setPosition(qreal, qreal);
signals:
	void positionChanged(qreal, qreal);
};

class DisplayLogo : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayLogo(QString name, QGraphicsItem *parent = nullptr) : QObject(), QGraphicsItem(parent), mName(name) {
		show();
		logo.load(":/resources/Logo.png");
	};
	~DisplayLogo() override = default;
	[[nodiscard]] QRectF boundingRect() const override {
		return {mX + 25, mY +25, (float) logo.rect().width(), (float) logo.rect().height()};
	}
	[[nodiscard]] QPainterPath shape() const override {
        return QGraphicsItem::shape();
	}
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		painter->drawPixmap((int) mX + 25, (int) mY + 25, logo);
	}
public slots:
	void hideLogo() {
		hide();
	}
	[[maybe_unused]] void showLogo() {
		show();
	}
	void setPosition(qreal x, qreal y) {
		this->mX = x;
		this->mY = y;
	}

private:
    QString mName;
    QPixmap logo;
	qreal mX = 0;
	qreal mY = 0;
};

class DisplayBorder : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayBorder(const QString &,QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), QObject() { hide(); };
	~DisplayBorder() override = default;
	[[nodiscard]] QRectF boundingRect() const override { return shape().boundingRect(); }
	[[nodiscard]] QPainterPath shape() const override {
		QPainterPath path;
		path.addRect(0, 0, 300, 400);
		path.translate(mX, mY);
		return path;
	}
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		painter->setPen(0x202020);
		painter->drawPath(shape());
		painter->setPen(QPen(QColor(0xCCCCCC), 1, Qt::DotLine));
		painter->drawLine((int) mX, (int) mY + 45, (int) mX + 300, (int) mY + 45);
		painter->drawLine((int) mX, (int) mY + 280, (int) mX + 300, (int) mY + 280);
		painter->setPen(QPen(QColor(0xC0C0C0), 3));
		painter->drawRect((int) mX + 5, (int) mY + 50, 290, 225);
	}
private:
	qreal mX = 0, mY = 0;
public slots:
	void showBorder() {
		show();
	}
	[[maybe_unused]] void hideBorder() {
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
	explicit DisplayText(const QString &,QGraphicsItem *parent = nullptr) : QGraphicsItem(parent),
															QObject(),
															displayData(new data),
															mX(0),
															mY(0),
															mSpeed(0),
															valuePt(65),
															rangeTextArr{"Since Start", "Since Refuel", "Long-term"},
															gearTextArr{"", "R", "1", "2", "3", "4", "5", "6"} {
		hide();
	}
	~DisplayText() override = default;
	[[nodiscard]] QRectF boundingRect() const override { return shape().boundingRect(); }
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public slots:
	void showText();
	[[maybe_unused]] void hideText();
	void setPosition(qreal, qreal);
	void setSpeed(qreal);
	void setPage(int);
	[[maybe_unused]] void setValueRange(int);
    void setValue(double, int);
private:
    int getDisplayPage(int) const;
	static QPainterPath addText(QPainterPath, QFont, int, qreal, qreal, const QString&, bool);
	static QPainterPath addValue(QPainterPath, QFont, int, qreal, qreal, const QString&, bool);
	static QPainterPath addTextNoTranslate(QPainterPath, QFont, int, qreal, qreal, const QString&);
	typedef struct pageData {
		QString title,
				value,
				unit,
				rangeText;
	} data;
	data *displayData;
	qreal 	mX,
			mY,
			mSpeed,
			mTrip,
			mCompTrip,
			mTemp;
	int valuePt;
	inline static qreal mRightPos;
	qreal 	mConsumptionArr[3],
			mSpeedArr[3],
			mTimeArr[3],
			mDistanceArr[3];
	QString rangeTextArr[3],
			gearTextArr[8];
	int page = 0,
		mValueRange = 0,
		mGear = 0;
    std::vector<double> values;
};

class DisplayTime : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DisplayTime(const QString &,QGraphicsItem *parent = nullptr);
	~DisplayTime() override = default;
	[[nodiscard]] QRectF boundingRect() const override { return shape().boundingRect(); }
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	int oldTime{};
	qreal mX = 0, mY = 0;
	QTime time;
public slots:
	void updateTime();
	void showTime();
	
	[[maybe_unused]] void hideTime();
	void setPosition(qreal, qreal);
signals:
};

#endif // CARPANEL_DISPLAY_H
