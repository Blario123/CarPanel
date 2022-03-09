//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_SPEEDOMETER_H
#define CARPANEL_SPEEDOMETER_H

#include "Dial.h"
#include <QGridLayout>
#include <QWidget>

class Speedometer : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit Speedometer(QGraphicsItem *parent = nullptr);
	~Speedometer() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	Dial *dial;

};

#endif // CARPANEL_SPEEDOMETER_H
