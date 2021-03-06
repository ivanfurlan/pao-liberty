#include "autoelettrica.h"

AutoElettrica::AutoElettrica(const std::string &mar, const std::string &model, const float &bat, const u_short &cav, const u_int &peso_vuoto, const u_int &posti, const u_int &km_i, const u_int &tag, const string& unita, const u_int &p_max, const float &lun, const float &lar, const float &alt)
    : Veicolo(mar, model, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt), VeicoloElettrico(bat, cav, unita)
{

}

bool AutoElettrica::fareTagliando() const
{
    return (getKmTotaliVeicolo() - getUltimoTagliando() >= 15000);
}

AutoElettrica *AutoElettrica::clone() const
{
    return new AutoElettrica(*this);
}
