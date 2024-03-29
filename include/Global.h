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

        enum IndicatorSide {
            Left,
            Right
        };
        Q_ENUM(IndicatorSide);

        enum DialType {
            Primary,
            Secondary
        };
        Q_ENUM(DialType);

        constexpr static float radiusRatio = 1.0/275.0;

        enum ControlPage {
            Speed,
            Warning,
            OilTemperature,
            Consumption,
            AvgConsumption,
            Range,
            TravellingTime,
            Distance,
            AvgSpeed,
            Pages_MAX = AvgSpeed
        };
        Q_ENUM(ControlPage);

        enum ControlPageRange {
            SinceStart,
            SinceRefuel,
            LongTerm,
            Range_MAX = LongTerm
        };
        Q_ENUM(ControlPageRange);

        constexpr static QMargins noMargins = {0,0,0,0};
};

#endif //GLOBAL_H
