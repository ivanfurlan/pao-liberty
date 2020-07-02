#ifndef DETTAGLIVEICOLILAYOUT_H
#define DETTAGLIVEICOLILAYOUT_H

#include <QWidget>
#include <QPushButton>
#include <QListWidgetItem>

#include <string>

#include "../model/autoibrida.h"
#include "proprietalabel.h"
#include "veicololistwidgetitem.h"


using std::string;

class DettagliVeicoliWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit DettagliVeicoliWidget(QWidget *parent = nullptr);
        ~DettagliVeicoliWidget() = default;

    public slots:
        void updateDati(QListWidgetItem* = nullptr);
        void permettiModifica();
        void annullaModifica();
        void prepareSignalSalvataggio();
    signals:
        void startModifica(); // segnale che viene preso da ogni ProprietàVeicoloLabel che "rende" appunto la lable modificabile. La connect è nel costruttore delle ProprietàVeicoloLabel
        void richiestaSalvataggio(u_int pos, string marca, string modello, u_int peso, u_short posti, u_int ultimo_tagliando, u_short cv_t, u_short cv_e, float capacita_serbatoio, float capacita_batteria, u_int km_i);
    private:
        QWidget * parent;
        QListWidgetItem * current_item;

        QPushButton * modifica;
        QPushButton * elimina;
        QPushButton * annulla;
        QPushButton * salva;

        ProprietaLabel * marca;
        ProprietaLabel * modello;
        ProprietaLabel * peso_vuoto;
        ProprietaLabel * posti;
        ProprietaLabel * km_totali;
        ProprietaLabel * km_iniziali;
        ProprietaLabel * ultimo_tagliando;
        ProprietaLabel * tagliando_da_fare;
        ProprietaLabel * cavalli;
        ProprietaLabel * cavalli_termici;
        ProprietaLabel * cavalli_elettrici;
        ProprietaLabel * kw;
        ProprietaLabel * autonomia_massima;
        ProprietaLabel * carburante;
        ProprietaLabel * consumo_medio;
        ProprietaLabel * consumo_elettrico_medio;
        ProprietaLabel * capacita_serbatoio;
        ProprietaLabel * capacita_batteria;
};

#endif // DETTAGLIVEICOLILAYOUT_H
