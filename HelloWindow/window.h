#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPushButton;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

private:
    QPushButton *button;
    int counter;

private slots:
    void slotButtonClicked(bool checked);

signals:
    void counterReached();

public slots:

};

#endif // WINDOW_H
