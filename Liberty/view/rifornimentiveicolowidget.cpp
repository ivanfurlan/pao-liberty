#include "rifornimentiveicolowidget.h"

Q_DECLARE_METATYPE(list<Rifornimento *>::const_iterator)

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
    const Veicolo * v =dynamic_cast<VeicoloListWidgetItem *>(item)->getVeicolo();
    const list<Rifornimento *> lista = v->getRifornimenti();
    for (list<Rifornimento *>::const_iterator rif=lista.begin();rif!=lista.end();rif.operator++()) {
        const VeicoloElettrico * ve = dynamic_cast<const VeicoloElettrico *>(v);
        const VeicoloTermico * vt = dynamic_cast<const VeicoloTermico *>(v);
        if(ve != nullptr && (*rif)->getTipoRifornimento()==Rifornimento::ELETTRICITA){
            unita = QString::fromStdString(ve->VeicoloElettrico::getUnitaRifornimento());
        }else if(vt != nullptr){
            unita = QString::fromStdString(vt->VeicoloTermico::getUnitaRifornimento());
        }

        u_int r = tableRifornimenti->rowCount();
        tableRifornimenti->insertRow(r);

        u_int t = std::distance(lista.begin(),rif);
        QTableWidgetItem * tipo = new QTableWidgetItem(QString::fromStdString(Rifornimento::tipo_string[(*rif)->getTipoRifornimento()]));
        tipo->setData(Qt::UserRole,QVariant::fromValue(t)); // per ogni cella salvo i dati del rifornimento, perché per modificare/eliminare l'utente può selezionare qualsiasi cella dellariga
        QTableWidgetItem * quantita = new QTableWidgetItem(QString::number((*rif)->getQuantita())+" "+unita);
        quantita->setData(Qt::UserRole,QVariant::fromValue(t));
        QTableWidgetItem * km = new QTableWidgetItem(QString::number((*rif)->getKmParziale())+" km");
        km->setData(Qt::UserRole,QVariant::fromValue(t));
        QTableWidgetItem * costo = new QTableWidgetItem(QString::number((*rif)->getCostoPerUnita())+" €/"+unita);
        costo->setData(Qt::UserRole,QVariant::fromValue(t));
        QTableWidgetItem * totale = new QTableWidgetItem(QString::number((*rif)->getCostoRifornimento())+" €");
        totale->setData(Qt::UserRole,QVariant::fromValue(t));
        QTableWidgetItem * consumo = new QTableWidgetItem(QString::number((*rif)->getConsumo())+" km/"+unita);
        consumo->setData(Qt::UserRole,QVariant::fromValue(t));
        tableRifornimenti->setItem(r, 0, tipo);
        tableRifornimenti->setItem(r, 1, quantita);
        tableRifornimenti->setItem(r, 2, km);
        tableRifornimenti->setItem(r, 3, costo);
        tableRifornimenti->setItem(r, 4, totale);
        tableRifornimenti->setItem(r, 5, consumo);
    }
}


void RifornimentiVeicoloWidget::askEliminaRifornimento()
{
    QList<QTableWidgetItem *> items = tableRifornimenti->selectedItems();
    if (items.empty()) return;
    if (QMessageBox::question(this, "Elimina", "Eliminare TUTTI i rifornimenti selezionati?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        auto vlwi=dynamic_cast<VeicoloListWidgetItem *>(current_item);
        if(vlwi != nullptr){
            int precedente =-1;
            u_int count=0; // uso un contatore perché se elimino un rifornimento poi cambia la posizione dei successivi
            for (QTableWidgetItem * i : items) {
                if(i->row()!=precedente){
                    auto it = vlwi->getVeicolo()->getRifornimenti().begin();
                    std::advance(it,i->data(Qt::UserRole).value<u_int>()-count);
                    emit eliminareRifornimento(vlwi->getPosizione(),it);
                    precedente=i->row();
                    ++count;
                }
            }}
    }
    updateDati(current_item);
}

void RifornimentiVeicoloWidget::windowRifornimento(const bool modifica)
{
    //preparo la finestra per modificare o aggiungere un rifornimento
    QList<string> tipi;
    auto v=dynamic_cast<VeicoloListWidgetItem *>(current_item)->getVeicolo();
    auto vt=dynamic_cast<const VeicoloTermico *>(v);
    if(vt){
        tipi.push_back(vt->getTipoRifornimento()); // nel caso di un veicolo che possa essere considerato temico aggingo il rispettivo carburante ai tipi consentiti
    }
    auto ve=dynamic_cast<const VeicoloElettrico *>(v);
    if(ve){
        tipi.push_back(Rifornimento::tipo_string[Rifornimento::ELETTRICITA]); // nel caso di un veicolo che possa essere considerato elettrico aggingo l'elettricità ai tipi consentiti
    }

    SetRifornimentoWidget * set = new SetRifornimentoWidget(tipi); // creo la finestra per lamodifica/agginta, passandogli i tipi consentiti
    if(modifica && tableRifornimenti->selectedRanges().count()==1){
        // Sto facendo una modiffica di un unico elemento
        auto row = tableRifornimenti->currentItem(); // chiamo row, anche se in realtà è una singola cella, ma i dati sono presenti su qualsiasi cella della riga
        auto it = v->getRifornimenti().begin();
        std::advance(it,row->data(Qt::UserRole).value<u_int>());
        Rifornimento * rif = *it;
        set->setValues(rif->getTipoRifornimento(),rif->getQuantita(),rif->getKmParziale(),rif->getCostoRifornimento());
        connect(set,SIGNAL(salvare(Rifornimento::tipo_r,float,float,float)),this,SLOT(prepareSignalModifica(Rifornimento::tipo_r,float,float,float)));
    }else if(!modifica){
        // Voglio aggiungere un nuovo rifornimento
        connect(set,SIGNAL(salvare(Rifornimento::tipo_r,float,float,float)),this,SLOT(prepareSignalAggiungere(Rifornimento::tipo_r, float, float, float)));
    }else{
        // ho cliccato modifica, ma ho più righe selezionate, quindi elimino la finestra e non faccio niente
        delete set;
    }


}

void RifornimentiVeicoloWidget::prepareSignalAggiungere(const Rifornimento::tipo_r tipo, const float q, const float k, const float t)
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

void RifornimentiVeicoloWidget::prepareSignalModifica(const Rifornimento::tipo_r tipo, const float q, const float k, const float t)
{
    auto vlwi=dynamic_cast<VeicoloListWidgetItem *>(current_item);
    if(vlwi != nullptr){
        QTableWidgetItem * item = tableRifornimenti->currentItem();
        auto it = vlwi->getVeicolo()->getRifornimenti().begin();
        std::advance(it,item->data(Qt::UserRole).value<u_int>());
        emit modificareRifornimento(vlwi->getPosizione(),it,tipo,q,k,t);
        updateDati(current_item);
    }

}
