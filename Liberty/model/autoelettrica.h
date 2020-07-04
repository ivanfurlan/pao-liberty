#ifndef AUTOELETTRICA_H
#define AUTOELETTRICA_H

#include "veicoloelettrico.h"

class AutoElettrica : public VeicoloElettrico
{
    public:
        // Costruttori
        AutoElettrica(const string &mar, const string &model, const float &bat, const u_short &cav=0, const u_int &peso_vuoto=0, const u_int &posti=0, const u_int &km_i=0, const u_int &tag=0, const string& unita = "Kwh", const u_int &p_max=0, const float &lun=0, const float &lar=0, const float &alt=0);
        AutoElettrica(const AutoElettrica&) = default;
        //AutoElettrica &operator=(const AutoElettrica&) = default; // c'è già senza dichiararlo

        // Metodi costanti
        virtual bool fareTagliando() const override;
        virtual AutoElettrica * clone() const override;
};

#endif // AUTOELETTRICA_H
