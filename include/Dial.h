#ifndef CARPANEL_DIAL_H
#define CARPANEL_DIAL_H

#include <QPainter>
#include <QPainterPath>
#include <QPolygon>
#include <QPen>
#include <QRectF>
#include <QGridLayout>
#include <QGraphicsItem>
#include "Global.h"

class DialOuter;
class DialNeedle;
class DialIncrements;
class DialText;

class Dial : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit Dial(const QString &,Global::DialType type = Global::DialType::Primary,QGraphicsItem *parent = nullptr);
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
    void radiusChanged(qreal);
	void positionChanged(qreal, qreal);
	void incrementsChanged(qreal, qreal);
public slots:
    void setRadius(qreal);
	void setPosition(qreal, qreal);
	void setIncrements(qreal, qreal);
	void setAngle(qreal);
private:
    Global::DialType mType;
	qreal mx;
	qreal my;
    QString mName;
};

class DialOuter : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialOuter(const QString &,Global::DialType,QGraphicsItem *parent = nullptr);
	~DialOuter() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
	qreal radius = 275;
	qreal mx;
	qreal my;
    Global::DialType mType;
    QString mName;
public slots:
	[[maybe_unused]] void setRadius(const qreal &);
	void setPosition(const qreal &, const qreal &);
};

class DialText : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialText(const QString &,Global::DialType,QGraphicsItem *parent = nullptr);
	~DialText() override;
	[[nodiscard]] QRectF boundingRect() const override;
	[[nodiscard]] QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
public slots:
	void setPosition(const qreal &, const qreal &);
	void setText(const QList<QString> &);
	void setIncrements(const qreal &);
    void setRadius(const qreal &);
private:
	qreal mX;
	qreal mY;
	qreal mRadius;
	qreal mMajorIncrements;
	QList<QString> mText;
    Global::DialType mType;
    QString mName;
};

class DialIncrements : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialIncrements(const QString &,Global::DialType,QGraphicsItem *parent = nullptr);
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
    Global::DialType mType;
    QString mName;
public slots:
	void setPosition(const qreal &, const qreal &);
	void setIncrements(const qreal &, const qreal &);
	
	[[maybe_unused]] void setRadius(const qreal &);
};

class DialNeedle : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)
public:
	explicit DialNeedle(const QString &,Global::DialType,QGraphicsItem *parent = nullptr);
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
    Global::DialType mType;
    QString mName;
public slots:
	void setPosition(const qreal &, const qreal &);
    void setRadius(const qreal &);
	void setAngle(const qreal &);
	void setAngleLimit(const qreal &);
};

#endif // CARPANEL_DIAL_H
