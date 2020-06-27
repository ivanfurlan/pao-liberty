#include "dettagliveicoliwidget.h"
#include "veicololistwidgetitem.h"
#include <iostream>

#include "../model/autoibrida.h"

DettagliVeicoliWidget::DettagliVeicoliWidget(QWidget *parent) \
    : QWidget(), parent(parent), rifornisci(new QPushButton("Aggiungi rifornimento", this)), modifica(new QPushButton("Modifica", this)), elimina(new QPushButton("Elimina", this)), annulla(new QPushButton("Annulla", this)), salva(new QPushButton("Salva", this)), marca(new ProprietaVeicoloLabel("Marca",this)), modello(new ProprietaVeicoloLabel("Modello",true,this)), peso_vuoto(new ProprietaVeicoloLabel("Peso",true,this)), posti(new ProprietaVeicoloLabel("Posti",true,this)), \
      km_totali(new ProprietaVeicoloLabel("Km totali",this)), ultimo_tagliando(new ProprietaVeicoloLabel("Ultimo tagliando a km",true,this)), tagliando_da_fare(new ProprietaVeicoloLabel("Tagliano da fare",this)), cavalli(new ProprietaVeicoloLabel("Cavalli",true,this)), kw(new ProprietaVeicoloLabel("KW",this)),\
      autonomia_massima(new ProprietaVeicoloLabel("Autonomia massima",this)), carburante(new ProprietaVeicoloLabel("Tipo carburante",this)), consumo_medio(new ProprietaVeicoloLabel("Consumo medio",this)), consumo_elettrico_medio(new ProprietaVeicoloLabel("Consumo elettrico medio",this)), capacita_serbatoio(new ProprietaVeicoloLabel("Capacità serbatoio",true,this)), capacita_batteria(new ProprietaVeicoloLabel("Capacità batteria",true,this))
{
    QGridLayout * dettagliLayout = new QGridLayout(this);
    dettagliLayout->addItem(marca,0,0);
    dettagliLayout->addItem(modello,0,1);
    dettagliLayout->addItem(peso_vuoto,1,0);
    dettagliLayout->addItem(posti,1,1);
    dettagliLayout->addItem(km_totali,2,0);
    dettagliLayout->addItem(ultimo_tagliando,3,0);
    dettagliLayout->addItem(tagliando_da_fare,3,1);
    dettagliLayout->addItem(cavalli,4,0);
    dettagliLayout->addItem(kw,4,1);
    dettagliLayout->addItem(autonomia_massima,5,0);
    dettagliLayout->addItem(carburante,6,0);
    dettagliLayout->addItem(consumo_medio,7,0);
    dettagliLayout->addItem(consumo_elettrico_medio,8,0);
    dettagliLayout->addItem(capacita_serbatoio,9,0);
    dettagliLayout->addItem(capacita_batteria,10,0);

    connect(modifica, SIGNAL(clicked()), this, SLOT(permettiModifica()));
    connect(elimina, SIGNAL(clicked()), parent, SLOT(askEliminaVeicolo()));
    connect(rifornisci, SIGNAL(clicked()), parent, SLOT(askRifornisciVeicolo()));

    dettagliLayout->addWidget(rifornisci,11,0,2,0);

    dettagliLayout->addWidget(modifica,12,0);
    annulla->hide();
    dettagliLayout->addWidget(annulla,12,0);
    dettagliLayout->addWidget(elimina,12,1);
    salva->hide();
    dettagliLayout->addWidget(salva,12,1);

    setLayout(dettagliLayout);
    hide();
}

void DettagliVeicoliWidget::updateDati(QListWidgetItem * item)
{
    VeicoloListWidgetItem * veicoloItem = dynamic_cast<VeicoloListWidgetItem*>(item);
    const Veicolo * v = veicoloItem->getVeicolo();

    marca->setProprietaText(QString::fromStdString(v->getMarca()));
    modello->setProprietaText(QString::fromStdString(v->getModello()));
    peso_vuoto->setProprietaNumber(v->getPeso(),"kg");
    posti->setProprietaNumber(v->getPosti());
    km_totali->setProprietaNumber(v->getKmTotaliVeicolo(),"km");
    ultimo_tagliando->setProprietaNumber(v->getUltimoTagliando(),"km");
    tagliando_da_fare->setProprietaText(v->fareTagliando()?"Sì":"No");
    cavalli->setProprietaNumber(v->getCavalli(),"cv");
    kw->setProprietaNumber(v->getKw(),"KW");
    autonomia_massima->setProprietaNumber(v->getKmAutonomia(),"km");

    const VeicoloTermico * vt = dynamic_cast<const VeicoloTermico *>(v);
    if(vt != nullptr){
        consumo_medio->setProprietaNumber(vt->getConsumoCarburanteMedio(),"km/l");
        capacita_serbatoio->setProprietaNumber(vt->getSerbatoio(),"l");
        carburante->setProprietaText(QString::fromStdString(vt->getTipoRifornimento()));

        carburante->show();
        consumo_medio->show();
        capacita_serbatoio->show();
    }else{
        carburante->hide();
        consumo_medio->hide();
        capacita_serbatoio->hide();
    }

    const VeicoloElettrico * ve = dynamic_cast<const VeicoloElettrico *>(v);
    if(ve != nullptr){
        consumo_elettrico_medio->setProprietaNumber(ve->getConsumoElettricoMedio(),"km/KW");
        capacita_batteria->setProprietaNumber(ve->getBatteria(),"KW");

        consumo_elettrico_medio->show();
        capacita_batteria->show();
    }else{
        consumo_elettrico_medio->hide();
        capacita_batteria->hide();
    }

    modifica->show();
    elimina->show();
    rifornisci->show();
    salva->hide();
    annulla->hide();

    show();
}

void DettagliVeicoliWidget::permettiModifica()
{
    rifornisci->hide();
    elimina->hide();
    modifica->hide();

    annulla->show();
    salva->show();
    std::cout<<"ciao\n";
    emit startModifica();
    /*
    marca->permettiModifica();
    modello->permettiModifica();
    peso_vuoto->permettiModifica();
    posti->permettiModifica();
    ultimo_tagliando->permettiModifica();
    cavalli->permettiModifica();
    carburante->permettiModifica();
    capacita_serbatoio->permettiModifica();
    carburante->permettiModifica();
    consumo_medio->permettiModifica();
    capacita_serbatoio->permettiModifica();
    capacita_batteria->permettiModifica();*/

}

