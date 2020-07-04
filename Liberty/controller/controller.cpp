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

void Controller::aggiungiVeicolo(const QString tipoV, const QString marca, const QString modello, const float km_iniziali, const Rifornimento::tipo_r tipo_rifornimento, const float peso, const u_short posti, const u_int cv_t, const u_int cv_e, const float serbatoio, const float batteria)
{
    Veicolo * v = nullptr;
    u_int pos = model->count();

    try {
        if(tipoV=="Auto Termica"){
            v = new AutoTermica(marca.toStdString(),modello.toStdString(),tipo_rifornimento,serbatoio,cv_t,peso,posti, km_iniziali);
        }else if(tipoV=="Auto Elettrica"){
            v = new AutoElettrica(marca.toStdString(),modello.toStdString(),batteria,cv_e,peso,posti, km_iniziali);
        }else if(tipoV=="Auto Ibrida"){
            v = new AutoIbrida(marca.toStdString(),modello.toStdString(),tipo_rifornimento,serbatoio,batteria,cv_t,cv_e,peso,posti, km_iniziali);
        }
        model->add(v);
        view->veicoloAggiunto(v,pos);
    } catch (std::exception & e) {
        delete v;
        view->mostraErrore(e.what());
    }
}

void Controller::salvaModificheVeicolo(const u_int pos, const std::string marca, const std::string modello, const u_int peso, const u_short posti, const u_int ultimo_tagliando, const u_short cv_t, const u_short cv_e, const float capacita_serbatoio, const float capacita_batteria, const u_int km_i)
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
        view->updateDetagli();
    } catch (std::exception & e) {
        *veicolo=*backup; // torno ripristinare lo stato del veicolo a prima delle modifiche nel caso si sia verificato qualche errore
        view->mostraErrore(e.what());
    }
    delete backup;
}

void Controller::eliminaRifornimento(const u_int v, const list<Rifornimento *>::const_iterator it)
{
    model->eliminaRifornimento(v,it);
    view->updateDetagli(); // aggiorno la tab dettagli perché saranno cambiati dati come i consumi medi e/o i km attuali
}

void Controller::aggiungiRifornimento(const u_int pos, const Rifornimento::tipo_r tipo, const float q, const float k, const float t, const string u)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    Rifornimento * rif = new Rifornimento(tipo, k, q, t, u);
    try {
        model->rifornisci(veicolo,rif);
        view->updateDetagli(); // aggiorno la tab dettagli perché saranno cambiati dati come i consumi medi e/o i km attuali
    } catch (std::exception & e) {
        delete rif; // Se il rifornimento da errore elimino l'oggetto perché non più necessario
        view->mostraErrore(e.what());
    }
}

void Controller::modificaRifornimento(const u_int pos, const list<Rifornimento *>::const_iterator it, const Rifornimento::tipo_r tipo, const float q, const float k, const float t, const string u)
{
    Veicolo * veicolo = model->getVeicoloAt(pos).operator*();
    Rifornimento * rif = new Rifornimento(tipo, k, q, t, u);
    try {
        model->modificaRifornimento(veicolo,it,rif);
        view->updateDetagli(); // aggiorno la tab dettagli perché saranno cambiati dati come i consumi medi e/o i km attuali
    } catch (std::exception & e) {
        delete rif; // Se il rifornimento da errore elimino l'oggetto perché non più necessario
        view->mostraErrore(e.what());
    }
}
