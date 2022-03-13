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
    ~Display() override;
	
	QRectF boundingRect() const override;
	
	QPainterPath shape() const override;
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	
	void setPosition(qreal x, qreal y) {
		emit(positionChanged(x, y));
	}
	DisplayLogo *logo;
	DisplayBorder *border;
	DisplayText *text;
private:
public slots:
	void showDisplay();
	void setSpeed(qreal);
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
		painter->drawPixmap(mX + 25, mY + 25, logo);
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
	qreal mX, mY;
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
		return path; }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		painter->setPen(Qt::white);
		painter->drawPath(shape());
	}
private:
	qreal mX, mY;
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
	explicit DisplayText(QGraphicsItem *parent = nullptr);
	~DisplayText() override = default;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
	void showText() {
		show();
	}
	void hideText() {
		hide();
	}
	void setPosition(qreal x, qreal y) {
		this->mX = x;
		this->mY = y;
	}

private:
	qreal mX, mY;
};

#endif // CARPANEL_DISPLAY_H
