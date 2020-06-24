#include "veicolotermico.h"

VeicoloTermico::VeicoloTermico() : tipo_rifornimento(Rifornimento::BENZINA)
{

}

u_int VeicoloTermico::getPesoTrasportabile(u_short num_passeggeri) const
{
    return Veicolo::getPesoTrasportabile(num_passeggeri) - (capacita_serbatoio*0.75);
}

u_int VeicoloTermico::getKmAutonomia() const
{
    return 0;
}

u_short VeicoloTermico::getCavalli() const
{
    return cavalli_termici;
}

u_short VeicoloTermico::getKw() const
{
    return cavalli_termici*0.745699872;
}

void VeicoloTermico::addRifornimento(Rifornimento *r)
{
    Veicolo::addRifornimento(r);
    setSerbatoio(100);
}

void VeicoloTermico::setSerbatoio(const float percentuale_serbatoio)
{
    //TO DO: controlli validità
    pieno_serbatoio=percentuale_serbatoio;
}

bool VeicoloTermico::checkCorrettezzaRifornimento(const Rifornimento& r) const
{
    // TO DO: controlli su tutti i campi
    return (r.getTipoRifornimento()==this->tipo_rifornimento);
}
