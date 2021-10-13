//
// Created by Blair on 01/10/2021.
//

#ifndef CARPANEL_CARPANEL_H
#define CARPANEL_CARPANEL_H

#include <QWidget>
#include "Display.h"
#include "RevCounter.h"
#include "Speedometer.h"
#include "Indicator.h"

class CarPanel : public QWidget {
    Q_OBJECT

public:
    explicit CarPanel(QWidget *parent = nullptr);

    ~CarPanel();

private:
    int setStyle();
	
	Indicator *leftInd;
	Indicator *rightInd;

    QGridLayout *layout;
    Speedometer *left;
    Display *center;
    RevCounter *right;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *p);
	
	void mousePressEvent(QMouseEvent *event);
};


#endif // CARPANEL_CARPANEL_H
