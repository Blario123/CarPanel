#include <QApplication>
#include <QGraphicsView>
#include <QLabel>

#include "../include/CarPanel.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    CarPanel w;
    w.show();
    return QApplication::exec();
}
