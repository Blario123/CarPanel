//
// Created by Blair on 07/10/2021.
//

#ifndef CARPANEL_DIALOUTER_H
#define CARPANEL_DIALOUTER_H


#include <QWidget>
#include <QPainter>
#include <cmath>
#include <QPoint>
#include <QPainterPath>

class DialOuter : public QWidget{
Q_OBJECT

public:
	explicit DialOuter(int dx, int dy, QWidget *parent = nullptr);
	~DialOuter() override;
	
private:
	QPoint *center;
	QPainterPath increment;
	double x;
	double y;
	double startAngle = 220;
	double endAngle = 140;
	int radius = 550/2;
	double outerRadius = 450.0/2;
	double majorRadius = 410.0/2;
	double minorRadius = 420.0/2;
	static double toDeg(double angle);
	
signals:

public slots:
	void setIncrements(int maj, int min);

protected:
	void paintEvent(QPaintEvent *event) override;
	
};


#endif //CARPANEL_DIALOUTER_H
