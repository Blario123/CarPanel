#ifndef CARPANEL_CARPANEL_H
#define CARPANEL_CARPANEL_H

#include <QGraphicsView>
#include <QTimer>
#include <QFontDatabase>
#include <QMouseEvent>
#include <QAction>

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
    ~CarPanel() override = default;
	RevCounter *left;
	Speedometer *right;
    DisplayMain *center;
	Control *ctrl;
	Indicator *leftInd;
	Indicator *rightInd;
	QGraphicsScene *scene;
	QGraphicsView *view;
	Background *background;
private:
    QGridLayout *layout;
	QAction *showControl;
signals:
	void toggleLInd();
	void toggleRInd();
protected:
	void mousePressEvent(QMouseEvent *event) override;
	
};

#endif // CARPANEL_CARPANEL_H
