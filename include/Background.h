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
    Background() {
        background.load(":/resources/outline.png");
    }
    QRectF boundingRect() const override { return background.rect(); }
	QPainterPath shape() const override { return QGraphicsItem::shape(); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		painter->drawPixmap(0, 0, background);
	}
private:
    QPixmap background;
};


#endif //CARPANEL_BACKGROUND_H
