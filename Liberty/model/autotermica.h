#ifndef AUTOTERMICA_H
#define AUTOTERMICA_H

#include "veicolotermico.h"

class AutoTermica : public VeicoloTermico
{
    public:
        // Costruttori
        AutoTermica(const string &mar, const string &model, const Rifornimento::tipo_r &tr, const float &ser, const u_short &cav=0, const u_int &peso_vuoto=0, const u_int &posti=0, const u_int &km_i=0, const u_int &tag=0, const string& unita = "l", const u_int &p_max=0, const float &lun=0, const float &lar=0, const float &alt=0);
        AutoTermica(const AutoTermica&) = default;

        // Metodi costanti
        virtual bool fareTagliando() const override;
        virtual AutoTermica * clone() const override;
};

#endif // AUTOTERMICA_H
