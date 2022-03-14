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
    Display *center;
	Control *ctrl;
	Indicator *leftInd;
	Indicator *rightInd;

private:
    QGridLayout *layout;
signals:
	void toggleLInd();
	void toggleRInd();
protected:
	void mousePressEvent(QMouseEvent *event) override;
	
};

#endif // CARPANEL_CARPANEL_H
