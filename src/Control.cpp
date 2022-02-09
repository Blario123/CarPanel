#include "include/Control.h"

Control::Control(QWidget *parent) : QDialog(parent),
									gridBox(new QGridLayout),
									speedLineEdit(new QLineEdit),
									revLineEdit(new QLineEdit),
									speedLabel(new QLabel(tr("Speed"))),
									revLabel(new QLabel(tr("Rev/m"))),
									speedSlider(new QSlider),
									revSlider(new QSlider) {
	setModal(false);
	
	speedLineEdit->setText(QString::number(speedSlider->value()));
	revLineEdit->setText(QString::number(revSlider->value()));
	
	speedLineEdit->setReadOnly(true);
	revLineEdit->setReadOnly(true);
	
	speedSlider->setMaximum(15000);
	revSlider->setMaximum(8000);
	
	speedSlider->setOrientation(Qt::Horizontal);
	revSlider->setOrientation(Qt::Horizontal);
	
	connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
	connect(revSlider, SIGNAL(valueChanged(int)), this, SLOT(setRev(int)));
	
	gridBox->addWidget(speedLabel, 0, 0);
	gridBox->addWidget(speedLineEdit, 0, 1);
	gridBox->addWidget(speedSlider, 1, 0, 1, 2);
	gridBox->addWidget(revLabel, 2, 0);
	gridBox->addWidget(revLineEdit, 2, 1);
	gridBox->addWidget(revSlider, 3, 0, 1, 2);
	
	setLayout(gridBox);
}

Control::~Control() = default;

void Control::setSpeed(int value) {
	speedLineEdit->setText(QString::number((qreal) value/100));
}

void Control::setRev(int value) {
	revLineEdit->setText(QString::number((qreal) value/100));
}
