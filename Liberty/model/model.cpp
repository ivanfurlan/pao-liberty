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

void Model::deleteV(const Container<Veicolo*>::const_iterator & it)
{
    Veicolo * temp = it.operator*();
    veicoli.remove(temp);
    delete temp;
}

void Model::deleteAll()
{
    while(veicoli.end()==veicoli.begin()){
        veicoli.removeBack();
    }
}

void Model::eliminaRifornimento(u_int v, u_int r)
{
    veicoli[v]->eliminaRifornimento(r);
}

void Model::modificaRifornimento(Veicolo *v, u_int pr, Rifornimento * r)
{
    v->modificaRifornimento(pr,r);
}
