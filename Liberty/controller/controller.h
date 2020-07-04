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
        const Veicolo *getVeicoloAt(const int& i) const;
        int getNumVeicoli() const;
        QString getNomeVeicolo(const int& i) const;
        void eliminaVeicolo(const int& i);
    public slots:
        void aggiungiVeicolo(const QString,const QString,const QString,const float,const Rifornimento::tipo_r,const float,const u_short,const u_int,const u_int,const float,const float);
        void salvaModificheVeicolo(const u_int pos,const string marca, const string modello, const u_int peso, const u_short posti, const u_int ultimo_tagliando, const u_short cv_t, const u_short cv_e, const float capacita_serbatoio, const float capacita_batteria, const u_int km_i);
        void eliminaRifornimento(const u_int,const list<Rifornimento *>::const_iterator);
        void aggiungiRifornimento(const u_int, const Rifornimento::tipo_r, const float,const float,const float, const string = "l");
        void modificaRifornimento(const u_int, const list<Rifornimento *>::const_iterator, const Rifornimento::tipo_r, const float,const float,const float, const string s = "l");
    private:
        Liberty* view;
        Model* model;

};

#endif // CONTROLLER_H
