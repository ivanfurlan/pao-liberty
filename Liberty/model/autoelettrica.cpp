#include "autoelettrica.h"

AutoElettrica::AutoElettrica(const std::string mar, const std::string model, const float bat=0, const u_short cav=0, const u_int peso_vuoto=0, const u_int p_max=0, const u_short pass=0, const u_int tag=0, const float lun=0, const float lar=0, const float alt=0)
    : Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), VeicoloElettrico(mar, model, bat, cav, peso_vuoto, p_max, pass, tag, lun, lar, alt)
{
    // TO DO: provare a mettere solo i primi campi nel costruttore del veicolo elettrico
}

bool AutoElettrica::fareTagliando() const
{
    return (this->getKmTotaliVeicolo() - this->getUltimoTagliando() >= 15000);
}
