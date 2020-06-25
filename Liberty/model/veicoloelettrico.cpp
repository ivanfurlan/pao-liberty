#include "veicoloelettrico.h"

Rifornimento::tipo_r VeicoloElettrico::tipo_rifornimento=Rifornimento::ELETTRICITA;

VeicoloElettrico::VeicoloElettrico(const std::string mar, const std::string model, const float bat, const u_short cav, const u_int peso_vuoto, const u_int p_max, const u_short pass, const u_int tag, const float lun, const float lar, const float alt)
    :Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), capacita_batteria(bat), cavalli_elettrici(cav)
{

}

u_int VeicoloElettrico::getKmAutonomia() const
{
    return capacita_batteria*getConsumoElettricoMedio();
}

u_short VeicoloElettrico::getCavalli() const
{
    return cavalli_elettrici;
}

u_short VeicoloElettrico::getKw() const
{
    return cavalli_elettrici*0.745699872;
}

float VeicoloElettrico::getConsumoElettricoMedio() const
{
    return getKmTotaliVeicolo() / getKwTotaliRicaricati();
}

float VeicoloElettrico::getBatteria() const
{
    return capacita_batteria;
}

void VeicoloElettrico::addRifornimento(Rifornimento *r)
{
    Veicolo::addRifornimento(r);
    setBatteria(100);
}

void VeicoloElettrico::setBatteria(const float percentuale_batteria)
{
    // TO DO: controlli validita
    carica_batteria=percentuale_batteria;
}

bool VeicoloElettrico::checkCorrettezzaRifornimento(const Rifornimento& r) const
{
    return (r.getTipoRifornimento()==this->tipo_rifornimento) && \
            (r.getQuantita()<=this->capacita_batteria) && \
            Veicolo::checkCorrettezzaRifornimento(r);
}

float VeicoloElettrico::getKwTotaliRicaricati() const
{
    return Veicolo::getTotaleRifornito(tipo_rifornimento);
}

