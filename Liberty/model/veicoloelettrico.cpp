#include "veicoloelettrico.h"

Rifornimento::tipo_r VeicoloElettrico::tipo_rifornimento=Rifornimento::ELETTRICITA;

VeicoloElettrico::VeicoloElettrico(const std::string &mar, const std::string &model, const float &bat, const u_short &cav, const u_int &peso_vuoto, const u_int &posti, const u_int &km_i, const u_int &tag, const string& unita, const u_int &p_max, const float &lun, const float &lar, const float &alt)
    :Veicolo(mar, model, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt), cavalli_elettrici(cav), capacita_batteria(bat), unita_rifornimento(unita)
{
    if(capacita_batteria<=0)
        throw std::domain_error("La capacità della batteria deve essere maggiore di 0");
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
    // Non uso getCavalli() perché è virtuale e in caso di veicoli con eritarietà multipla (ES AutoIbrida) voglio che si possa sapere i kw solo elettrici, altrimenti prenderebbe i totali
    return cavalli_elettrici*0.745699872;
}

float VeicoloElettrico::getConsumoElettricoMedio() const
{
    return getSommaKmRifornimenti() / getKwTotaliRicaricati();
}

const float& VeicoloElettrico::getBatteria() const
{
    return capacita_batteria;
}

const std::string &VeicoloElettrico::getUnitaRifornimento() const
{
    return unita_rifornimento;
}

void VeicoloElettrico::setBatteria(const float &capacita_batteria)
{
    if(capacita_batteria<=0){
        throw std::domain_error("La capacità della batteria deve essere maggiore di 0");
    }
    this->capacita_batteria=capacita_batteria;
}

void VeicoloElettrico::setCvElettrici(const u_short &ce)
{
    cavalli_elettrici=ce;
}

VeicoloElettrico::VeicoloElettrico(const float &bat, const u_short &cav, const std::string &unita) : cavalli_elettrici(cav), capacita_batteria(bat), unita_rifornimento(unita)
{
    if(capacita_batteria<=0)
        throw std::domain_error("La capacità della batteria deve essere maggiore di 0");
}

bool VeicoloElettrico::checkCorrettezzaRifornimento(const Rifornimento &r) const
{
    return (r.getTipoRifornimento()==this->tipo_rifornimento) && \
            (r.getQuantita()<=this->capacita_batteria) && \
            Veicolo::checkCorrettezzaRifornimento(r);
}

float VeicoloElettrico::getKwTotaliRicaricati() const
{
    return Veicolo::getTotaleRifornito(tipo_rifornimento);
}

