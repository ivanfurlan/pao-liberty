#ifndef RIFORNIMENTO_H
#define RIFORNIMENTO_H

#include <string>
#include <map>

using std::string;
using std::map;

class Rifornimento
{
    public:
        // Tipologie di rifornimento
        enum tipo_r{DIESEL, BENZINA, ELETTRICITA};

        static map<tipo_r, string> tipo_string;
        static map<string, tipo_r> string_tipo;

        // Costruttori
        Rifornimento(const tipo_r t, const float km, const float qt, const float cpu);

        // Metodi Costanti
        float getCostoRifornimento() const;
        float getKm() const;
        float getQuantita() const;
        float getCostoPerUnita() const;
        tipo_r getTipoRifornimento() const;

    private:
        tipo_r tipo_rifornimento; // In litri o Kw/h
        float km_totali;
        float quantita_rifornita;
        float costo_per_unita;
};

#endif // RIFORNIMENTO_H
