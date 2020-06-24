#ifndef AUTOTERMICA_H
#define AUTOTERMICA_H

#include "veicolotermico.h"

class AutoTermica : public VeicoloTermico
{
    public:
        // Costruttori
        AutoTermica();

        // Metodi costanti
        virtual bool fareTagliando() const;
};

#endif // AUTOTERMICA_H
