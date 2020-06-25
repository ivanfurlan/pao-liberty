#include "autotermica.h"

AutoTermica::AutoTermica(const std::string mar, const std::string model, const Rifornimento::tipo_r tr, const float ser=0, const u_short cav=0, const u_int peso_vuoto=0, const u_int p_max=0, const u_short pass=0, const u_int tag=0, const float lun=0, const float lar=0, const float alt=0)
    : Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), VeicoloTermico(mar, model, tr, ser, cav, peso_vuoto, p_max, pass, tag, lun, lar, alt)
{
    // TO DO: provare a mettere solo i primi campi nel costruttore del veicolo termico
}

bool AutoTermica::fareTagliando() const
{
    return (this->getKmTotaliVeicolo() - this->getUltimoTagliando() >= 10000);
}
