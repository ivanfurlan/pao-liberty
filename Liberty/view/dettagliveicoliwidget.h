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
        void richiestaSalvataggio(const u_int pos, const string marca, const string modello, const u_int peso, const u_short posti, const u_int ultimo_tagliando, const u_short cv_t, const u_short cv_e, const float capacita_serbatoio, const float capacita_batteria, const u_int km_i);
    private:
        QWidget * parent;
        QListWidgetItem * current_item;

        // tutti gli oggetti puntati dai puntatori li elimina qt
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
