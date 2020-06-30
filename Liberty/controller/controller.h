#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "../model/model.h"
#include "../view/liberty.h"

class Controller: public QObject
{
        Q_OBJECT
    public:
        Controller(Model* m, QObject* parent = nullptr);

        void setView(Liberty* );
        const Veicolo * getVeicoloAt(const int& i) const; //TO DO: boh
        int getNumVeicoli() const;
        QString getNomeVeicolo(const int& i) const;
        void eliminaVeicolo(const int& i);
    public slots:
        void salvaModificheVeicolo(u_int pos,string marca, string modello, u_int peso, u_short posti, u_int ultimo_tagliando, u_short cv_t, u_short cv_e, float capacita_serbatoio, float capacita_batteria);
        void eliminaRifornimento(u_int,u_int);
        void aggiungiRifornimento(u_int, Rifornimento::tipo_r, float,float,float);
        void modificaRifornimento(u_int, u_int, Rifornimento::tipo_r, float,float,float);
    private:
        Liberty* view;
        Model* model;

};

#endif // CONTROLLER_H
