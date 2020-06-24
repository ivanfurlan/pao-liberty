#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include "rifornimento.h"
#include <list>

using std::string;
using std::list;

class Veicolo
{ // TO DO: gestire la memoria e mettere passaggi per  riferimento o puntatore ovunque sia possibile
    public:
        // Costruttori
        Veicolo();

        // Metodi costanti
        string getNomeEsteso() const;
        u_int getPeso() const;
        u_short getPosti() const;
        const Rifornimento& getUltimoRifornimento() const;
        u_int getKmTotaliVeicolo() const;
        u_int getUltimoTagliando() const;
        virtual u_int getPesoTrasportabile(const u_short num_passeggeri = 0) const;
        virtual u_int getKmAutonomia() const = 0;
        virtual u_short getCavalli() const = 0;
        virtual u_short getKw() const = 0;
        virtual bool fareTagliando() const = 0;

        // Metodi non costanti
        virtual void addRifornimento(Rifornimento*);
        void doTagliando(const u_int);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento& ) const = 0;

        list<Rifornimento* > rifornimenti; //TO DO: mettere irifornimenti const

    private:
        string marca; // Es: "Ford"
        string modello; // Es: "Fiesta ST 2019"
        //float prezzo; // In Euro
        float largheza, lunghezza, altezza; // In cm
        u_short num_ruote;
        u_int peso; // In kg (senza decimali)
        u_int peso_max;
        u_short passeggeri_max;
        u_short coppia; // In Nm
        u_short velocita_max;
        u_int ultimo_tagliando_km;
};

#endif // VEICOLO_H
