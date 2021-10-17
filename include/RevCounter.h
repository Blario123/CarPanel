//
// Created by Blair on 02/10/2021.
//

#ifndef CARPANEL_REVCOUNTER_H
#define CARPANEL_REVCOUNTER_H

#include "Dial.h"
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

class RevCounter : public QWidget {
	Q_OBJECT

public:
	explicit RevCounter(QWidget *parent = nullptr);
	~RevCounter() override;

private:
	Dial *dial;
	QGridLayout *layout;
public slots:
	void paintEvent(QPaintEvent *event) override;
};

#endif // CARPANEL_REVCOUNTER_H
