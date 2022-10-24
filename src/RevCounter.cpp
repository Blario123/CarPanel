#include "../include/RevCounter.h"

RevCounter::RevCounter(const QString &name,QGraphicsItem *parent) : QGraphicsItem(parent),
												QObject(),
												dial(new Dial(name + "::Dial",Global::DialType::Primary, this)) {
	dial->setPosition(325, 375);
	dial->setIncrements(9, 3);
	dial->text->setText({"0", "10", "20", "30", "40", "50", "60", "70", "80"});
}

RevCounter::~RevCounter() = default;

QRectF RevCounter::boundingRect() const {
	return QRectF();
}

QPainterPath RevCounter::shape() const {
	return QGraphicsItem::shape();
}

void RevCounter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

[[maybe_unused]] void RevCounter::setRev(qreal value) const {
	dial->setAngle(value);
}
