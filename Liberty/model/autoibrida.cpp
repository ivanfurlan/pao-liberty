#include "autoibrida.h"

AutoIbrida::AutoIbrida(const std::string mar, const std::string model, const Rifornimento::tipo_r tr, const float ser, const float bat, const u_short cav_t, const u_short cav_e, const u_int peso_vuoto, const u_int p_max, const u_short pass, const u_int tag, const float lun, const float lar, const float alt)
    : Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), VeicoloTermico(mar, model, tr, ser, cav_t, peso_vuoto, p_max, pass, tag, lun, lar, alt), VeicoloElettrico(mar, model, bat, cav_e, peso_vuoto, p_max, pass, tag, lun, lar, alt)
{
    // TO DO: provare a mettere solo i primi campi nel costruttore del veicolo termico ed elettrico
}

u_int AutoIbrida::getKmAutonomia() const
{
    u_int km_carburante = VeicoloTermico::getKmAutonomia();
    u_int km_batteria = VeicoloElettrico::getKmAutonomia();
    if(km_carburante<km_batteria)
        return km_carburante;
    else
        return km_batteria+((km_carburante-km_batteria)*0.7); // Quando si scarica la batteria ipotizzo che il solo motore termico consumi di più e faccia il 30% in meno di km rispetto alla previsione con la batteria carica
}

bool AutoIbrida::fareTagliando() const
{
    return (getKmTotaliVeicolo() - getUltimoTagliando() >= 15000);
}

void AutoIbrida::addRifornimento(Rifornimento *r)
{
    if(r->getTipoRifornimento()==Rifornimento::ELETTRICITA)
        VeicoloElettrico::addRifornimento(r);
    else
        VeicoloTermico::addRifornimento(r);
}

bool AutoIbrida::checkCorrettezzaRifornimento(const Rifornimento & r) const
{
    if(r.getTipoRifornimento()==VeicoloElettrico::tipo_rifornimento)
        return VeicoloElettrico::checkCorrettezzaRifornimento(r);
    else if(r.getTipoRifornimento()==VeicoloTermico::tipo_rifornimento)
        return VeicoloTermico::checkCorrettezzaRifornimento(r);
    else
        return false;
}

u_short AutoIbrida::getCavalli() const
{
    return VeicoloTermico::getCavalli()+VeicoloElettrico::getCavalli();
}

u_short AutoIbrida::getKw() const
{
    return (VeicoloTermico::getCavalli()+VeicoloElettrico::getCavalli())*0.745699872;
}
