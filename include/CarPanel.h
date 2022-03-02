//
// Created by Blair on 01/10/2021.
//

#ifndef CARPANEL_CARPANEL_H
#define CARPANEL_CARPANEL_H

#include <QGraphicsView>
#include "Control.h"
#include "Display.h"
#include "RevCounter.h"
#include "Speedometer.h"
#include "Indicator.h"
#include "Background.h"

class CarPanel : public QWidget {
    Q_OBJECT

public:
    explicit CarPanel(QWidget *parent = nullptr);

    ~CarPanel() override;
	RevCounter *left;
	Speedometer *right;
	Control *ctrl;

private:
    int setStyle();
	
	Indicator *leftInd;
	Indicator *rightInd;

    QGridLayout *layout;
    Display *center;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	
};

#endif // CARPANEL_CARPANEL_H
