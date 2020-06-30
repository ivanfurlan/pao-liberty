#include "rifornimento.h"

map<Rifornimento::tipo_r,std::string> Rifornimento::tipo_string = {{Rifornimento::DIESEL,"Diesel"},{Rifornimento::BENZINA,"Benzina"},{Rifornimento::ELETTRICITA,"Elettricità"}};
map<std::string,Rifornimento::tipo_r> Rifornimento::string_tipo = {{"Diesel",Rifornimento::DIESEL},{"Benzina",Rifornimento::BENZINA},{"Elettricità",Rifornimento::ELETTRICITA}};

Rifornimento::Rifornimento(Rifornimento::tipo_r t, float km, float qt, float cpu) : tipo_rifornimento(t), km_totali(km), quantita_rifornita(qt), costo_per_unita(cpu)
{
}

float Rifornimento::getCostoRifornimento() const
{
    return quantita_rifornita * costo_per_unita;
}

float Rifornimento::getKm() const
{
    return this->km_totali;
}

float Rifornimento::getQuantita() const
{
    return quantita_rifornita;
}

float Rifornimento::getCostoPerUnita() const
{
    return costo_per_unita;
}

Rifornimento::tipo_r Rifornimento::getTipoRifornimento() const
{
    return tipo_rifornimento;
}
