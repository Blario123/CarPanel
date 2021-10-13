//
// Created by Blair on 07/10/2021.
//

#ifndef CARPANEL_DIALOUTER_H
#define CARPANEL_DIALOUTER_H


#include <QWidget>
#include <QPainter>
#include <cmath>
#include <QPainterPath>

class DialOuter : public QWidget{
Q_OBJECT

public:
	explicit DialOuter(double dx, double dy, QWidget *parent = nullptr);
	~DialOuter() override;
	
private:
	double x;
	double y;
	double radius = 550;
	
signals:

public slots:
	void setMajorIncrements(int maj);
	void setMinorIncrements(int min);

protected:
	void paintEvent(QPaintEvent *event) override;
	
};


#endif //CARPANEL_DIALOUTER_H
