#ifndef MODEL_H
#define MODEL_H

#include "veicolo.h"
#include "../container.h"

class Model
{
    public:
        // Costruttori
        Model();
        ~Model();

        // Metodi costanti
        Container<Veicolo* >::const_iterator getVeicoloAt(const u_int&) const;
        u_int count() const;
        // get: Veicolo meno costoso perkm, Veicolo più costoso per km, get veicolo con Autonomia con un pieno maggiore

        // Metodi non costanti
        void add(Veicolo *);
        void rifornisci(Veicolo *, Rifornimento *);
        void deleteV(const Container<Veicolo *>::const_iterator &);
        void deleteAll();
        void eliminaRifornimento(u_int,u_int);
        void modificaRifornimento(Veicolo *,u_int, Rifornimento *);

    private:
        Container<Veicolo*> veicoli;
};

#endif // MODEL_H
