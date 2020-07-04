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
        void salvare(const QString,const QString,const QString,const float,const Rifornimento::tipo_r,const float,const u_short,const u_int,const u_int,const float,const float);
    private:
        // tutti gli oggetti puntati dai puntatori li elimina qt
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
