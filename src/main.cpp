#include <QApplication>
#include <QGraphicsView>
#include <QLabel>

#include "include/CarPanel.h"
#include "include/Dial.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    CarPanel cp;
    cp.show();
    return QApplication::exec();
}
