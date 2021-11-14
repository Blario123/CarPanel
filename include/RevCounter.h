//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_REVCOUNTER_H
#define CARPANEL_REVCOUNTER_H

#include "Dial.h"
#include <QGridLayout>
#include <QObject>

class RevCounter : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit RevCounter(QGraphicsItem *parent = nullptr);
	~RevCounter() override;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	Dial *dial;

private:
public slots:
};

#endif // CARPANEL_REVCOUNTER_H
