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

class DisplayLogo;
class DisplayBorder;
class DisplayText;

class Display : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
    explicit Display(QGraphicsItem *parent = nullptr);
    ~Display() override = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	DisplayLogo *logo;
	DisplayBorder *border;
	DisplayText *text;
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
	explicit DisplayText(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), QObject() { hide(); }
	~DisplayText() override = default;
	QRectF boundingRect() const override { return {}; }
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
	void showText();
	void hideText();
	void setPosition(qreal, qreal);
	void setSpeed(qreal);
private:
	qreal mX = 0, mY = 0, mSpeed = 0;
	int switchValue = 0;
};

#endif // CARPANEL_DISPLAY_H
