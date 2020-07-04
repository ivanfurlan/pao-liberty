#include "view/liberty.h"

#include <QApplication>

#include "model/model.h"
#include "controller/controller.h"

#include "model/autoelettrica.h"
#include "model/autotermica.h"
#include "model/autoibrida.h"

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
    AutoTermica * at = new AutoTermica("Ford","ST 2019",Rifornimento::BENZINA,42,200,1300,5,100000);
    AutoIbrida * ai = new AutoIbrida("Toyota","Prius Plug-In",Rifornimento::BENZINA,35,17,130,75,1800,5,78345);

    ai->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,700,10,3));
    ai->addRifornimento(new Rifornimento(Rifornimento::BENZINA,700,30,40));

    at->addRifornimento(new Rifornimento(Rifornimento::BENZINA,400,37.5,55.6));
    at->addRifornimento(new Rifornimento(Rifornimento::BENZINA,453,39.01,63.45));

    Rifornimento * r= new Rifornimento(Rifornimento::BENZINA,4,4,4);
    Rifornimento * s= new Rifornimento(*r);
    Rifornimento * t= new Rifornimento(*r);;
    *t=*r;
    AutoTermica * att = new AutoTermica(*at);
    AutoTermica * at2 = new AutoTermica(*at);
    *at2=*att;
    at2->addRifornimento(r);
    at2->addRifornimento(s);
    at2->addRifornimento(t);

    m->add(at2);
    m->add(att);
    m->add(at);
    m->add(new AutoTermica("Volvo","XC 40",Rifornimento::DIESEL,60,160,2200,5,184357));
    m->add(new AutoElettrica("Tesla","Model 3",75,245,2000,4,45000));
    m->add(ai);
}
