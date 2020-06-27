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
