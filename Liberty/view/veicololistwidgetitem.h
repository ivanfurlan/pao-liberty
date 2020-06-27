#ifndef VEICOLOLISTWIDGETITEM_H
#define VEICOLOLISTWIDGETITEM_H

#include <QListWidgetItem>

class Veicolo;

class VeicoloListWidgetItem : public QListWidgetItem
{
    public:
        VeicoloListWidgetItem();
        VeicoloListWidgetItem(const Veicolo*, const u_int&);
        const Veicolo *getVeicolo() const;
        void setPosizione(const u_int);
        void setVeicolo(const Veicolo*);
    private:
        const Veicolo * veicolo; // non devo preoccuparmi della distruzione. Si occupa il model, questo è un puntatore allo stesso elemento presente nel model
        u_int posizione;
};

#endif // VEICOLOLISTWIDGETITEM_H
