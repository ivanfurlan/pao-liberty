#ifndef DETTAGLIVEICOLILAYOUT_H
#define DETTAGLIVEICOLILAYOUT_H

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidgetItem>

#include "../model/veicolo.h"
#include "proprietaveicololabel.h"

class DettagliVeicoliWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit DettagliVeicoliWidget(QWidget *parent = nullptr);
        ~DettagliVeicoliWidget() = default;

    public slots:
        void updateDati(QListWidgetItem*);
        void permettiModifica();
    signals:
        void startModifica();
    private:
        QWidget * parent;

        QPushButton * rifornisci;
        QPushButton * modifica;
        QPushButton * elimina;
        QPushButton * annulla;
        QPushButton * salva;

        ProprietaVeicoloLabel * marca;
        ProprietaVeicoloLabel * modello;
        ProprietaVeicoloLabel * peso_vuoto;
        ProprietaVeicoloLabel * posti;
        ProprietaVeicoloLabel * km_totali;
        ProprietaVeicoloLabel * ultimo_tagliando;
        ProprietaVeicoloLabel * tagliando_da_fare;
        ProprietaVeicoloLabel * cavalli;
        ProprietaVeicoloLabel * kw;
        ProprietaVeicoloLabel * autonomia_massima;
        ProprietaVeicoloLabel * carburante;
        ProprietaVeicoloLabel * consumo_medio;
        ProprietaVeicoloLabel * consumo_elettrico_medio;
        ProprietaVeicoloLabel * capacita_serbatoio;
        ProprietaVeicoloLabel * capacita_batteria;
};

#endif // DETTAGLIVEICOLILAYOUT_H
