#include "veicolotermico.h"

VeicoloTermico::VeicoloTermico(const std::string mar, const std::string model, const Rifornimento::tipo_r tr, const float ser, const u_short cav, const u_int peso_vuoto, const u_int posti, const u_int km_i, const u_int tag, const u_int p_max, const float lun, const float lar, const float alt)
    :Veicolo(mar, model, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt), tipo_rifornimento(tr), capacita_serbatoio(ser), cavalli_termici(cav)
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
    // Non uso getCavalli() perché è virtuale e in caso di veicoli con eritarietà multipla voglio che si possa sapere i kw solo termici, altrimenti prenderebbe i totali
    return cavalli_termici*0.745699872;
}

float VeicoloTermico::getConsumoCarburanteMedio() const
{
    return getSommaKmRifornimenti() / getTotaleRifornito();
}

float VeicoloTermico::getSerbatoio() const
{
    return capacita_serbatoio;
}

string VeicoloTermico::getTipoRifornimento() const
{
    return Rifornimento::tipo_string[tipo_rifornimento];
}

void VeicoloTermico::setSerbatoio(const float capacita_serbatoio)
{
    this->capacita_serbatoio=capacita_serbatoio;
}

void VeicoloTermico::setCvTermici(const u_short ct)
{
    cavalli_termici=ct;
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
