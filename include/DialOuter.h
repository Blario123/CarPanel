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

class DialOuter : public QWidget{
Q_OBJECT

public:
	explicit DialOuter(int dx, int dy, int majW, int minW, QColor color = Qt::white, int size = 550, QWidget *parent = nullptr);
	~DialOuter() override;
	void setIncrements(double maj, int min);
	void setText(int maj, QList<QString> list, int pt);
	
private:
	QPoint *center;
	QPainterPath *increment;
	QPainterPath *incrementText;
	QColor *color;
	QRawFont *font;
	int radius;
	double x;
	double y;
	double startAngle = 220;
	double endAngle = 140;
	double textRadius;
	double outerRadius;
	double majorRadius;
	double minorRadius;
	static double toDeg(double angle);
	
signals:

public slots:

protected:
	void paintEvent(QPaintEvent *event) override;
	
};


#endif //CARPANEL_DIALOUTER_H
