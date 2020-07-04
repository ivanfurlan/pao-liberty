#include "autoibrida.h"

AutoIbrida::AutoIbrida(const std::string &mar, const std::string &model, const Rifornimento::tipo_r &tr, const float &ser, const float &bat, const u_short &cav_t, const u_short &cav_e, const u_int &peso_vuoto, const u_int &posti, const u_int &km_i, const u_int &tag, const u_int &p_max, const float &lun, const float &lar, const float &alt)
    : Veicolo(mar, model, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt),  VeicoloTermico(mar, model, tr, ser, cav_t, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt), VeicoloElettrico(mar, model, bat, cav_e, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt)
{

}

u_int AutoIbrida::getKmAutonomia() const
{
    u_int km_carburante = VeicoloTermico::getKmAutonomia();
    u_int km_batteria = VeicoloElettrico::getKmAutonomia();
    if(km_carburante<km_batteria) // controllo se finisco primala batteria o il carburante
        return km_carburante+((km_batteria-km_carburante)*0.04);// Quando finisco il carburante e ho ancora batteria ipotizzo che il solo motore elettrico consumi molto di più e faccia il 96% in meno di km rispetto alla previsione con l'aiuto del termico
    else
        return km_batteria+((km_carburante-km_batteria)*0.70); // Quando si scarica la batteria e ho ancora carburante ipotizzo che il solo motore termico consumi di più e faccia il 30% in meno di km rispetto alla previsione con l'aiuto dell'elettrico
}

bool AutoIbrida::fareTagliando() const
{
    return (getKmTotaliVeicolo() - getUltimoTagliando() >= 15000);
}

u_int AutoIbrida::getSommaKmRifornimenti() const
{
    u_int temp_e = 0;
    u_int temp_t = 0;
    for (Rifornimento* r : rifornimenti) {
        if(r->getTipoRifornimento()==Rifornimento::ELETTRICITA){
            temp_e+=r->getKmParziale();
        }else{
            temp_t+=r->getKmParziale();
        }
    }
    return (temp_t>temp_e)?temp_t:temp_e; // Ritorno i chilometri più alti, perché elettricità e carburante suppongo abbiano parziali separati

}

AutoIbrida *AutoIbrida::clone() const
{
    return new AutoIbrida(*this);

}

bool AutoIbrida::checkCorrettezzaRifornimento(const Rifornimento & r) const
{
    if(r.getTipoRifornimento()==Rifornimento::ELETTRICITA)
        return VeicoloElettrico::checkCorrettezzaRifornimento(r);
    else if(r.getTipoRifornimento()==VeicoloTermico::getTipoRifornimentoEnum())
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
    // dovevo ridefinisro per evitare l'ambiguità
    return getCavalli()*0.745699872;
}
