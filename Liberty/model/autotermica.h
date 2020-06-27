#ifndef AUTOTERMICA_H
#define AUTOTERMICA_H

#include "veicolotermico.h"

class AutoTermica : public VeicoloTermico
{
    public:
        // Costruttori
        AutoTermica(const string, const string, const Rifornimento::tipo_r, const float, const u_short = 0, const u_int = 0, const u_int = 0, const u_short = 0, const u_int = 0, const float = 0, const float = 0, const float = 0);

        // Metodi costanti
        virtual bool fareTagliando() const override;
};

#endif // AUTOTERMICA_H
