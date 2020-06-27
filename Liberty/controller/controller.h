#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "../model/model.h"
#include "../view/liberty.h"

class Controller: public QObject
{
        Q_OBJECT
    public:
        Controller(Model* m, QObject* parent = nullptr);

        void setView(Liberty* );
        const Veicolo * getVeicoloAt(const int& i) const; //TO DO: boh
        int getNumVeicoli() const;
        QString getNomeVeicolo(const int& i) const;

    private:
        Liberty* view;
        Model* model;

};

#endif // CONTROLLER_H
