#include "dettagliveicoliwidget.h"
#include "veicololistwidgetitem.h"

#include "../model/autoibrida.h"

DettagliVeicoliWidget::DettagliVeicoliWidget(QWidget *parent) \
    : QWidget(), parent(parent), modifica(new QPushButton("Modifica", this)), elimina(new QPushButton("Elimina", this)), annulla(new QPushButton("Annulla", this)), salva(new QPushButton("Salva", this)), marca(new ProprietaLabel("Marca",true,this)), modello(new ProprietaLabel("Modello",true,this)), peso_vuoto(new ProprietaLabel("Peso",true,this)), posti(new ProprietaLabel("Posti",true,this)), \
      km_totali(new ProprietaLabel("Km totali",this)), ultimo_tagliando(new ProprietaLabel("Ultimo tagliando a km",true,this)), tagliando_da_fare(new ProprietaLabel("Tagliano da fare",this)), cavalli(new ProprietaLabel("Cavalli",this)), cavalli_termici(new ProprietaLabel("Di cui termici",true,this)), cavalli_elettrici(new ProprietaLabel("Di cui elettrici",true,this)), kw(new ProprietaLabel("KW",this)),\
      autonomia_massima(new ProprietaLabel("Autonomia massima",this)), carburante(new ProprietaLabel("Tipo carburante",this)), consumo_medio(new ProprietaLabel("Consumo medio",this)), consumo_elettrico_medio(new ProprietaLabel("Consumo elettrico medio",this)), capacita_serbatoio(new ProprietaLabel("Capacità serbatoio",true,this)), capacita_batteria(new ProprietaLabel("Capacità batteria",true,this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout * dettagliLayout = new QGridLayout(this);

    u_short riga=0;
    QFrame* line = new QFrame();
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    QFrame* line2 = new QFrame();
    line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    dettagliLayout->addItem(marca,riga,0);
    dettagliLayout->addItem(modello,riga,1);
    dettagliLayout->addItem(peso_vuoto,++riga,0);
    dettagliLayout->addItem(posti,riga,1);
    dettagliLayout->addItem(km_totali,++riga,0);
    dettagliLayout->addItem(ultimo_tagliando,++riga,0);
    dettagliLayout->addItem(tagliando_da_fare,riga,1);
    dettagliLayout->addItem(cavalli,++riga,0);
    dettagliLayout->addItem(kw,riga,1);
    dettagliLayout->addItem(cavalli_termici,++riga,0);
    dettagliLayout->addItem(cavalli_elettrici,++riga,0);
    dettagliLayout->addWidget(line,++riga,0,1,2);
    dettagliLayout->addItem(autonomia_massima,++riga,0);
    dettagliLayout->addItem(carburante,riga,1);
    dettagliLayout->addItem(consumo_medio,++riga,0);
    dettagliLayout->addItem(consumo_elettrico_medio,++riga,0);
    dettagliLayout->addItem(capacita_serbatoio,++riga,0);
    dettagliLayout->addItem(capacita_batteria,++riga,0);
    dettagliLayout->addWidget(line2,++riga,0,1,2);

    connect(modifica, SIGNAL(clicked()), this, SLOT(permettiModifica()));
    connect(elimina, SIGNAL(clicked()), parent, SLOT(askEliminaVeicolo()));

    connect(annulla, SIGNAL(clicked()), this, SLOT(annullaModifica()));
    connect(salva, SIGNAL(clicked()), this, SLOT(prepareSignalSalvataggio()));

    dettagliLayout->addWidget(modifica,++riga,0);
    annulla->hide();
    dettagliLayout->addWidget(annulla,riga,0);
    dettagliLayout->addWidget(elimina,riga,1);
    salva->hide();
    dettagliLayout->addWidget(salva,riga,1);

    setLayout(dettagliLayout);
}

void DettagliVeicoliWidget::updateDati(QListWidgetItem * item)
{
    if(item)
        current_item=item;
    else
        item=current_item;
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
        cavalli_termici->setProprietaNumber(vt->VeicoloTermico::getCavalli(),"cv");

        carburante->show();
        consumo_medio->show();
        capacita_serbatoio->show();
        cavalli_termici->show();
    }else{
        carburante->hide();
        consumo_medio->hide();
        capacita_serbatoio->hide();
        cavalli_termici->hide();
    }

    const VeicoloElettrico * ve = dynamic_cast<const VeicoloElettrico *>(v);
    if(ve != nullptr){
        consumo_elettrico_medio->setProprietaNumber(ve->getConsumoElettricoMedio(),"km/KW");
        capacita_batteria->setProprietaNumber(ve->getBatteria(),"KW");
        cavalli_elettrici->setProprietaNumber(ve->VeicoloElettrico::getCavalli(),"cv");

        consumo_elettrico_medio->show();
        capacita_batteria->show();
        cavalli_elettrici->show();
    }else{
        consumo_elettrico_medio->hide();
        capacita_batteria->hide();
        cavalli_elettrici->hide();
    }

    modifica->show();
    elimina->show();
    salva->hide();
    annulla->hide();

    //show();
}

void DettagliVeicoliWidget::permettiModifica()
{
    elimina->hide();
    modifica->hide();

    annulla->show();
    salva->show();

    //if(capacita_serbatoio->visible())


    emit startModifica(); // Rendo modificabili le lable
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

void DettagliVeicoliWidget::annullaModifica()
{
    elimina->show();
    modifica->show();

    annulla->hide();
    salva->hide();

    updateDati(current_item);
}

void DettagliVeicoliWidget::prepareSignalSalvataggio()
{
    string marca = (this->marca->getTextModifica()).toStdString();
    string modello = (this->modello->getTextModifica()).toStdString();
    u_int peso_vuoto = (this->peso_vuoto->getTextModifica()).toUInt();
    u_short posti = (this->posti->getTextModifica()).toUShort();
    //u_short posti = QString("4").toUShort();
    u_int ultimo_tagliando = (this->ultimo_tagliando->getTextModifica()).toUInt();
    u_short cavalli_termici = (this->cavalli_termici->getTextModifica()).toUShort();
    u_short cavalli_elettrici = (this->cavalli_elettrici->getTextModifica()).toUShort();
    //asdas carburante = (this->carburante->getTextModifica()).toStdString();
    float capacita_serbatoio = (this->capacita_serbatoio->getTextModifica()).toFloat();
    float capacita_batteria = (this->capacita_batteria->getTextModifica()).toFloat();

    emit richiestaSalvataggio(dynamic_cast<VeicoloListWidgetItem *>(current_item)->getPosizione(), marca, modello, peso_vuoto, posti, ultimo_tagliando, cavalli_termici, cavalli_elettrici, capacita_serbatoio, capacita_batteria);

    updateDati(current_item); //si può fare l'aggiornamento qua, perché quando viene emessa la emit il programma aspetta di aver sovolto tutti gli slot che la catturano prima di procedere, quindi l'aggiornamento dei dati verrà sempre fatto dopo che essi effettivamente siano stati modificati/salvati
}

