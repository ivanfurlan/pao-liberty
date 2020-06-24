#ifndef AUTOIBRIDA_H
#define AUTOIBRIDA_H

#include "veicolotermico.h"
#include "veicoloelettrico.h"

class AutoIbrida : public VeicoloTermico, VeicoloElettrico
{
    public:
        // Costruttori
        AutoIbrida();

        // Metodi costanti
        virtual u_int getKmAutonomia() const;
        virtual u_short getCavalli() const;
        virtual u_short getKw() const;
        virtual bool fareTagliando() const;

        // Metodi non costanti
        virtual void addRifornimento(Rifornimento*);
};

#endif // AUTOIBRIDA_H
