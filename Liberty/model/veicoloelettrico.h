#ifndef VEICOLOELETTRICO_H
#define VEICOLOELETTRICO_H

#include "veicolo.h"

class VeicoloElettrico : public virtual Veicolo
{
    public:
        // Costruttori
        VeicoloElettrico(const string &mar, const string &model, const float &bat, const u_short &cav=0, const u_int &peso_vuoto=0, const u_int &posti=0, const u_int &km_i=0, const u_int &tag=0, const u_int &p_max=0, const float &lun=0, const float &lar=0, const float &alt=0);
        VeicoloElettrico(const VeicoloElettrico &) = default;
        //VeicoloElettrico &operator=(const VeicoloElettrico&) = default; // c'è già senza dichiararlo

        // Metodi costanti
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        float getConsumoElettricoMedio() const; // In km/Kw
        const float& getBatteria() const; //capienza batteria

        // Metodi non costanti
        void setBatteria(const float &capacita_batteria);
        void setCvElettrici(const u_short &);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento &) const override;

    private:
        float getKwTotaliRicaricati() const;

        u_short cavalli_elettrici;
        static Rifornimento::tipo_r tipo_rifornimento;
        float capacita_batteria;
};

#endif // VEICOLOELETTRICO_H
