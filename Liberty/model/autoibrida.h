#ifndef AUTOIBRIDA_H
#define AUTOIBRIDA_H

#include "veicolotermico.h"
#include "veicoloelettrico.h"

class AutoIbrida : public VeicoloTermico, public VeicoloElettrico
{
    public:
        // Costruttori
        AutoIbrida(const string &mar, const string &model, const Rifornimento::tipo_r &tr, const float &ser, const float &bat, const u_short &cav_t=0, const u_short &cav_e=0, const u_int &peso_vuoto=0, const u_int &posti=0, const u_int &km_i=0, const u_int &tag=0, const u_int &p_max=0, const float &lun=0, const float &lar=0, const float &alt=0);
        AutoIbrida(const AutoIbrida&) = default;
        //AutoIbrida &operator=(const AutoIbrida&) = default; // c'è già senza dichiararlo

        // Metodi costanti
        virtual u_int getKmAutonomia() const override;
        virtual u_short getCavalli() const override;
        virtual u_short getKw() const override;
        virtual bool fareTagliando() const override;
        virtual u_int getSommaKmRifornimenti() const override;
        virtual AutoIbrida * clone() const override;

    protected:
        virtual bool checkCorrettezzaRifornimento(const Rifornimento& ) const override;
};

#endif // AUTOIBRIDA_H
