#ifndef VEICOLOTERMICO_H
#define VEICOLOTERMICO_H

#include "veicolo.h"

class VeicoloTermico : public Veicolo
{
    public:
        // Costruttori
        VeicoloTermico();

        // Metodi costanti
        virtual u_int getPesoTrasportabile(const u_short num_passeggeri = 0) const;
        virtual u_int getKmAutonomia() const;
        virtual u_short getCavalli() const;
        virtual u_short getKw() const;
        float getSerbatoio() const;

        // Metodi non costanti
        virtual void addRifornimento(Rifornimento*);
        void setSerbatoio(const float);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento&) const;

        const Rifornimento::tipo_r tipo_rifornimento;
        float capacita_serbatoio;

    private:
        float pieno_serbatoio; // In % quanto pieno è il serbatorio
        u_short cavalli_termici;
};

#endif // VEICOLOTERMICO_H
