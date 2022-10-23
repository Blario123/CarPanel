#include <QApplication>
#include <QMetaType>

#include "include/CarPanel.h"
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication::setStyle(QStyleFactory::create("fusion"));
    Q_INIT_RESOURCE(resources);
    QApplication a(argc, argv);
    CarPanel cp("CarPanel");
    cp.show();
    return QApplication::exec();
}
