#include "../include/Speedometer.h"

Speedometer::Speedometer(const QString &name,QGraphicsItem *parent) : 	QGraphicsItem(parent),
													QObject(), 
													dial(new Dial(name + "::Dial", this)) {
#ifdef CPDEBUG
	qDebug() << name;
#endif
	dial->setPosition(1275, 375);
	dial->setIncrements(8.5, 3);
	dial->text->setText({"0", "20", "40", "60", "80", "100", "120", "140"});
//
//	kmDial->setIncrements(13, 3);
//	kmDial->setText(13, {"0", "20", "40", "60", "80", "100", "120", "140", "160", "180", "200", "220", "240"}, 12);
//	kmDial->setRadius(450);
//	kmDial->setOuterRadius(500);
//	kmDial->setTextRadius(510);
//	kmDial->setCenter(QPointF(1250, 100));
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
