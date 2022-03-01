#include <QApplication>
#include <QGraphicsView>
#include <QLabel>

#include "include/CarPanel.h"
#include "include/Control.h"
#include "include/Dial.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    CarPanel cp;
	Control ctrl;
//	cp.connect(&ctrl, SIGNAL(valueChanged(qreal)), cp.right->dial->needle, SLOT(setSpeed(qreal)));
	cp.connect(&ctrl, SIGNAL(valueChanged(qreal)), cp.left->dial->needle, SLOT(setAngle(qreal)));
	ctrl.show();
    cp.show();
    return QApplication::exec();
}
