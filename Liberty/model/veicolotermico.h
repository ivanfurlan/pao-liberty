#ifndef VEICOLOTERMICO_H
#define VEICOLOTERMICO_H

#include "veicolo.h"

class VeicoloTermico : public virtual Veicolo
{
    public:
        // Costruttori
        VeicoloTermico(const string, const string, const Rifornimento::tipo_r, const float, const u_short = 0, const u_int = 0, const u_int = 0, const u_short = 0, const u_int = 0, const float = 0, const float = 0, const float = 0);

        // Metodi costanti
        virtual u_int getPesoTrasportabile(const u_short num_passeggeri = 0) const override;
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        float getConsumoCarburanteMedio() const; // in km per unità di carburante
        float getSerbatoio() const; // capienza serbatoio
        string getTipoRifornimento() const;

        // Metodi non costanti
        virtual void addRifornimento(Rifornimento*) override;
        void setSerbatoio(const float); // TO DO: forse non serve
        void setCvTermici(const u_short);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento&) const override;

        const Rifornimento::tipo_r tipo_rifornimento;
        float capacita_serbatoio;

    private:
        float getTotaleRifornito() const;

        float pieno_serbatoio; // In % quanto pieno è il serbatorio // TO DO: forse non serve
        u_short cavalli_termici;
};

#endif // VEICOLOTERMICO_H
