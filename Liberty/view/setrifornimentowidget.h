#ifndef SETRIFORNIMENTOWIDGET_H
#define SETRIFORNIMENTOWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "../model/rifornimento.h"

class SetRifornimentoWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit SetRifornimentoWidget(QList<string>, QWidget *parent = nullptr);
        void setValues(Rifornimento::tipo_r tr,float,float,float);

    public slots:
        void prepareSignal();
    signals:
        void salvare(Rifornimento::tipo_r,float,float,float);
    private:
        QComboBox * tipo;
        QLineEdit * quantita;
        QLineEdit * km;
        QLineEdit * totale;
};

#endif // SETRIFORNIMENTOWIDGET_H
