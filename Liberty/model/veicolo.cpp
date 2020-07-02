#include "veicolo.h"

Veicolo::Veicolo(const std::string mar, const std::string model, const u_int peso_vuoto, const u_short post, const u_int km_i, const u_int tag, const u_int p_max, const float lun, const float lar, const float alt)
    : marca(mar), modello(model), peso(peso_vuoto), km_iniziali(km_i), posti(post), ultimo_tagliando_km(tag), peso_max(p_max), lunghezza(lun), largheza(lar), altezza(alt)
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
    return posti;
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

void Veicolo::setName(std::string ma, std::string mo)
{
    marca=ma;
    modello=mo;
}

void Veicolo::setPeso(u_int p)
{
    peso=p;
}

void Veicolo::setPosti(u_short p)
{
    posti = p;
}

void Veicolo::eliminaRifornimento(u_int pos)
{
    auto it = rifornimenti.begin();
    std::advance(it, pos);
    Rifornimento * temp = *it;
    rifornimenti.erase(it);
    delete temp;
}

void Veicolo::modificaRifornimento(u_int pos, Rifornimento * r)
{
    auto it = rifornimenti.begin();
    std::advance(it, pos);
    Rifornimento * temp = *it;
    *it=r;
    delete temp;

}

bool Veicolo::checkCorrettezzaRifornimento(const Rifornimento & r) const
{
    return (r.getQuantita()>0 && r.getKmParziale()>0 && r.getCostoRifornimento()>0);
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
        return km_iniziali;
    else{
        return km_iniziali+getSommaKmRifornimenti();
    }
}

u_int Veicolo::getSommaKmRifornimenti() const
{
    u_int temp=0;
    for (Rifornimento* r : rifornimenti) {
        temp+=r->getKmParziale();
    }
    return temp;
}

u_int Veicolo::getUltimoTagliando() const
{
    return ultimo_tagliando_km;
}

const list<Rifornimento *> &Veicolo::getRifornimenti() const
{
    return rifornimenti;
}

u_int Veicolo::getKmIniziali() const
{
    return km_iniziali;
}
