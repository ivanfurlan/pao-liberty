#ifndef SETVEICOLOWIDGET_H
#define SETVEICOLOWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include "../model/rifornimento.h"

class SetVeicoloWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit SetVeicoloWidget(QWidget *parent = nullptr);

    public slots:
        void tipoCambiato();
        void prepareSignal();
    signals:
        void salvare(QString,QString,QString,float,Rifornimento::tipo_r,float,u_short,u_int,u_int,float,float);
    private:

        QLabel * cavalli_tLabel;
        QLabel * cavalli_eLabel;
        QLabel * serbatoioLabel;
        QLabel * batteriaLabel;

        QComboBox * tipo;
        QLineEdit * marca;
        QLineEdit * modello;
        QLineEdit * km_iniziali;
        QComboBox * tipo_carburante;
        QLineEdit * peso;
        QLineEdit * posti_sedere;
        QLineEdit * cavalli_t;
        QLineEdit * cavalli_e;
        QLineEdit * serbatoio;
        QLineEdit * batteria;

};

#endif // SETVEICOLOWIDGET_H
