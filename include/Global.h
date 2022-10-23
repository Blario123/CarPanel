#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>

class Global {
    Q_GADGET
    public:
        enum IndicatorState {
            Off = 0,
            On = 1
        };
        Q_ENUM(IndicatorState);
};

#endif //GLOBAL_H
