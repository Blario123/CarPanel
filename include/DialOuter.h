//
// Created by Blair on 07/10/2021.
//

#ifndef CARPANEL_DIALOUTER_H
#define CARPANEL_DIALOUTER_H

#include <cmath>
#include <iostream>
#include <QColor>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPoint>
#include <QWidget>
#include <QRawFont>
#include <QGraphicsPathItem>

class DialOuter : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialOuter(QGraphicsItem *parent = nullptr);
	~DialOuter() override;
	void setIncrements(double maj, int min);
	void setText(int maj, QList<QString> list, int pt);
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void setCenter(QPointF center);
	void setRadius(int radius);
	void setOuterRadius(int radius);
	void setInnerRadius(int radius);
	void setTextRadius(int radius);
	void setX(int x);
	void setY(int y);
	void setPosition(int x, int y);
	
private:
	QPainterPath *increment;
	QPainterPath *incrementText;
	double dx;
	double dy;
	double startAngle = 220;
	double endAngle = 140;
	qreal mX;
	qreal mY;
	int mRadius;
	double mTextRadius;
	double mOuterRadius;
	double mMinorRadius;
};


#endif //CARPANEL_DIALOUTER_H
