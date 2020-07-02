#ifndef VEICOLOTERMICO_H
#define VEICOLOTERMICO_H

#include "veicolo.h"

class VeicoloTermico : public virtual Veicolo
{
    public:
        // Costruttori
        VeicoloTermico(const string mar, const string model, const Rifornimento::tipo_r tr, const float ser, const u_short cav=0, const u_int peso_vuoto=0, const u_int posti=0, const u_int km_i=0, const u_int tag=0, const u_int p_max=0, const float lun=0, const float lar=0, const float alt=0);

        // Metodi costanti
        virtual u_int getPesoTrasportabile(const u_short num_passeggeri = 0) const override;
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        float getConsumoCarburanteMedio() const; // in km per unità di carburante
        float getSerbatoio() const; // capienza serbatoio
        string getTipoRifornimento() const;

        // Metodi non costanti
        void setSerbatoio(const float);
        void setCvTermici(const u_short);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento&) const override;

        const Rifornimento::tipo_r tipo_rifornimento;
        float capacita_serbatoio;

    private:
        float getTotaleRifornito() const;

        u_short cavalli_termici;
};

#endif // VEICOLOTERMICO_H
