#ifndef SETRIFORNIMENTOWIDGET_H
#define SETRIFORNIMENTOWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include "../model/rifornimento.h"

class SetRifornimentoWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit SetRifornimentoWidget(QList<string>, QWidget *parent = nullptr);
        void setValues(float,float,float);

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
