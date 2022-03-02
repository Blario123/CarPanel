//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_DIAL_H
#define CARPANEL_DIAL_H

#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QPen>
#include <QRectF>
#include <QGridLayout>
#include <QGraphicsItem>

class DialOuter;
class DialNeedle;
class DialIncrements;
class DialText;

class Dial : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit Dial(QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);
	~Dial() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setPosition(qreal, qreal);
	void setIncrements(qreal, qreal);
	void setAngle(qreal);
	DialOuter *outer;
	DialNeedle *needle;
	DialIncrements *increments;
signals:
	void valueChanged(qreal);
	void positionChanged(qreal, qreal);
	void incrementsChanged(qreal, qreal);
public slots:
private:
	qreal mx;
	qreal my;
};

class DialOuter : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialOuter(QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);
	~DialOuter() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setRadius(qreal r);
private:
	qreal radius = 275;
	qreal mx;
	qreal my;
public slots:
	void setPosition(qreal, qreal);
};

class DialText : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialText(QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);
	~DialText() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

class DialIncrements : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialIncrements(QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);
	~DialIncrements() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	qreal mx;
	qreal my;
public slots:
	void setPosition(qreal, qreal);
	void setIncrements(qreal, qreal);
};

class DialNeedle : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialNeedle(QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);
	~DialNeedle() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	qreal mX;
	qreal mY;
	qreal mRadius = 225;
	qreal mAngle = 0;
	qreal mAngleLimit;
public slots:
	void setPosition(qreal, qreal);
	void setAngle(qreal);
	void setAngleLimit(qreal);
};

#endif // CARPANEL_DIAL_H
