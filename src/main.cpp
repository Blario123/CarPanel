#include <QApplication>

#include "include/CarPanel.h"
#include <cstring>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication::setStyle(QStyleFactory::create("fusion"));
    Q_INIT_RESOURCE(resources);
	if(argc > 1) {
		if(strcmp(argv[1], "-d") == 0) {
			qDebug() << "Debug Enabled";
			#define CPDEBUG
		}
	}
    QApplication a(argc, argv);
    CarPanel cp("CarPanel");
    cp.show();
    return QApplication::exec();
}
