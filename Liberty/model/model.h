#ifndef MODEL_H
#define MODEL_H

#include "veicolo.h"
#include "../container.h"

class Model
{
    public:
        // Costruttori
        ~Model();

        // Metodi costanti
        Container<Veicolo* >::const_iterator getVeicoloAt(const u_int&) const;
        u_int count() const;

        // Metodi non costanti
        void add(Veicolo *);
        void rifornisci(Veicolo *, Rifornimento *);
        void deleteV(const Container<Veicolo *>::const_iterator &);
        void deleteAll();
        void eliminaRifornimento(const u_int &, list<Rifornimento *>::const_iterator);
        void modificaRifornimento(Veicolo *, list<Rifornimento *>::const_iterator, Rifornimento *);

    private:
        Container<Veicolo*> veicoli;
};

#endif // MODEL_H
