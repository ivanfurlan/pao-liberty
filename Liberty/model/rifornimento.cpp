#include "rifornimento.h"

map<Rifornimento::tipo_r,std::string> Rifornimento::tipo_string = {{Rifornimento::DIESEL,"Diesel"},{Rifornimento::BENZINA,"Benzina"},{Rifornimento::GPL,"Gpl"},{Rifornimento::ELETTRICITA,"Elettricità"}};
map<std::string,Rifornimento::tipo_r> Rifornimento::string_tipo = {{"Diesel",Rifornimento::DIESEL},{"Benzina",Rifornimento::BENZINA},{"Gpl",Rifornimento::GPL},{"Elettricità",Rifornimento::ELETTRICITA}};

Rifornimento::Rifornimento(const Rifornimento::tipo_r &t, const float &km, const float &qt, const float &c, const string uni) : unita(uni), tipo_rifornimento(t), km_parziale(km), quantita_rifornita(qt), costo_totale(c)
{
}

const float& Rifornimento::getCostoRifornimento() const
{
    return costo_totale;
}

const float& Rifornimento::getKmParziale() const
{
    return km_parziale;
}

const float& Rifornimento::getQuantita() const
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

const Rifornimento::tipo_r& Rifornimento::getTipoRifornimento() const
{
    return tipo_rifornimento;
}

const std::string& Rifornimento::getUnitaMisura() const
{
    return unita;
}
