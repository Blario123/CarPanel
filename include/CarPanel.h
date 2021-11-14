//
// Created by Blair on 01/10/2021.
//

#ifndef CARPANEL_CARPANEL_H
#define CARPANEL_CARPANEL_H

#include <QGraphicsView>
#include "Display.h"
#include "RevCounter.h"
#include "Speedometer.h"
#include "Indicator.h"

class CarPanel : public QWidget {
    Q_OBJECT

public:
    explicit CarPanel(QWidget *parent = nullptr);

    ~CarPanel() override;

private:
    int setStyle();
	
	Indicator *leftInd;
	Indicator *rightInd;

    QGridLayout *layout;
    Display *center;

signals:

public slots:

protected:
	void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *p) override;
	
};


#endif // CARPANEL_CARPANEL_H
