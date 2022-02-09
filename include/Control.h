#ifndef CONTROL_H
#define CONTROL_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QGridLayout>

class Control : public QDialog {
Q_OBJECT
public:
	explicit Control(QWidget *parent = nullptr);
	~Control() override;
private slots:
	void setSpeed(int value);
	void setRev(int value);
signals:
private:
	QGridLayout *gridBox;
	QSlider *speedSlider;
	QSlider *revSlider;
	QLineEdit *speedLineEdit;
	QLineEdit *revLineEdit;
	QLabel *speedLabel;
	QLabel *revLabel;
};

#endif //CONTROL_H
