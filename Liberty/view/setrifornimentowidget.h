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
        explicit SetRifornimentoWidget(const QList<string> &, QWidget *parent = nullptr);
        void setValues(const Rifornimento::tipo_r &,const float &,const float &,const float &);

    public slots:
        void prepareSignal();
    signals:
        void salvare(const Rifornimento::tipo_r,const float,const float,const float);
    private:
        // tutti gli oggetti puntati dai puntatori li elimina qt
        QComboBox * tipo;
        QLineEdit * quantita;
        QLineEdit * km;
        QLineEdit * totale;
};

#endif // SETRIFORNIMENTOWIDGET_H
