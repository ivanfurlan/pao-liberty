#ifndef AUTOTERMICA_H
#define AUTOTERMICA_H

#include "veicolotermico.h"

class AutoTermica : public VeicoloTermico
{
    public:
        // Costruttori
        AutoTermica(const string, const string, const Rifornimento::tipo_r, const float, const u_short, const u_int, const u_int, const u_short, const u_int, const float, const float, const float);

        // Metodi costanti
        virtual bool fareTagliando() const override;
};

#endif // AUTOTERMICA_H
