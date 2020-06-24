#include "veicolo.h"

Veicolo::Veicolo()
{

}

std::string Veicolo::getNomeEsteso() const
{
    return marca+" - "+modello;
}

u_int Veicolo::getPeso() const
{
    return peso;
}

u_int Veicolo::getPesoTrasportabile(u_short num_passeggeri) const
{
    // TO DO: controllare num_passeggeri sia accettabile
    return peso_max - peso - 75*(1 + num_passeggeri);
}

u_short Veicolo::getPosti() const
{
    return passeggeri_max+1;
}

void Veicolo::addRifornimento(Rifornimento* r)
{
    if(checkCorrettezzaRifornimento(*r))
        rifornimenti.push_front(r);
    // TO DO: gestire gli errori
}

void Veicolo::doTagliando(const u_int km)
{
    // TO DO: check km siano validi
    ultimo_tagliando_km=km;
}

const Rifornimento &Veicolo::getUltimoRifornimento() const
{
    return *rifornimenti.front();
}

u_int Veicolo::getKmTotaliVeicolo() const
{
    return rifornimenti.front()->getKm();
}

u_int Veicolo::getUltimoTagliando() const
{
    return ultimo_tagliando_km;
}
