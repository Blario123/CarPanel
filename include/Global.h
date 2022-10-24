#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>

class Global {
    Q_GADGET
    public:
        enum IndicatorState {
            Off,
            On
        };
        Q_ENUM(IndicatorState);

        enum DialType {
            Primary,
            Secondary
        };
        Q_ENUM(DialType);
        constexpr static float radiusRatio = 1.0/275.0;
};

#endif //GLOBAL_H
