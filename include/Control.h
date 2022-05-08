#ifndef CARPANEL_CONTROL_H
#define CARPANEL_CONTROL_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>

class Control : public QWidget {
Q_OBJECT
public:
	explicit Control(const QString &,QWidget *parent = nullptr);
	~Control() override;
	QSlider *speedSlider;
	QSlider *revSlider;
private slots:
	void setSpeed(int value);
	void setRev(int value);
	void processPage(int value);
signals:
	void speedChanged(qreal);
	void revChanged(qreal);
	void closeSignal();
	void pageChanged(int);
private:
	QGridLayout *gridBox;
	QLineEdit *speedLineEdit;
	QLineEdit *revLineEdit;
	QLabel *speedLabel;
	QLabel *revLabel;
	QLabel *pageLabel;
	QLabel *pageName;
	QSpinBox *spinBox;
protected:
	void closeEvent(QCloseEvent *event);
};

#endif //CARPANEL_CONTROL_H
