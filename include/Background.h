#ifndef CARPANEL_BACKGROUND_H
#define CARPANEL_BACKGROUND_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>

class Background : public QObject, public QGraphicsItem {
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem);
public:
    explicit Background(const QString &name, QGraphicsItem *parent = nullptr) : QGraphicsItem(parent), QObject(), mName(name), background(new QPixmap) {
        background->load(":/resources/outline.png");
    }
    ~Background() override = default;
    [[nodiscard]] QRectF boundingRect() const override { return background->rect(); }
    [[nodiscard]] QPainterPath shape() const override { return QGraphicsItem::shape(); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override {
		painter->drawPixmap(0, 0, *background);
	}
private:
    QString mName;
    QPixmap *background;
};

#endif //CARPANEL_BACKGROUND_H
