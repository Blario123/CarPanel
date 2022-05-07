#ifndef CARPANEL_DIAL_H
#define CARPANEL_DIAL_H

#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QPen>
#include <QRectF>
#include <QGridLayout>
#include <QGraphicsItem>

class DialOuter;
class DialNeedle;
class DialIncrements;
class DialText;

class Dial : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit Dial(QGraphicsItem *parent = nullptr);
	~Dial() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	DialOuter *outer;
	DialNeedle *needle;
	DialIncrements *increments;
	DialText *text;
signals:
	void valueChanged(qreal);
	void positionChanged(qreal, qreal);
	void incrementsChanged(qreal, qreal);
public slots:
	void setPosition(qreal, qreal);
	void setIncrements(qreal, qreal);
	void setAngle(qreal);
private:
	qreal mx;
	qreal my;
};

class DialOuter : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialOuter(QGraphicsItem *parent = nullptr);
	~DialOuter() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	qreal radius = 275;
	qreal mx;
	qreal my;
public slots:
	
	[[maybe_unused]] void setRadius(const qreal &);
	void setPosition(const qreal &, const qreal &);
};

class DialText : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialText(QGraphicsItem *parent = nullptr);
	~DialText() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public slots:
	void setPosition(const qreal &, const qreal &);
	void setText(const QList<QString> &);
	void setIncrements(const qreal &);
private:
	qreal mX;
	qreal mY;
	qreal mRadius;
	qreal mMajorIncrements;
	QList<QString> mText;
};

class DialIncrements : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialIncrements(QGraphicsItem *parent = nullptr);
	~DialIncrements() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	QPainterPath redPath;
	bool doLastLine;
	qreal mX;
	qreal mY;
	qreal mMajor;
	qreal mMinor;
	qreal mRadius;
public slots:
	void setPosition(const qreal &, const qreal &);
	void setIncrements(const qreal &, const qreal &);
	
	[[maybe_unused]] void setRadius(const qreal &);
};

class DialNeedle : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialNeedle(QGraphicsItem *parent = nullptr);
	~DialNeedle() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
	qreal mX;
	qreal mY;
	qreal mRadius;
	qreal mAngle;
	qreal mAngleLimit;
public slots:
	void setPosition(const qreal &, const qreal &);
	void setAngle(const qreal &);
	void setAngleLimit(const qreal &);
};

#endif // CARPANEL_DIAL_H
