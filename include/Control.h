#ifndef CARPANEL_CONTROL_H
#define CARPANEL_CONTROL_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QTreeWidget>
#include <QPushButton>
#include <QTimer>
#include <QCloseEvent>
#include "Global.h"


class Control : public QDialog {
Q_OBJECT
public:
	explicit Control(const QString &,QWidget *parent = nullptr);
	~Control() override = default;
	QSlider *speedSlider;
	QSlider *revSlider;
public slots:
    void shutdown();
private slots:
	void setSpeed(int value);
	void setRev(int value);
	void processPage(int value);
    void onItemDoubleClicked(QTreeWidgetItem *, int);
    void onLeftIndicatorClicked();
    void onRightIndicatorClicked();
    void onHazardClicked();
signals:
	void speedChanged(qreal);
	void revChanged(qreal);
	void closeSignal();
	void pageChanged(int);
    void toggleLInd();
    void toggleRInd();
    void setLInd(Global::IndicatorState);
    void setRInd(Global::IndicatorState);
private:
    QMetaObject::Connection connection;
    QTimer *indicatorTimer;
    QGridLayout *controlLayout;
    QGroupBox *sliderBox;
    QGroupBox *tripBox;
    QGroupBox *indicatorBox;
    QGridLayout *sliderLayout;
    QGridLayout *tripLayout;
    QGridLayout *indicatorLayout;
    QLineEdit *speedLineEdit;
	QLineEdit *revLineEdit;
	QLabel *speedLabel;
	QLabel *revLabel;
	QLabel *pageLabel;
	QLabel *pageName;
	QSpinBox *spinBox;
    QTreeWidget *tripTree;
    QPushButton *leftIndButton;
    QPushButton *rightIndButton;
    QPushButton *hazardButton;
    bool doLeftIndicator = false;
    bool doRightIndicator = false;
    bool doHazard = false;
};

#endif //CARPANEL_CONTROL_H
