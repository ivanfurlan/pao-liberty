#ifndef VEICOLOELETTRICO_H
#define VEICOLOELETTRICO_H

#include "veicolo.h"

class VeicoloElettrico : public virtual Veicolo
{
    public:
        // Costruttori
        VeicoloElettrico(const string &mar, const string &model, const float &bat, const u_short &cav=0, const u_int &peso_vuoto=0, const u_int &posti=0, const u_int &km_i=0, const u_int &tag=0, const string& unita = "Kwh", const u_int &p_max=0, const float &lun=0, const float &lar=0, const float &alt=0);
        VeicoloElettrico(const VeicoloElettrico &) = default;

        // Metodi costanti
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        float getConsumoElettricoMedio() const; // In km/Kw
        const float& getBatteria() const; //capienza batteria
        const string &getUnitaRifornimento() const;

        // Metodi non costanti
        void setBatteria(const float &capacita_batteria);
        void setCvElettrici(const u_short &);

    protected:
        // costruttore solo per le classi derivate, così non devono passare i dati di Veicolo
        VeicoloElettrico(const float &bat, const u_short &cav=0, const string& unita = "Kwh");

        virtual bool checkCorrettezzaRifornimento(const Rifornimento &) const override;

    private:
        float getKwTotaliRicaricati() const;

        u_short cavalli_elettrici;
        static Rifornimento::tipo_r tipo_rifornimento;
        float capacita_batteria;
        string unita_rifornimento;
};

#endif // VEICOLOELETTRICO_H
