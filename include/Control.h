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
#include <QValidator>

#include "Global.h"

class ControlSpinBox;

class Control : public QDialog {
Q_OBJECT
public:
	explicit Control(const QString &,QWidget *parent = nullptr);
	~Control() override = default;
	QSlider *speedSlider;
	QSlider *revSlider;
private slots:
	void setSpeed(int value);
	void setRev(int value);
    void onItemDoubleClicked(QTreeWidgetItem *, int);
    void onLeftIndicatorClicked();
    void onRightIndicatorClicked();
    void onHazardClicked();
    void onShortIndicate(Global::IndicatorSide);
signals:
	void speedChanged(qreal);
	void revChanged(qreal);
	void pageChanged(int);
    void toggleLInd();
    void toggleRInd();
    void setLInd(Global::IndicatorState);
    void setRInd(Global::IndicatorState);
    void rangeChanged(Global::ControlPageRange);
private:
    QMetaObject::Connection connection;
    QTimer *indicatorTimer;
    QGridLayout *controlLayout;
    QGroupBox *sliderBox;
    QGroupBox *tripBox;
    QGroupBox *indicatorBox;
    QGroupBox *pageBox;
    QGridLayout *sliderLayout;
    QGridLayout *tripLayout;
    QGridLayout *indicatorLayout;
    QGridLayout *pageLayout;
    QLineEdit *speedLineEdit;
	QLineEdit *revLineEdit;
	QLabel *speedLabel;
	QLabel *revLabel;
	QLabel *pageLabel;
	ControlSpinBox *spinBox;
    QTreeWidget *tripTree;
    QPushButton *shortLeftIndButton;
    QPushButton *leftIndButton;
    QPushButton *shortRightIndButton;
    QPushButton *rightIndButton;
    QPushButton *hazardButton;
    QPushButton *rangeButton;
    bool doLeftIndicator = false;
    bool doRightIndicator = false;
    bool doHazard = false;
    qreal rangeIndex;
    int timerCount;
};

class ControlSpinBox : public QWidget {
    Q_OBJECT
public:
    explicit ControlSpinBox(QWidget *parent = nullptr) :    QWidget(parent),
                                                            lineEdit(new QLineEdit),
                                                            index(0),
                                                            layout(new QHBoxLayout),
                                                            buttonLayout(new QVBoxLayout),
                                                            upArrow(new QPushButton("+")),
                                                            downArrow(new QPushButton("-")) {
        lineEdit->setText(QString(QVariant::fromValue(Global::ControlPage(0)).toString()));

        upArrow->setFixedSize(25, 25);
        upArrow->setContentsMargins(Global::noMargins);
        downArrow->setFixedSize(25, 25);
        downArrow->setContentsMargins(Global::noMargins);

        buttonLayout->addWidget(upArrow);
        buttonLayout->addWidget(downArrow);
        buttonLayout->setSizeConstraint(QLayout::SetMinimumSize);
        buttonLayout->setSpacing(0);
        buttonLayout->setContentsMargins(Global::noMargins);

        layout->addWidget(lineEdit);
        layout->addLayout(buttonLayout);
        layout->setSizeConstraint(QLayout::SetMinimumSize);
        layout->setSpacing(0);
        layout->setContentsMargins(Global::noMargins);

        setLayout(layout);

        connect(upArrow, &QPushButton::pressed, [=]() {
            index++;
            if(index >  Global::ControlPage::Pages_MAX) {
                index = 0;
            }
            lineEdit->setText(QString(QVariant::fromValue(Global::ControlPage(index)).toString()));
            emit valueChanged(index);
            update();
        });
        connect(downArrow, &QPushButton::pressed, [=]() {
            index--;
            if(index < 0) {
                index = Global::ControlPage::Pages_MAX;
            }
            lineEdit->setText(QString(QVariant::fromValue(Global::ControlPage(index)).toString()));
            emit valueChanged(index);
            update();
        });
    }
private:
    int index;
    QLineEdit *lineEdit;
    QPushButton *upArrow;
    QPushButton *downArrow;
    QHBoxLayout *layout;
    QVBoxLayout *buttonLayout;
signals:
    void valueChanged(int);
public slots:
    void setIndex(qreal value) {
        index = value;
        update();
    }

protected:
    void showEvent(QShowEvent *event) override {
        lineEdit->setFixedHeight(buttonLayout->contentsRect().height());
        upArrow->setFixedHeight(buttonLayout->contentsRect().height()/2);
        downArrow->setFixedHeight(buttonLayout->contentsRect().height()/2);
        QWidget::showEvent(event);
    }
};

#endif //CARPANEL_CONTROL_H
