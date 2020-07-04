#include "autotermica.h"

AutoTermica::AutoTermica(const std::string &mar, const std::string &model, const Rifornimento::tipo_r &tr, const float &ser, const u_short &cav, const u_int &peso_vuoto, const u_int &posti, const u_int &km_i, const u_int &tag, const string& unita, const u_int &p_max, const float &lun, const float &lar, const float &alt)
    : Veicolo(mar, model, peso_vuoto, posti, km_i, tag, p_max, lun, lar, alt), VeicoloTermico(mar, model, tr, ser, cav, peso_vuoto, posti, km_i, tag, unita, p_max, lun, lar, alt)
{

}

bool AutoTermica::fareTagliando() const
{
    return (this->getKmTotaliVeicolo() - this->getUltimoTagliando() >= 10000);
}

AutoTermica *AutoTermica::clone() const
{
    return new AutoTermica(*this);
}
