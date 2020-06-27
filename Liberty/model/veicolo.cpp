#include "veicolo.h"

Veicolo::Veicolo(const std::string mar, const std::string model, const u_int peso_vuoto, const u_int p_max, const u_short pass, const u_int tag, const float lun, const float lar, const float alt)
    : marca(mar), modello(model), peso(peso_vuoto), peso_max(p_max), passeggeri_max(pass), ultimo_tagliando_km(tag), lunghezza(lun), largheza(lar), altezza(alt)
{

}

Veicolo::~Veicolo()
{
    for(auto it = rifornimenti.begin(); it!=rifornimenti.end(); it++){
        delete (*it);
    }
}

std::string Veicolo::getNomeEsteso() const
{
    return marca+" - "+modello;
}

std::string Veicolo::getMarca() const
{
    return marca;
}

std::string Veicolo::getModello() const
{
    return modello;
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

bool Veicolo::checkCorrettezzaRifornimento(const Rifornimento & r) const
{
    return (r.getKm()>=this->getKmTotaliVeicolo()) && \
            (r.getCostoPerUnita()>0);
}

float Veicolo::getTotaleRifornito(const Rifornimento::tipo_r tr) const
{
    float tot_kw=0;
    for(auto it=rifornimenti.begin();it!=rifornimenti.end();++it){
        if(tr==(*it)->getTipoRifornimento())
            tot_kw+=(*it)->getQuantita();
    }
    return tot_kw;
}

const Rifornimento &Veicolo::getUltimoRifornimento() const
{
    return *rifornimenti.front();
}

u_int Veicolo::getKmTotaliVeicolo() const
{
    if(rifornimenti.empty())
        return 0;
    else
        return rifornimenti.front()->getKm();
}

u_int Veicolo::getUltimoTagliando() const
{
    return ultimo_tagliando_km;
}
