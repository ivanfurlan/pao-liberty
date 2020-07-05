#include "model.h"

Model::~Model()
{
    for(auto it=veicoli.begin(); it<veicoli.end(); ++it){
        delete *it;
    }
}

Container<Veicolo* >::const_iterator Model::getVeicoloAt(const u_int & i) const
{
    return Container<Veicolo* >::const_iterator(veicoli,i);
}

u_int Model::count() const
{
    return veicoli.countElements();
}

void Model::add(Veicolo * v)
{
    veicoli.insertBack(v);
}

void Model::rifornisci(Veicolo * v, Rifornimento * r)
{
    v->addRifornimento(r);
}

void Model::deleteV(const Container<Veicolo*>::const_iterator & it)
{
    Veicolo * temp = it.operator*();
    veicoli.remove(*it);
    delete temp;
}

void Model::deleteAll()
{
    while(veicoli.countElements()>0){
        auto it = veicoli.begin();
        deleteV(it);
    }
}

void Model::eliminaRifornimento(const u_int &v, list<Rifornimento *>::const_iterator it)
{
    veicoli[v]->eliminaRifornimento(it);
}

void Model::modificaRifornimento(Veicolo *v, list<Rifornimento *>::const_iterator it, Rifornimento * r)
{
    v->modificaRifornimento(it,r);
}
