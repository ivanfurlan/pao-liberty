#include "veicololistwidgetitem.h"

VeicoloListWidgetItem::VeicoloListWidgetItem() : QListWidgetItem()
{

}

VeicoloListWidgetItem::VeicoloListWidgetItem(const Veicolo * v, const u_int & p) : veicolo(v), posizione(p)
{

}

const Veicolo * VeicoloListWidgetItem::getVeicolo() const
{
    return veicolo;
}

const u_int& VeicoloListWidgetItem::getPosizione() const
{
    return posizione;
}

void VeicoloListWidgetItem::setPosizione(const u_int& pos)
{
    posizione = pos;
}

void VeicoloListWidgetItem::setVeicolo(const Veicolo * v)
{
    veicolo = v;
}
