#ifndef AUTOELETTRICA_H
#define AUTOELETTRICA_H

#include "veicoloelettrico.h"

class AutoElettrica : public VeicoloElettrico
{
    public:
        // Costruttori
        AutoElettrica();

        // Metodi costanti
        virtual bool fareTagliando() const;
};

#endif // AUTOELETTRICA_H
