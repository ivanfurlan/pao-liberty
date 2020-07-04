#include "veicolo.h"
#include <regex>

Veicolo::Veicolo(const std::string mar, const std::string model, const u_int &peso_vuoto, const u_short &post, const u_int &km_i, const u_int &tag, const u_int &p_max, const float &lun, const float &lar, const float &alt)
    : rifornimenti(), marca(mar), modello(model), peso(peso_vuoto), km_iniziali(km_i), posti(post), ultimo_tagliando_km(tag), peso_max(p_max), lunghezza(lun), larghezza(lar), altezza(alt)
{
    std::regex rx("[ ]*");
    if(std::regex_match(marca,rx)){
        marca = "Sconosciuta";
    }
    if(std::regex_match(modello,rx)){
        modello = "Sconosciuto";
    }
}

Veicolo::Veicolo(const Veicolo & v) : rifornimenti(copiaRifornimenti(v.rifornimenti)), marca(v.marca), modello(v.modello), peso(v.peso), km_iniziali(v.km_iniziali), posti(v.posti), ultimo_tagliando_km(v.ultimo_tagliando_km), peso_max(v.peso_max), lunghezza(v.lunghezza), larghezza(v.larghezza), altezza(v.altezza)
{

}

Veicolo& Veicolo::operator=(const Veicolo & v)
{
    if(this != &v){
        marca=v.marca;
        modello=v.modello;
        peso=v.peso;
        km_iniziali=v.km_iniziali;
        posti=v.posti;
        ultimo_tagliando_km=v.ultimo_tagliando_km;
        peso_max=v.peso_max;
        lunghezza=v.lunghezza;
        larghezza=v.larghezza;
        altezza=v.larghezza;
        distruggiRifornimenti(rifornimenti);
        rifornimenti=copiaRifornimenti(v.rifornimenti);
    }
    return *this;
}

Veicolo::~Veicolo()
{
    distruggiRifornimenti(rifornimenti);
}

std::string Veicolo::getNomeEsteso() const
{
    return marca+" - "+modello;
}

const std::string& Veicolo::getMarca() const
{
    return marca;
}

const std::string& Veicolo::getModello() const
{
    return modello;
}

const u_int& Veicolo::getPeso() const
{
    return peso;
}

u_int Veicolo::getPesoTrasportabile(const u_short &num_passeggeri) const
{
    if(num_passeggeri>getPosti()-1){
        throw std::range_error("Il numero di passeggeri non può essere maggiore del numero ddi posti del veicolo meno il conducente");
    }
    return peso_max - peso - 75*(1 + num_passeggeri);
}

const u_short& Veicolo::getPosti() const
{
    return posti;
}

void Veicolo::addRifornimento(Rifornimento* r)
{
    if(checkCorrettezzaRifornimento(*r))
        rifornimenti.push_front(r);
    else
        throw std::runtime_error("Il rifornimento presenta errori o non è adatto a questo veicolo");
}

void Veicolo::doTagliando(const u_int &km)
{
    ultimo_tagliando_km=km;
}

void Veicolo::setName(const std::string &ma, const std::string &mo)
{
    std::regex rx("[ ]*");
    if(std::regex_match(marca,rx)){
        marca = "Sconosciuta";
    }else{
        marca=ma;
    }
    if(std::regex_match(modello,rx)){
        modello = "Sconosciuto";
    }else{
        modello=mo;
    }
}

void Veicolo::setDimensioni(const float & lun, const float & lar, const float & alt)
{
    if(lun<=0 || lar<=0 || alt<=0){
        throw std::domain_error("I valori delle dimensioni devono essere tutti strettamente positivi");
    }
    lunghezza = lun;
    larghezza = lar;
    altezza = alt;
}

void Veicolo::setPeso(const u_int &p)
{
    peso=p;
}

void Veicolo::setPosti(const u_short &p)
{
    posti = p;
}

void Veicolo::setKmIniziali(const u_int &km_i)
{
    km_iniziali= km_i;
}

void Veicolo::eliminaRifornimento(const list<Rifornimento *>::const_iterator &it)
{
    delete *it;
    rifornimenti.erase(it);
}

void Veicolo::modificaRifornimento(const list<Rifornimento *>::const_iterator &it, const Rifornimento * r)
{
    if(checkCorrettezzaRifornimento(*r))
        **it=*r;
    else
        throw std::runtime_error("Il rifornimento presenta errori o non è adatto a questo veicolo");
}

bool Veicolo::checkCorrettezzaRifornimento(const Rifornimento & r) const
{
    return (r.getQuantita()>0 && r.getKmParziale()>0 && r.getCostoRifornimento()>0);
}

float Veicolo::getTotaleRifornito(const Rifornimento::tipo_r &tr) const
{
    float tot_kw=0;
    for(auto it=rifornimenti.begin();it!=rifornimenti.end();++it){
        if(tr==(*it)->getTipoRifornimento())
            tot_kw+=(*it)->getQuantita();
    }
    return tot_kw;
}

list<Rifornimento *> Veicolo::copiaRifornimenti(const list<Rifornimento *> & lista) const
{
    list<Rifornimento *> temp;
    for(auto it = lista.begin(); it!=lista.end(); it++){
        temp.push_front(new Rifornimento(**it));
    }
    temp.reverse();
    return temp;
}

void Veicolo::distruggiRifornimenti(const list<Rifornimento *> & lista) const
{
    for(auto it = lista.begin(); it!=lista.end(); it++){
        delete (*it);
    }
}

list<Rifornimento *>::const_iterator Veicolo::getUltimoRifornimento() const
{
    return rifornimenti.begin();
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

const u_int& Veicolo::getUltimoTagliando() const
{
    return ultimo_tagliando_km;
}

const list<Rifornimento *> &Veicolo::getRifornimenti() const
{
    return rifornimenti;
}

const u_int& Veicolo::getKmIniziali() const
{
    return km_iniziali;
}

u_short Veicolo::getKw() const{
    return getCavalli()*0.745699872;
}
