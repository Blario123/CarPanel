#ifndef CARPANEL_BACKGROUND_H
#define CARPANEL_BACKGROUND_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QObject>

class Background : public QObject, public QGraphicsItem {
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem);
public:
	QRectF boundingRect() const override { return QRectF();}
	QPainterPath shape() const override { return QGraphicsItem::shape(); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		QPixmap background;
		background.load(":/resources/outline.png");
		painter->drawPixmap(0, 0, background);
	}
};


#endif //CARPANEL_BACKGROUND_H
