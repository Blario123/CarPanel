#include <QApplication>

#include "include/CarPanel.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(resources);
	if(argc > 1) {
		if(strcmpi(argv[1], "-d") == 0) {
			qDebug() << "Debug Enabled";
			#define CPDEBUG
		}
	}
    QApplication a(argc, argv);
    CarPanel cp("CarPanel");
    cp.show();
    return QApplication::exec();
}
