#include "veicolotermico.h"

VeicoloTermico::VeicoloTermico(const std::string &mar, const std::string &model, const Rifornimento::tipo_r &tr, const float &ser, const u_short &cav, const u_int &peso_vuoto, const u_int &posti, const u_int &km_i, const u_int &tag, const string& unita, const u_int &p_max, const float &lun, const float &lar, const float &alt)
    :Veicolo(mar, model, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt), cavalli_termici(cav), tipo_rifornimento(tr), capacita_serbatoio(ser), unita_rifornimento(unita)
{
    if(capacita_serbatoio<=0)
        throw std::domain_error("La capacità del serbatoio deve essere maggiore di 0");
}

u_int VeicoloTermico::getPesoTrasportabile(const u_short &num_passeggeri) const
{
    // il controllo che il num_passeggeri sia valido è già fatto dal metodo di Veicolo che viene richiamato
    return Veicolo::getPesoTrasportabile(num_passeggeri) - (capacita_serbatoio*((tipo_rifornimento==Rifornimento::DIESEL)?0.835:0.73));
}

u_int VeicoloTermico::getKmAutonomia() const
{
    return getConsumoCarburanteMedio()*getSerbatoio();
}

u_short VeicoloTermico::getCavalli() const
{
    return cavalli_termici;
}

u_short VeicoloTermico::getKw() const
{
    // Non uso getCavalli() perché è virtuale e in caso di veicoli con eritarietà multipla (ES AutoIbrida) voglio che si possa sapere i kw solo termici, altrimenti prenderebbe i totali
    return cavalli_termici*0.745699872;
}

float VeicoloTermico::getConsumoCarburanteMedio() const
{
    return getSommaKmRifornimenti() / getTotaleRifornito();
}

const float& VeicoloTermico::getSerbatoio() const
{
    return capacita_serbatoio;
}

const string& VeicoloTermico::getTipoRifornimento() const
{
    return Rifornimento::tipo_string[tipo_rifornimento];
}

const Rifornimento::tipo_r& VeicoloTermico::getTipoRifornimentoEnum() const
{
    return tipo_rifornimento;
}

const std::string &VeicoloTermico::getUnitaRifornimento() const
{
    return unita_rifornimento;
}

void VeicoloTermico::setSerbatoio(const float &capacita_serbatoio)
{
    if(capacita_serbatoio<=0){
        throw std::domain_error("La capacità del serbatoio deve essere maggiore di 0");
    }
    this->capacita_serbatoio=capacita_serbatoio;
}

void VeicoloTermico::setCvTermici(const u_short &ct)
{
    cavalli_termici=ct;
}

bool VeicoloTermico::checkCorrettezzaRifornimento(const Rifornimento &r) const
{
    return (r.getTipoRifornimento()==this->tipo_rifornimento) && \
            (r.getQuantita()<=this->capacita_serbatoio) && \
            Veicolo::checkCorrettezzaRifornimento(r);
}

float VeicoloTermico::getTotaleRifornito() const
{
    return Veicolo::getTotaleRifornito(tipo_rifornimento);
}
