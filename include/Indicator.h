#ifndef CARPANEL_INDICATOR_H
#define CARPANEL_INDICATOR_H

#include <QObject>
#include <QGraphicsItem>

class Indicator : public QObject, public QGraphicsItem {
	Q_OBJECT
	
public:
	explicit Indicator(const QString &,QGraphicsItem *parent = nullptr);
	~Indicator() override = default;
	[[nodiscard]] QRectF boundingRect() const override { return {}; }
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
	void toggle();
	void setPosition(qreal, qreal);
	void toggleOrientation();

private:
	bool mState = false;
	qreal mX = 0, mY = 0;
	qreal mSize = 64;
	float mOrientation = 0;
	
};

#endif // CARPANEL_INDICATOR_H
