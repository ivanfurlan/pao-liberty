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

        static map<tipo_r, string> tipo_string; // Associo ad ogni tipo una stringa
        static map<string, tipo_r> string_tipo; // Associo ad ogni stringa un tipo

        // Costruttori
        Rifornimento(const tipo_r t, const float km, const float qt, const float c, string unita = "l");

        // Metodi Costanti
        float getCostoRifornimento() const;
        float getKmParziale() const;
        float getQuantita() const;
        float getCostoPerUnita() const;
        float getConsumo() const; // In km per unità
        tipo_r getTipoRifornimento() const;
        string getUnitaMisura() const;

    private:
        string unita;
        tipo_r tipo_rifornimento; // In litri o Kw
        float km_parziale;
        float quantita_rifornita;
        float costo_totale;
};

#endif // RIFORNIMENTO_H
