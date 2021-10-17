//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_SPEEDOMETER_H
#define CARPANEL_SPEEDOMETER_H

#include "Dial.h"
#include <QGridLayout>
#include <QWidget>

class Speedometer : public QWidget {
  Q_OBJECT
  
public:
	explicit Speedometer(QWidget *parent = nullptr);
	~Speedometer() override;
	Dial *dial;
	DialOuter *kmDial;

private:
	QGridLayout *grid;
	
public slots:
  void paintEvent(QPaintEvent *event);

};

#endif // CARPANEL_SPEEDOMETER_H
