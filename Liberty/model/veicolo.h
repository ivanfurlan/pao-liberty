#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <list>
#include <stdexcept>

#include "rifornimento.h"

using std::string;
using std::list;

class Veicolo
{ // TO DO: DA CONTROLLARE/FARE: gestire la memoria e mettere passaggi per riferimento o puntatore ovunque sia possibile
    public:
        // Costruttori
        Veicolo(const string mar = "Sconosciuta", const string model = "Sconosciuto", const u_int &peso_vuoto=0, const u_short &post=0, const u_int &km_i=0, const u_int &tag=0, const u_int &p_max=0, const float &lun=0, const float &lar=0, const float &alt=0);
        Veicolo(const Veicolo&);
        Veicolo& operator=(const Veicolo&);
        virtual ~Veicolo();

        // Metodi costanti
        string getNomeEsteso() const;
        const string& getMarca() const;
        const string& getModello() const;
        const u_int& getPeso() const;
        const u_short& getPosti() const;
        list<Rifornimento *>::const_iterator getUltimoRifornimento() const;
        const u_int& getUltimoTagliando() const;
        const list<Rifornimento *>& getRifornimenti() const;
        const u_int& getKmIniziali() const;
        u_int getKmTotaliVeicolo() const;
        virtual u_int getSommaKmRifornimenti() const;
        virtual u_int getPesoTrasportabile(const u_short &num_passeggeri = 0) const; // non usato in GUI
        virtual u_int getKmAutonomia() const = 0;
        virtual u_short getCavalli() const = 0;
        virtual u_short getKw() const;
        virtual bool fareTagliando() const = 0;
        virtual Veicolo * clone() const = 0;

        // Metodi non costanti
        void addRifornimento(Rifornimento*);
        void doTagliando(const u_int &);
        void setName(const string &, const string &);
        void setDimensioni(const float &, const float &, const float &);
        void setPeso(const u_int &);
        void setPosti(const u_short &);
        void setKmIniziali(const u_int &);
        void eliminaRifornimento(const list<Rifornimento *>::const_iterator &);
        void modificaRifornimento(const list<Rifornimento *>::const_iterator &, const Rifornimento *);

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento & ) const;
        float getTotaleRifornito(const Rifornimento::tipo_r &) const;

        list<Rifornimento* > rifornimenti;

    private:
        list<Rifornimento *> copiaRifornimenti(const list<Rifornimento *> &) const;
        void distruggiRifornimenti(const list<Rifornimento *> &) const;

        string marca; // Es: "Ford"
        string modello; // Es: "Fiesta ST 2019"
        u_int peso; // In kg (senza decimali)
        u_int km_iniziali;
        u_short posti;
        u_int ultimo_tagliando_km;
        u_int peso_max; // Peso massimo a pieno carico // non usato in GUI
        float lunghezza, larghezza, altezza; // Dimensioni del veicolo
};

#endif // VEICOLO_H
