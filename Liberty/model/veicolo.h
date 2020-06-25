#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include "rifornimento.h"
#include <list>

using std::string;
using std::list;

class Veicolo
{ // TO DO: DA CONTROLLARE/FARE: gestire la memoria e mettere passaggi per riferimento o puntatore ovunque sia possibile
    public:
        // Costruttori
        Veicolo(const string, const string = "Sconosciuto", const u_int = 0, const u_int = 0, const u_short = 0, const u_int = 0, const float = 0, const float = 0, const float = 0);
        virtual ~Veicolo();

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
        void update(string, string, float, float, float,  u_int, u_int, u_short, u_int);
        void doTagliando(const u_int);
        void setName(string, string);
        void setDimensioni(float, float, float);
        void setPesi(u_int, u_int);
        void setMaxPasseggieri(u_short);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento& ) const;
        float getTotaleRifornito(const Rifornimento::tipo_r) const;

        list<Rifornimento* > rifornimenti; //TO DO: mettere i rifornimenti const (?)

    private:
        string marca; // Es: "Ford"
        string modello; // Es: "Fiesta ST 2019"
        u_int peso; // In kg (senza decimali)
        u_int peso_max;
        u_short passeggeri_max;
        u_int ultimo_tagliando_km;
        float lunghezza, largheza, altezza; // In cm
};

#endif // VEICOLO_H
