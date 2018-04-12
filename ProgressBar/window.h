#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QProgressBar;
class QSlider;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

private:
    QProgressBar *progressBar;
    QSlider *slider;

signals:

public slots:

};

#endif // WINDOW_H
