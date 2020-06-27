#include "model.h"
Model::Model()
{

}

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

void Model::delelte(Container<Veicolo*>::iterator & it)
{
    veicoli.remove(it);
}

void Model::deleteAll()
{
    while(veicoli.end()==veicoli.begin()){
        veicoli.removeBack();
    }
}
