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
    AutoTermica * at = new AutoTermica("Ford","ST 2019",Rifornimento::BENZINA,42,200,1300,2700,5);
    AutoIbrida * ai = new AutoIbrida("Toyota","Prius Plug-In",Rifornimento::BENZINA,35,17,130,75,1800,2700,5);

    ai->addRifornimento(new Rifornimento(Rifornimento::ELETTRICITA,700,10,0.235));
    ai->addRifornimento(new Rifornimento(Rifornimento::BENZINA,700,30,1.389));

    at->addRifornimento(new Rifornimento(Rifornimento::BENZINA,400,37.5,1.359));
    at->addRifornimento(new Rifornimento(Rifornimento::BENZINA,900,39.01,1.425));

    m->add(at);
    m->add(new AutoTermica("Volvo","XC 40",Rifornimento::DIESEL,60,160,2200,2800,5));
    m->add(new AutoElettrica("Tesla","Model 3",75,245,2000,3000,4));
    m->add(ai);
}
