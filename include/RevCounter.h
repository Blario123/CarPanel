#ifndef CARPANEL_REVCOUNTER_H
#define CARPANEL_REVCOUNTER_H

#include "Dial.h"
#include <QGridLayout>
#include <QObject>

class RevCounter : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit RevCounter(const QString &,QGraphicsItem *parent = nullptr);
	~RevCounter() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	Dial *dial;

private:
public slots:
	[[maybe_unused]] void setRev(qreal) const;
};

#endif // CARPANEL_REVCOUNTER_H
