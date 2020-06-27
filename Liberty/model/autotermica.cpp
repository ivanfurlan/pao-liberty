#include "autotermica.h"

AutoTermica::AutoTermica(const std::string mar, const std::string model, const Rifornimento::tipo_r tr, const float ser, const u_short cav, const u_int peso_vuoto, const u_int p_max, const u_short pass, const u_int tag, const float lun, const float lar, const float alt)
    : Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), VeicoloTermico(mar, model, tr, ser, cav, peso_vuoto, p_max, pass, tag, lun, lar, alt)
{
    // TO DO: provare a mettere solo i primi campi nel costruttore del veicolo termico
}

bool AutoTermica::fareTagliando() const
{
    return (this->getKmTotaliVeicolo() - this->getUltimoTagliando() >= 10000);
}
