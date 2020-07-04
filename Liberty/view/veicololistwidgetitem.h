#ifndef VEICOLOLISTWIDGETITEM_H
#define VEICOLOLISTWIDGETITEM_H

#include <QListWidgetItem>

#include "../model/veicolo.h"

class VeicoloListWidgetItem : public QListWidgetItem
{
    public:
        VeicoloListWidgetItem();
        VeicoloListWidgetItem(const Veicolo*, const u_int&);
        const Veicolo *getVeicolo() const;
        const u_int& getPosizione() const;
        void setPosizione(const u_int&);
        void setVeicolo(const Veicolo*);
    private:
        const Veicolo * veicolo; // non devo preoccuparmi della distruzione. Si occupa il model, questo è un puntatore allo stesso elemento presente nel model
        u_int posizione;
};

#endif // VEICOLOLISTWIDGETITEM_H
