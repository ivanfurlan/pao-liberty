#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <unistd.h>

#include "../model/model.h"
#include "../view/liberty.h"
#include "../model/autoibrida.h"
#include "../model/autoelettrica.h"
#include "../model/autotermica.h"

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
        void aggiungiVeicolo(QString,QString,QString,float,Rifornimento::tipo_r,float,u_short,u_int,u_int,float,float);
        void salvaModificheVeicolo(u_int pos,string marca, string modello, u_int peso, u_short posti, u_int ultimo_tagliando, u_short cv_t, u_short cv_e, float capacita_serbatoio, float capacita_batteria);
        void eliminaRifornimento(u_int,u_int);
        void aggiungiRifornimento(u_int, Rifornimento::tipo_r, float,float,float, string = "l");
        void modificaRifornimento(u_int, u_int, Rifornimento::tipo_r, float,float,float, string s = "l");
    private:
        Liberty* view;
        Model* model;

};

#endif // CONTROLLER_H
