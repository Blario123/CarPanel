//
// Created by Blair on 21/10/2021.
//

#ifndef CARPANEL_DIALNEEDLE_H
#define CARPANEL_DIALNEEDLE_H

#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsPathItem>

class DialNeedle : public QObject, public QGraphicsItem {
	Q_OBJECT
	
public:
	explicit DialNeedle(QGraphicsItem *parent = nullptr);
	~DialNeedle() override;
	QPainterPath shape() const override;
	QRectF boundingRect() const override;
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	int needleRadius;
	int angle;
	QPointF center;

public slots:
	void setSpeed(int speed);
	void setRadius(int radius);

signals:

protected:

};

#endif //CARPANEL_DIALNEEDLE_H
