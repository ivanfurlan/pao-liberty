#include "view/liberty.h"

#include <QApplication>

#include "model/model.h"
#include "controller/controller.h"

#include "model/autoelettrica.h"
#include "model/autotermica.h"
#include "model/autoibrida.h"

#include <iostream>

void popola(Model *);

int main(int argc, char *argv[])
{
    Model model;
    popola(&model);
    Controller controller(&model);

    QApplication a(argc, argv);
    Liberty view(&controller);

    controller.setView(&view);

    view.show();
    return a.exec();
}

void popola(Model * m){
    AutoTermica * at = new AutoTermica("Ford","ST 2018",Rifornimento::BENZINA,42,200,1300,5,100000,84000);
    AutoTermica * at3 = new AutoTermica("Volvo","XC 40",Rifornimento::DIESEL,60,160,2200,5,184357);
    AutoIbrida * ai = new AutoIbrida("Toyota","Prius Plug-In",Rifornimento::BENZINA,35,17,130,75,1800,5,78345,77315);
    AutoElettrica * ae = new AutoElettrica("Tesla","Model 3",95,245,2000,4,45000,20000);

    Rifornimento * r = new Rifornimento(Rifornimento::BENZINA,400,23.4,32);
    Rifornimento * s = new Rifornimento(*r); // costruttore di copia
    Rifornimento * t = new Rifornimento(*r);; // costruttore di copia
    *t=*r; // assegnamento
    AutoTermica * at2 = new AutoTermica(*at); // costruttore di copia
    AutoIbrida * ai2 = new AutoIbrida(*ai); // costruttore di copia
    *ai2=*ai; // assegnamento
    ai2->setName("Renault","Captur");
    at2->setName("Ford","ST 2019");

    ai->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,700,10,3));
    ai->addRifornimento(new Rifornimento(Rifornimento::BENZINA,700,30,40));
    at->addRifornimento(new Rifornimento(Rifornimento::BENZINA,400,37.5,55.6));
    at->addRifornimento(new Rifornimento(Rifornimento::BENZINA,453,39.01,63.45));
    ae->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,431.59,91.32,21));
    ae->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,375,90,20));
    ae->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,230,50,13));
    ae->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,400,84,17));
    at3->addRifornimento(new Rifornimento(Rifornimento::DIESEL,700,30,40));
    at3->addRifornimento(new Rifornimento(Rifornimento::DIESEL,700,30,40));
    ai2->addRifornimento(r);
    ai2->addRifornimento(s);
    ai2->addRifornimento(t);

    m->add(at);
    m->add(at2);
    m->add(at3);
    m->add(ae);
    m->add(ai);
    m->add(ai2);
}
