#include "autoelettrica.h"

AutoElettrica::AutoElettrica(const std::string mar, const std::string model, const float bat, const u_short cav, const u_int peso_vuoto, const u_int p_max, const u_short pass, const u_int tag, const float lun, const float lar, const float alt)
    : Veicolo(mar, model, peso_vuoto, p_max, pass, tag, lun, lar, alt), VeicoloElettrico(mar, model, bat, cav, peso_vuoto, p_max, pass, tag, lun, lar, alt)
{
    // TO DO: provare a mettere solo i primi campi nel costruttore del veicolo elettrico
}

bool AutoElettrica::fareTagliando() const
{
    return (this->getKmTotaliVeicolo() - this->getUltimoTagliando() >= 15000);
}
