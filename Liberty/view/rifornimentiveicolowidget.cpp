#include "rifornimentiveicolowidget.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>

#include <list>
#include "../model/rifornimento.h"
#include "../model/veicolo.h"
#include "proprietalabel.h"
#include "setrifornimentowidget.h"
#include "../model/autoibrida.h"

using std::list;
Q_DECLARE_METATYPE(Rifornimento *)

RifornimentiVeicoloWidget::RifornimentiVeicoloWidget(QWidget *parent) : QWidget(parent), tableRifornimenti(new QTableWidget(this)), aggiungi(new QPushButton("Aggiungi",this)), modifica(new QPushButton("Modifica",this)), elimina(new QPushButton("Elimina",this))
{
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Expanding);

    QVBoxLayout * mainLayout = new QVBoxLayout();
    QHBoxLayout * pulsantiLayout = new QHBoxLayout();
    pulsantiLayout->addWidget(aggiungi);
    pulsantiLayout->addWidget(modifica);
    pulsantiLayout->addWidget(elimina);
    mainLayout->addLayout(pulsantiLayout);
    setLayout(mainLayout);

    QStringList tableHeader;
    tableRifornimenti->setColumnCount(6);
    tableHeader<<"Tipo"<<"Quantità"<<"Km percorsi"<<"Costo"<<"Totale"<<"Consumo";
    tableRifornimenti->setHorizontalHeaderLabels(tableHeader);
    tableRifornimenti->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableRifornimenti->verticalHeader()->setVisible(false);
    tableRifornimenti->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableRifornimenti->setSelectionBehavior(QAbstractItemView::SelectRows);

    mainLayout->addWidget(tableRifornimenti);

    connect(elimina,SIGNAL(clicked()),this,SLOT(askEliminaRifornimento()));
    connect(aggiungi,SIGNAL(clicked()),this,SLOT(windowRifornimento()));
    connect(modifica,SIGNAL(clicked()),this,SLOT(convertSignalModifica()));
    connect(tableRifornimenti,SIGNAL(cellDoubleClicked(int, int)),this,SLOT(convertSignalModifica()));

}

void RifornimentiVeicoloWidget::updateDati(QListWidgetItem * item)
{
    if(item)
        current_item=item;
    else
        item=current_item;
    tableRifornimenti->setRowCount(0);
    QString unita = "l";

    u_int pos = QTableWidgetItem::UserType; // parto da QTableWidgetItem::UserType, cioè 1000, perché, come da documentazione, valori sotto QTableWidgetItem::UserType sono riservati da Qt

    const list<Rifornimento *> lista = dynamic_cast<VeicoloListWidgetItem *>(item)->getVeicolo()->getRifornimenti();
    for (Rifornimento * rif : lista) {
        if(rif->getTipoRifornimento()==Rifornimento::ELETTRICITA){
            unita="Kw";
        }else{
            unita="l";
        }

        u_int r = tableRifornimenti->rowCount();
        tableRifornimenti->insertRow(r);

        QTableWidgetItem * tipo = new QTableWidgetItem(QString::fromStdString(Rifornimento::tipo_string[rif->getTipoRifornimento()]),pos);
        tipo->setData(Qt::UserRole,QVariant::fromValue(rif));
        QTableWidgetItem * quantita = new QTableWidgetItem(QString::number(rif->getQuantita())+" "+unita,pos);
        quantita->setData(Qt::UserRole,QVariant::fromValue(rif));
        QTableWidgetItem * km = new QTableWidgetItem(QString::number(rif->getKm())+" km",pos);
        km->setData(Qt::UserRole,QVariant::fromValue(rif));
        QTableWidgetItem * costo = new QTableWidgetItem(QString::number(rif->getCostoPerUnita())+" €/"+unita,pos);
        costo->setData(Qt::UserRole,QVariant::fromValue(rif));
        QTableWidgetItem * totale = new QTableWidgetItem(QString::number(rif->getCostoRifornimento())+" €",pos);
        totale->setData(Qt::UserRole,QVariant::fromValue(rif));
        QTableWidgetItem * consumo = new QTableWidgetItem(QString::number(0)+" km/"+unita,pos);
        consumo->setData(Qt::UserRole,QVariant::fromValue(rif));
        tableRifornimenti->setItem(r, 0, tipo);
        tableRifornimenti->setItem(r, 1, quantita);
        tableRifornimenti->setItem(r, 2, km);
        tableRifornimenti->setItem(r, 3, costo);
        tableRifornimenti->setItem(r, 4, totale);
        tableRifornimenti->setItem(r, 5, consumo);
        pos++;
    }
}


void RifornimentiVeicoloWidget::askEliminaRifornimento()
{
    QList<QTableWidgetItem *> item = tableRifornimenti->selectedItems();
    if (item.empty()) return;
    if (QMessageBox::question(this, "Elimina", "Eliminare TUTTI i rifornimenti selezionati?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        // TO DO: sarebbe da fare gl iiteratori con il puntatore non con la posizione

        auto vlwi=dynamic_cast<VeicoloListWidgetItem *>(current_item);
        if(vlwi != nullptr){
            u_int count = QTableWidgetItem::UserType;
            int precedente =-1;
            for (QTableWidgetItem * i : item) {
                if(i->row()!=precedente){
                    emit eliminareRifornimento(vlwi->getPosizione(),i->type()-count);
                    precedente=i->row();
                    count++;
                }
            }}
    }
    updateDati(current_item);
}

void RifornimentiVeicoloWidget::windowRifornimento(bool modifica)
{
    QList<string> tipi;
    auto v=dynamic_cast<VeicoloListWidgetItem *>(current_item)->getVeicolo();
    auto vt=dynamic_cast<const VeicoloTermico *>(v);
    if(vt){
        tipi.push_back(vt->getTipoRifornimento());
    }
    auto ve=dynamic_cast<const VeicoloElettrico *>(v);
    if(ve){
        tipi.push_back(Rifornimento::tipo_string[Rifornimento::ELETTRICITA]);
    }

    SetRifornimentoWidget * set = new SetRifornimentoWidget(tipi);
    if(modifica && tableRifornimenti->selectedRanges().count()==1){
        auto row = tableRifornimenti->currentItem();
        // TO DO: passare anche il tipo rifornimento attuale
        set->setValues(row->data(Qt::UserRole).value<Rifornimento*>()->getQuantita(),row->data(Qt::UserRole).value<Rifornimento*>()->getKm(),row->data(Qt::UserRole).value<Rifornimento*>()->getCostoRifornimento());
        connect(set,SIGNAL(salvare(Rifornimento::tipo_r,float,float,float)),this,SLOT(prepareSignalModifica(Rifornimento::tipo_r,float,float,float)));
    }else if(!modifica){
        connect(set,SIGNAL(salvare(Rifornimento::tipo_r,float,float,float)),this,SLOT(prepareSignalAggiungere(Rifornimento::tipo_r,float,float,float)));
    }else{
        delete set;
    }


}

void RifornimentiVeicoloWidget::prepareSignalAggiungere(Rifornimento::tipo_r tipo, float q, float k, float t)
{
    auto vlwi=dynamic_cast<VeicoloListWidgetItem *>(current_item);
    if(vlwi != nullptr){
        emit aggiungereRifornimento(vlwi->getPosizione(),tipo,q,k,t);
        updateDati(current_item);
    }
}

void RifornimentiVeicoloWidget::convertSignalModifica()
{
    QTableWidgetItem * item = tableRifornimenti->currentItem();
    if (!item) return;
    windowRifornimento(true);
}

void RifornimentiVeicoloWidget::prepareSignalModifica(Rifornimento::tipo_r tipo, float q, float k, float t)
{
    auto vlwi=dynamic_cast<VeicoloListWidgetItem *>(current_item);
    if(vlwi != nullptr){
        QTableWidgetItem * item = tableRifornimenti->currentItem();
        emit modificareRifornimento(vlwi->getPosizione(),item->type()-QTableWidgetItem::UserType,tipo,q,k,t);
        updateDati(current_item);
    }

}

// add riga
// chexkbox per eliminare/modificare
// nuova finestra per aggiungere
