#include "rifornimento.h"

map<Rifornimento::tipo_r,std::string> Rifornimento::tipo_string = {{Rifornimento::DIESEL,"Diesel"},{Rifornimento::BENZINA,"Benzina"},{Rifornimento::ELETTRICITA,"Elettricità"}};
map<std::string,Rifornimento::tipo_r> Rifornimento::string_tipo = {{"Diesel",Rifornimento::DIESEL},{"Benzina",Rifornimento::BENZINA},{"Elettricità",Rifornimento::ELETTRICITA}};

Rifornimento::Rifornimento(Rifornimento::tipo_r t, float km, float qt, float c, string uni) : unita(uni), tipo_rifornimento(t), km_parziale(km), quantita_rifornita(qt), costo_totale(c)
{
}

float Rifornimento::getCostoRifornimento() const
{
    return costo_totale;
}

float Rifornimento::getKmParziale() const
{
    return this->km_parziale;
}

float Rifornimento::getQuantita() const
{
    return quantita_rifornita;
}

float Rifornimento::getCostoPerUnita() const
{
    return costo_totale/quantita_rifornita;
}

float Rifornimento::getConsumo() const
{
    return km_parziale/quantita_rifornita;
}

Rifornimento::tipo_r Rifornimento::getTipoRifornimento() const
{
    return tipo_rifornimento;
}

std::string Rifornimento::getUnitaMisura() const
{
    return unita;
}
