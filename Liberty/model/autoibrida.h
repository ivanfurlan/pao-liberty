#ifndef AUTOIBRIDA_H
#define AUTOIBRIDA_H

#include "veicolotermico.h"
#include "veicoloelettrico.h"

class AutoIbrida : public VeicoloTermico, public VeicoloElettrico
{
    public:
        // Costruttori
        AutoIbrida(const string, const string, const Rifornimento::tipo_r, const float, const float, const u_short = 0, const u_short = 0, const u_int = 0, const u_int = 0, const u_short = 0, const u_int = 0, const float = 0, const float = 0, const float = 0);
        ~AutoIbrida() = default;
        // Metodi costanti
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        virtual bool fareTagliando() const override;


        // Metodi non costanti
        virtual void addRifornimento(Rifornimento*) override;
    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento& ) const override;
};

#endif // AUTOIBRIDA_H
