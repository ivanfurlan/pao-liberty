#ifndef LIBERTY_H
#define LIBERTY_H

#include <QWidget>
#include "controller/controller.h"

class Liberty : public QWidget
{
        Q_OBJECT

    public:
        Liberty(QWidget *parent = nullptr);
        ~Liberty();
};
#endif // LIBERTY_H
