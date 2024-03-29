#include "../include/Display.h"

//<editor-fold desc="Display">
DisplayMain::DisplayMain(const QString &name, QGraphicsItem *parent) :
                                                    QGraphicsItem(parent),
													QObject(),
													logo(new DisplayLogo(name + "::Logo", this)),
													border(new DisplayBorder(name + "::Border", this)),
													text(new DisplayText(name + "::Text", this)),
													time(new DisplayTime(name + "::Time", this)),
													timer(new QTimer(this)),
                                                    mName(name) {
	connect(timer, &QTimer::timeout, logo, &DisplayLogo::hideLogo);
	connect(timer, &QTimer::timeout, text, &DisplayText::showText);
	connect(timer, &QTimer::timeout, border, &DisplayBorder::showBorder);
	connect(timer, &QTimer::timeout, time, &DisplayTime::showTime);
	
	connect(this, &DisplayMain::positionChanged, border, &DisplayBorder::setPosition);
	connect(this, &DisplayMain::positionChanged, logo, &DisplayLogo::setPosition);
	connect(this, &DisplayMain::positionChanged, text, &DisplayText::setPosition);
	connect(this, &DisplayMain::positionChanged, time, &DisplayTime::setPosition);
	
	timer->setSingleShot(true);
	timer->start(2000);


}

QPainterPath DisplayMain::shape() const {
	return {};
}

void DisplayMain::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

}

void DisplayMain::setPosition(qreal x, qreal y) {
	emit(positionChanged(x, y));
}

[[maybe_unused]] [[maybe_unused]] void DisplayMain::showDisplay() {
	show();
}
//</editor-fold>

//<editor-fold desc="DisplayText">
QPainterPath DisplayText::shape() const {
	QPainterPath path, tempPath;
	QFont f("CarPanel");
    int displayPage = 0;
    int offset = 0;
	switch(page) {
		case Global::ControlPage::Speed:
			displayData->title = "";
			displayData->value = QString::number(round(mSpeed/100));
			displayData->unit = "mph";
			displayData->rangeText = "";
			break;
		case Global::ControlPage::Warning:
            // Page 1
            offset = 0;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Warning at";
			displayData->value = (values[displayPage] > 0) ? QString::number(values[displayPage]) : "---";
			displayData->unit = "mph";
			displayData->rangeText = "";
			break;
		case Global::ControlPage::OilTemperature:
            // Page 2
            offset = 0;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Oil Temperature";
			displayData->value = QString::number(values[displayPage]);
			displayData->unit = "°C";
			displayData->rangeText = "";
			break;
		case Global::ControlPage::Consumption:
            // Page 3
            offset = 0;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Consumption";
			displayData->value = QString::number(values[displayPage]);
			displayData->unit = "mpg";
			displayData->rangeText = "";
			break;
		case Global::ControlPage::AvgConsumption:
            // Page 4
            offset = 0;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Avg. Consumption";
			displayData->value = QString::number(values[displayPage + mValueRange]);
			displayData->unit = "mpg";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		case Global::ControlPage::Range:
            // Page 5, but value 7
            offset = 2;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Range";
			displayData->value = QString::number(values[displayPage]);
			displayData->unit = "mi";
			displayData->rangeText = "";
			break;
		case Global::ControlPage::TravellingTime:
            // Page 6, but value 8
            offset = 2;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Travelling Time";
			displayData->value = QString::number(values[displayPage + mValueRange]);
			displayData->unit = "hr";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		case Global::ControlPage::Distance:
            // Page 7, but value 11
            offset = 4;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Distance";
			displayData->value = QString::number(values[displayPage + mValueRange]);
			displayData->unit = "mi";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		case Global::ControlPage::AvgSpeed:
            // Page 8, but value 14
            offset = 6;
            displayPage = getDisplayPage(page) + offset;
			displayData->title = "Average Speed";
			displayData->value = QString::number(values[displayPage + mValueRange]);
			displayData->unit = "mph";
			displayData->rangeText = rangeTextArr[mValueRange];
			break;
		default:
			displayData->title = "";
			displayData->value = "";
			displayData->unit = "";
			displayData->rangeText = "";
			break;
	}
	path.addPath(addText(tempPath, f, 16, 150, 85, displayData->title, true));
	path.addPath(addValue(tempPath, f, valuePt, 215, 230, displayData->value, false));
	path.addPath(addTextNoTranslate(tempPath, f, 15, 225, 230, displayData->unit));
	path.addPath(addTextNoTranslate(tempPath, f, 15, 25, 255, displayData->rangeText));
	path.addPath(addTextNoTranslate(tempPath, f, 15, 275, 30, gearTextArr[mGear]));
	path.addPath(addText(tempPath, f, 19, 275, 370, QString::number(mTrip, 'f', 1), false));
	path.addPath(addTextNoTranslate(tempPath, f, 19, 25, 370, QString::number(mCompTrip)));
	path.addPath(addText(tempPath, f, 20, 150, 305, QString::number(mTemp, 'f', 1) , true));
	path.addPath(addTextNoTranslate(tempPath, f, 13,  mRightPos + 5, 305, "°C"));
	path.addPath(addTextNoTranslate(tempPath, f, 12, 250, 345, "trip"));
	path.addPath(addTextNoTranslate(tempPath, f, 12, 25, 345, "mi"));
	path.translate(mX, mY);
	return path;
}

int DisplayText::getDisplayPage(int p) const {
    return (p - 1);
}

QPainterPath DisplayText::addText(QPainterPath path, QFont f, int pt, qreal x, qreal y, const QString& t, bool o)  {
	path.clear();
	f.setPointSize(pt);
	path.addText(x, y, f, t);
	path.translate((o) ? -path.boundingRect().width()/2 : -path.boundingRect().width(), 0);
	mRightPos = path.boundingRect().right();
	return path;
}

QPainterPath DisplayText::addValue(QPainterPath path, QFont f, int pt, qreal x, qreal y, const QString& t, bool o) {
	Q_UNUSED(o)
	path.clear();
	f.setPointSize(pt);
	QFontMetrics fm(f);
 	int hzAdv = fm.horizontalAdvance(QString::number(0));
	path.addText(x, y, f, t);
	path.translate((qreal) -t.length() * hzAdv, 0);
	mRightPos = (qreal) t.length() * hzAdv;
	return path;
}

QPainterPath DisplayText::addTextNoTranslate(QPainterPath path, QFont f, int pt, qreal x, qreal y, const QString& t)  {
	path.clear();
	f.setPointSize(pt);
	path.addText(x, y, f, t);
	return path;
}

void DisplayText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen(Qt::white);
	painter->setBrush(Qt::white);
	painter->drawPath(shape());
}

void DisplayText::showText() {
	show();
}

[[maybe_unused]] void DisplayText::hideText() {
	hide();
}

void DisplayText::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}

void DisplayText::setSpeed(qreal speed) {
	this->mSpeed = speed;
}

void DisplayText::setPage(int p) {
	this->page = p;
	valuePt = (p == 0) ? 65 : 45;
	update();
}

[[maybe_unused]] void DisplayText::setValueRange(int vr) {
	this->mValueRange = vr;
	update();
}

void DisplayText::setValue(int index, double cvalue) {
    if(index == -1) {
        values.emplace_back(cvalue);
    } else {
        values[index] = cvalue;
    }
    update();
}

//</editor-fold>

//<editor-fold desc="DisplayTime">
DisplayTime::DisplayTime(const QString &name,QGraphicsItem *parent) : QGraphicsItem(parent), QObject() {
	hide();
	time = QTime::currentTime();
	auto *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &DisplayTime::updateTime);
	timer->start(1000);
}

void DisplayTime::updateTime() {
	time = QTime::currentTime();
	if(time.minute() != oldTime) {
		oldTime = time.minute();
		update();
	}
}

QPainterPath DisplayTime::shape() const {
	QPainterPath path;
	path.addText(15, 30, QFont("CarPanel", 15), time.toString("HH:mm"));
	path.translate(mX, mY);
	return path;
}

void DisplayTime::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
	painter->setPen(Qt::white);
	painter->setBrush(Qt::white);
	painter->drawPath(shape());
}

void DisplayTime::showTime() {
	show();
}

[[maybe_unused]] void DisplayTime::hideTime() {
	hide();
}

void DisplayTime::setPosition(qreal x, qreal y) {
	this->mX = x;
	this->mY = y;
}
//</editor-fold>
