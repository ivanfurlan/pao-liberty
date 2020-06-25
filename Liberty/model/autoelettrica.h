#ifndef AUTOELETTRICA_H
#define AUTOELETTRICA_H

#include "veicoloelettrico.h"

class AutoElettrica : public VeicoloElettrico
{
    public:
        // Costruttori
        AutoElettrica(const string, const string, const float, const u_short, const u_int, const u_int, const u_short, const u_int, const float, const float, const float);

        // Metodi costanti
        virtual bool fareTagliando() const override;
};

#endif // AUTOELETTRICA_H
