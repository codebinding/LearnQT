#include "window.h"

#include <QProgressBar>
#include <QSlider>

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(500, 250);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(0);
    slider->setGeometry(10, 40, 180, 30);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setGeometry(10, 10, 180, 30);

    connect(slider, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));
}
