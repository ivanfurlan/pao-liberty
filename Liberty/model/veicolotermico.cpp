#include "veicolotermico.h"

VeicoloTermico::VeicoloTermico(const std::string mar, const std::string model, const Rifornimento::tipo_r tr, const float ser, const u_short cav, const u_int peso_vuoto, const u_int p_max, const u_short pass, const u_int tag, const float lun, const float lar, const float alt)
    :Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), tipo_rifornimento(tr), capacita_serbatoio(ser), cavalli_termici(cav)
{

}

u_int VeicoloTermico::getPesoTrasportabile(u_short num_passeggeri) const
{
    return Veicolo::getPesoTrasportabile(num_passeggeri) - (capacita_serbatoio*0.75);
}

u_int VeicoloTermico::getKmAutonomia() const
{
    return getConsumoCarburanteMedio()*getSerbatoio();
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

float VeicoloTermico::getConsumoCarburanteMedio() const
{
    return getKmTotaliVeicolo() / getTotaleRifornito();
}

float VeicoloTermico::getSerbatoio() const
{
    return capacita_serbatoio;
}

string VeicoloTermico::getTipoRifornimento() const
{
    return Rifornimento::tipo_string[tipo_rifornimento];
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
    return (r.getTipoRifornimento()==this->tipo_rifornimento) && \
            (r.getQuantita()<=this->capacita_serbatoio) && \
            Veicolo::checkCorrettezzaRifornimento(r);
}

float VeicoloTermico::getTotaleRifornito() const
{
    return Veicolo::getTotaleRifornito(tipo_rifornimento);
}
