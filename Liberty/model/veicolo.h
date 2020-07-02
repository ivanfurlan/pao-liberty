#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <list>

#include "rifornimento.h"

using std::string;
using std::list;

class Veicolo
{ // TO DO: DA CONTROLLARE/FARE: gestire la memoria e mettere passaggi per riferimento o puntatore ovunque sia possibile
    public:
        // Costruttori
        Veicolo(const string mar = "Sconosciuta", const string model = "Sconosciuto", const u_int peso_vuoto=0, const u_short post=0, const u_int km_i=0, const u_int tag=0, const u_int p_max=0, const float lun=0, const float lar=0, const float alt=0);
        virtual ~Veicolo();

        // Metodi costanti
        string getNomeEsteso() const;
        string getMarca() const;
        string getModello() const;
        u_int getPeso() const;
        u_short getPosti() const;
        const Rifornimento& getUltimoRifornimento() const;
        u_int getUltimoTagliando() const;
        const list<Rifornimento *>& getRifornimenti() const;
        u_int getKmIniziali() const;
        u_int getKmTotaliVeicolo() const;
        virtual u_int getSommaKmRifornimenti() const;
        virtual u_int getPesoTrasportabile(const u_short num_passeggeri = 0) const; // TO DO: non usato in GUI
        virtual u_int getKmAutonomia() const = 0;
        virtual u_short getCavalli() const = 0;
        virtual u_short getKw() const = 0;
        virtual bool fareTagliando() const = 0;

        // Metodi non costanti
        void addRifornimento(Rifornimento*);
        void update(string, string, float, float, float,  u_int, u_int, u_short, u_int);
        void doTagliando(const u_int);
        void setName(string, string);
        void setDimensioni(float, float, float);
        void setPeso(u_int);
        void setPosti(u_short);
        void setKmIniziali(u_int);
        void eliminaRifornimento(u_int);
        void modificaRifornimento(u_int, Rifornimento *); // TO DO: fare virtual

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento& ) const;
        float getTotaleRifornito(const Rifornimento::tipo_r) const;

        list<Rifornimento* > rifornimenti; //TO DO: mettere i rifornimenti const (?)
//TO DO: copia profonda
    private:
        string marca; // Es: "Ford"
        string modello; // Es: "Fiesta ST 2019"
        u_int peso; // In kg (senza decimali)
        u_int km_iniziali;
        u_short posti;
        u_int ultimo_tagliando_km;
        u_int peso_max; // TO DO: non usato in GUI
        float lunghezza, largheza, altezza; // TO DO: non usato in GUI
};

#endif // VEICOLO_H
