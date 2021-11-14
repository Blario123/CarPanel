//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_DIAL_H
#define CARPANEL_DIAL_H

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QRectF>
#include <QGridLayout>
#include <QGraphicsPathItem>

#include "include/DialNeedle.h"
#include "include/DialOuter.h"

class Dial : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit Dial(QGraphicsItem *parent = nullptr, QGraphicsScene *scene = nullptr);
	~Dial() override;
	DialOuter *outer;
	DialNeedle *needle;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setPosition(int x, int y);

private:
	int mX;
	int mY;
	int mRadius = 550;
	int mAngle = -140;
	QPointF *center;

protected:
};

#endif // CARPANEL_DIAL_H
