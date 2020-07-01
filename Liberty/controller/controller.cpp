#include "controller/controller.h"

Controller::Controller(Model *m, QObject *parent) : QObject(parent), view(nullptr), model(m)
{

}

void Controller::setView(Liberty *v)
{
    view = v;
}

const Veicolo* Controller::getVeicoloAt(const int& i) const
{
    return *(model->getVeicoloAt(i));
}

int Controller::getNumVeicoli() const
{
    return model->count();
}

QString Controller::getNomeVeicolo(const int &i) const
{
    return QString::fromStdString(model->getVeicoloAt(i).operator*()->getNomeEsteso());
}

void Controller::eliminaVeicolo(const int &i)
{
    model->deleteV(model->getVeicoloAt(i));
}

void Controller::salvaModificheVeicolo(u_int pos, std::string marca, std::string modello, u_int peso, u_short posti, u_int ultimo_tagliando, u_short cv_t, u_short cv_e, float capacita_serbatoio, float capacita_batteria)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();

    veicolo->setPosti(posti);
    veicolo->setName(marca,modello);
    veicolo->setPeso(peso);
    veicolo->doTagliando(ultimo_tagliando);

    if(auto vt = dynamic_cast<VeicoloTermico *>(veicolo)){
        vt->setSerbatoio(capacita_serbatoio);
        vt->setCvTermici(cv_t);
    }
    if(auto ve = dynamic_cast<VeicoloElettrico *>(veicolo)){
        ve->setBatteria(capacita_batteria);
        ve->setCvElettrici(cv_e);
    }
}

void Controller::eliminaRifornimento(u_int v, u_int r)
{
    model->eliminaRifornimento(v,r);
}

void Controller::aggiungiRifornimento(u_int pos, Rifornimento::tipo_r tipo, float q, float k, float t)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    model->rifornisci(veicolo,new Rifornimento(tipo, k, q, t/q)); // TO DO: eliminare zona allocata in caso di errore
}

void Controller::modificaRifornimento(u_int pos, u_int rif, Rifornimento::tipo_r tipo, float q, float k, float t)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    model->modificaRifornimento(veicolo,rif,new Rifornimento(tipo, k, q, t/q)); // TO DO: eliminare zona allocata in caso di errore
}
