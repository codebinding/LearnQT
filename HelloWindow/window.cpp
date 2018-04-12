#include "window.h"

#include <QPushButton>
#include <QApplication>

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    int width = 500;
    int height = 250;

    setFixedSize(width, height);

    button = new QPushButton("Hello World", this);
    button->setCheckable(true);
    button->setGeometry(width/2-40, height/2-30, 180, 30);

    counter = 0;

    connect(button, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked(bool)));
    connect( this, SIGNAL(counterReached()), QApplication::instance(), SLOT(quit()));
}

void Window::slotButtonClicked(bool checked){

    if(checked){

        button->setText("Checked");
    }
    else{

        button->setText("Hello World");
    }

    if( ++counter == 10){

        emit counterReached();
    }
}
