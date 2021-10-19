//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_DIAL_H
#define CARPANEL_DIAL_H

#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QWidget>

#include "include/DialOuter.h"
#include <QGridLayout>

class Dial : public QWidget {
  Q_OBJECT

public:
	explicit Dial(int majW, int minW, int dx = 0, int dy = 0, QWidget *parent = nullptr);
	~Dial() override;
	DialOuter *outer;
 
private:
	int x;
	int y;
	int radius = 550;
	QGridLayout *layout;

signals:

public slots:

protected:
  void paintEvent(QPaintEvent *event) override;
};

#endif // CARPANEL_DIAL_H
