#include "../include/Speedometer.h"

Speedometer::Speedometer(const QString &name,QGraphicsItem *parent) : 	QGraphicsItem(parent),
													QObject(), 
													dial(new Dial(name + "::Dial",Global::DialType::Primary, this)),
                                                    kmDial(new Dial(name + "::kmDial",Global::DialType::Secondary , this)) {
	dial->setPosition(1275, 375);
	dial->setIncrements(8.5, 3);
    dial->setRadius(275);
	dial->text->setText({"0", "20", "40", "60", "80", "100", "120", "140"});
    dial->setZValue(1);
    kmDial->setPosition(1275, 375);
    kmDial->setRadius(205);
	kmDial->setIncrements(13, 3);
	kmDial->text->setText({"0", "20", "40", "60", "80", "100", "120", "140", "160", "180", "200", "220", "240"});
}

Speedometer::~Speedometer() = default;

QRectF Speedometer::boundingRect() const {
	return {};
}

QPainterPath Speedometer::shape() const {
	return QGraphicsItem::shape();
}

void Speedometer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}
