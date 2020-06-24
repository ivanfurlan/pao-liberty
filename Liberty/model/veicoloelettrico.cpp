#include "veicoloelettrico.h"

Rifornimento::tipo_r VeicoloElettrico::tipo_rifornimento=Rifornimento::ELETTRICITA;

VeicoloElettrico::VeicoloElettrico()
{

}

u_int VeicoloElettrico::getKmAutonomia() const
{
    return 0;
}

u_short VeicoloElettrico::getCavalli() const
{
    return cavalli_elettrici;
}

u_short VeicoloElettrico::getKw() const
{
    return cavalli_elettrici*0.745699872;
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
    // TO DO: controlli su tutti i campi
    return (r.getTipoRifornimento()==this->tipo_rifornimento);
}

