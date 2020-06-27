#ifndef AUTOELETTRICA_H
#define AUTOELETTRICA_H

#include "veicoloelettrico.h"

class AutoElettrica : public VeicoloElettrico
{
    public:
        // Costruttori
        AutoElettrica(const string, const string, const float, const u_short = 0, const u_int = 0, const u_int = 0, const u_short = 0, const u_int = 0, const float = 0, const float = 0, const float = 0);

        // Metodi costanti
        virtual bool fareTagliando() const override;
};

#endif // AUTOELETTRICA_H
