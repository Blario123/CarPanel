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
    explicit CarPanel(const QString &,QWidget *parent = nullptr);
//    ~CarPanel() override = default;
	RevCounter *left;
	Speedometer *right;
    DisplayMain *center;
	Control *ctrl;
	Indicator *leftInd;
	Indicator *rightInd;
	Background *background;
	QGraphicsScene *scene;
	QGraphicsView *view;
private:
    QGridLayout *layout;
	QAction *showControl;
public slots:
    void showRClickMenu(const QPoint &p);
signals:
    void closeSignal();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CARPANEL_CARPANEL_H
