#include "autoibrida.h"

AutoIbrida::AutoIbrida()
{

}

u_int AutoIbrida::getKmAutonomia() const
{
    return 0;
}

bool AutoIbrida::fareTagliando() const
{
    return false;
}

void AutoIbrida::addRifornimento(Rifornimento *r)
{
    if(r->getTipoRifornimento()==Rifornimento::ELETTRICITA)
        VeicoloElettrico::addRifornimento(r);
    else
        VeicoloTermico::addRifornimento(r);
}

u_short AutoIbrida::getCavalli() const
{
    return VeicoloTermico::getCavalli()+VeicoloElettrico::getCavalli();
}

u_short AutoIbrida::getKw() const
{
    return (VeicoloTermico::getCavalli()+VeicoloElettrico::getCavalli())*0.745699872;
}
