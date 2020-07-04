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

void Controller::aggiungiVeicolo(QString tipoV, QString marca, QString modello, float km_iniziali, Rifornimento::tipo_r tipo_rifornimento, float peso, u_short posti, u_int cv_t, u_int cv_e, float serbatoio, float batteria)
{
    Veicolo * v = nullptr;

    try {
        if(tipoV=="Auto Termica"){
            v = new AutoTermica(marca.toStdString(),modello.toStdString(),tipo_rifornimento,serbatoio,cv_t,peso,posti, km_iniziali);
        }else if(tipoV=="Auto Elettrica"){
            v = new AutoElettrica(marca.toStdString(),modello.toStdString(),batteria,cv_e,peso,posti, km_iniziali);
        }else if(tipoV=="Auto Ibrida"){
            v = new AutoIbrida(marca.toStdString(),modello.toStdString(),tipo_rifornimento,serbatoio,batteria,cv_t,cv_e,peso,posti, km_iniziali);
        }
        model->add(v);
        view->updateLista();
    } catch (std::exception & e) {
        delete v;
        view->mostraErrore(e.what());
    }
}

void Controller::salvaModificheVeicolo(u_int pos, std::string marca, std::string modello, u_int peso, u_short posti, u_int ultimo_tagliando, u_short cv_t, u_short cv_e, float capacita_serbatoio, float capacita_batteria, u_int km_i)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    Veicolo * backup = veicolo->clone();

    try{
        veicolo->setPosti(posti);
        veicolo->setName(marca,modello);
        veicolo->setPeso(peso);
        veicolo->doTagliando(ultimo_tagliando);
        veicolo->setKmIniziali(km_i);
        if(auto vt = dynamic_cast<VeicoloTermico *>(veicolo)){
            vt->setSerbatoio(capacita_serbatoio);
            vt->setCvTermici(cv_t);
        }
        if(auto ve = dynamic_cast<VeicoloElettrico *>(veicolo)){
            ve->setBatteria(capacita_batteria);
            ve->setCvElettrici(cv_e);
        }

    } catch (std::exception & e) {
        *veicolo=*backup; // torno ripristinare lo stato del veicolo a prima delle modifiche nel caso si sia verificato qualche errore
        view->mostraErrore(e.what());
    }
    delete backup;
}

void Controller::eliminaRifornimento(u_int v, list<Rifornimento *>::const_iterator it)
{
    model->eliminaRifornimento(v,it);
}

void Controller::aggiungiRifornimento(u_int pos, Rifornimento::tipo_r tipo, float q, float k, float t, string u)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    Rifornimento * rif = new Rifornimento(tipo, k, q, t, u);
    try {
        model->rifornisci(veicolo,rif);
    } catch (std::exception & e) {
        delete rif; // Se il rifornimento da errore elimino l'oggetto perché non più necessario
        view->mostraErrore(e.what());
    }
}

void Controller::modificaRifornimento(u_int pos, list<Rifornimento *>::const_iterator it, Rifornimento::tipo_r tipo, float q, float k, float t, string u)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    Rifornimento * rif = new Rifornimento(tipo, k, q, t, u);
    try {
        model->modificaRifornimento(veicolo,it,rif);
    } catch (std::exception & e) {
        delete rif; // Se il rifornimento da errore elimino l'oggetto perché non più necessario
        view->mostraErrore(e.what());
    }
}
