#ifndef VEICOLOELETTRICO_H
#define VEICOLOELETTRICO_H

#include "veicolo.h"

class VeicoloElettrico : public virtual Veicolo
{
    public:
        // Costruttori
        VeicoloElettrico(const string, const string, const float, const u_short = 0, const u_int = 0, const u_int = 0, const u_short = 0, const u_int = 0, const float = 0, const float = 0, const float = 0);

        // Metodi costanti
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        float getConsumoElettricoMedio() const; // In km/Kw
        float getBatteria() const; //capienza batteria

        // Metodi non costanti
        virtual void addRifornimento(Rifornimento*) override;
        void setBatteria(const float); // TO DO: forse non serve

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento&) const override;

        static Rifornimento::tipo_r tipo_rifornimento;
        float capacita_batteria;

    private:
        float getKwTotaliRicaricati() const;

        float carica_batteria; // In % quanto carica è la batteria // TO DO: forse non serve
        u_short cavalli_elettrici;
};

#endif // VEICOLOELETTRICO_H
