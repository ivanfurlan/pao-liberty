#ifndef VEICOLOELETTRICO_H
#define VEICOLOELETTRICO_H

#include "veicolo.h"

class VeicoloElettrico : public Veicolo
{
    public:
        // Costruttori
        VeicoloElettrico();

        // Metodi costanti
        virtual u_int getKmAutonomia() const;
        virtual u_short getCavalli() const;
        virtual u_short getKw() const;
        float getBatteria() const;

        //Metodi non costanti
        virtual void addRifornimento(Rifornimento*);
        void setBatteria(const float);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento&) const;

        static Rifornimento::tipo_r tipo_rifornimento;
        float capacita_batteria;

    private:
        float carica_batteria; //In % quanto carica è la batteria
        u_short cavalli_elettrici;
};

#endif // VEICOLOELETTRICO_H
