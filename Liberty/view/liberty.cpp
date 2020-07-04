#include "liberty.h"

#include "../controller/controller.h"

Liberty::Liberty(Controller * c, QWidget *parent) : QWidget(parent), controller(c), mainLayout(new QVBoxLayout(this)), listaWidgetVeicoli(new QListWidget(this)), info_veicolo(new QTabWidget(this)), dettagli(new DettagliVeicoliWidget(this)), rifornimenti(new RifornimentiVeicoloWidget(this)),errMess(new QErrorMessage(this))
{
    addMenu(); //aggiungo bara del menu

    QHBoxLayout* veicoliLayout = new QHBoxLayout(); // Layout che comprende il widget a sx con la lista dei veicoli, e quello a dx con le informazioni su ogni veicolo
    veicoliLayout->setAlignment(Qt::AlignLeft);

    listaWidgetVeicoli->setSelectionMode(QListWidget::SelectionMode::ExtendedSelection); // permetto di selezionare più veicoli contemporaneamente

    veicoliLayout->addWidget(listaWidgetVeicoli); // aggiungo widget di sx

    veicoliLayout->addWidget(info_veicolo); // aggingo widget di dx
    info_veicolo->addTab(dettagli,"Veicolo");
    info_veicolo->addTab(rifornimenti,"Rifornimenti");

    mainLayout->addLayout(veicoliLayout);

    setStyle();
    setLayout(mainLayout);

    // mostro o nascondo le info se cambio il veicolo selezionato
    connect(listaWidgetVeicoli, SIGNAL(itemClicked(QListWidgetItem *)), dettagli, SLOT(updateDati(QListWidgetItem *)));
    connect(listaWidgetVeicoli, SIGNAL(itemClicked(QListWidgetItem *)), rifornimenti, SLOT(updateDati(QListWidgetItem *)));
    connect(listaWidgetVeicoli, SIGNAL(itemSelectionChanged()), this, SLOT(visibilitaInfoVeicolo())); // sennò se si deselezionano tutti resta comunque una scheda aperta

    // collego il segnale di modifica di un veicolo  con il relativo slot del controller
    connect(dettagli, SIGNAL(richiestaSalvataggio(u_int, string, string, u_int, u_short, u_int, u_short, u_short, float, float, u_int)), controller, SLOT(salvaModificheVeicolo(u_int, string, string, u_int, u_short, u_int, u_short, u_short, float, float, u_int)));

    // collego i segnali di aggiunta/modifica/elimina di un rifornimeno di un veicolo con i relativi slot del controller
    connect(rifornimenti, SIGNAL(eliminareRifornimento(u_int,list<Rifornimento *>::const_iterator)), controller, SLOT(eliminaRifornimento(u_int,list<Rifornimento *>::const_iterator)));
    connect(rifornimenti, SIGNAL(aggiungereRifornimento(u_int, Rifornimento::tipo_r,float,float,float)), controller, SLOT(aggiungiRifornimento(u_int, Rifornimento::tipo_r,float,float,float)));
    connect(rifornimenti, SIGNAL(modificareRifornimento(u_int, list<Rifornimento *>::const_iterator, Rifornimento::tipo_r,float,float,float)), controller, SLOT(modificaRifornimento(u_int, list<Rifornimento *>::const_iterator, Rifornimento::tipo_r,float,float,float)));

    updateLista();
}

void Liberty::mostraErrore(const QString &errore)
{
    // mostro un messaggio di errore in caso si verifichino per esempio delle eccezioni
    errMess->showMessage(errore);
    errMess->exec();
}

void Liberty::updateDetagli()
{
    // aggiorno il widget con i dettagli. Viene chiamato dal controller quando vanno a buon fine modifiche sui rifornimenti o sui dettagli stessi
    dettagli->updateDati();
}

void Liberty::updateLista()
{
    // aggiorno la lista dei veicoli sul widget di sx; chiamata nel caso ci eliminazioni di veicoli
    info_veicolo->hide();
    listaWidgetVeicoli->clear();
    int num = controller->getNumVeicoli();

    for(int i=0; i<num; i++){
        VeicoloListWidgetItem* vItem = new VeicoloListWidgetItem(controller->getVeicoloAt(i), i);
        vItem->setText(controller->getNomeVeicolo(i));
        listaWidgetVeicoli->addItem(vItem);
    }
}

void Liberty::windowNuovoVeicolo()
{
    // mostro la schermata per aggiungere un nuovo veicolo
    SetVeicoloWidget * add = new SetVeicoloWidget();
    connect(add,SIGNAL(salvare(QString,QString,QString,float,Rifornimento::tipo_r,float,u_short,u_int,u_int,float,float)),controller,SLOT(aggiungiVeicolo(QString,QString,QString,float,Rifornimento::tipo_r,float,u_short,u_int,u_int,float,float)));
    add->show();
}

void Liberty::askEliminaVeicolo()
{
    QList<QListWidgetItem *> items = listaWidgetVeicoli->selectedItems();

    if (items.empty()) return; // se non c'è nessun elemento selezionato non faccio niente

    // chiedo se si è sicuri di eliminare i veicoli selezionati
    QMessageBox::StandardButton risposta = QMessageBox::question(this, "Elimina", "Eliminare TUTTI gli elementi selezionati?", QMessageBox::Yes|QMessageBox::No);
    if (risposta == QMessageBox::Yes){

        u_short count=0; // uso un contatore perché ad ogni veicolo eliminato cambia la posizione dei successivi
        for (QListWidgetItem * i : items) {
            auto vlwi =dynamic_cast<VeicoloListWidgetItem* >(i);
            if(vlwi != nullptr){
                controller->eliminaVeicolo(vlwi->getPosizione()-count);
                count++;
            }
        }
    }
    updateLista();
}

void Liberty::veicoloAggiunto(const Veicolo * v, const u_int & posizione)
{
    // aggiungo un nuovo veicolo che è stato aggiunto alla lista. Viene chiamato dal controller quando l'agginta di un nuovo veicolo è andata a buon fine
    VeicoloListWidgetItem* vItem = new VeicoloListWidgetItem(v, posizione);
    vItem->setText(controller->getNomeVeicolo(posizione));
    listaWidgetVeicoli->addItem(vItem);
    listaWidgetVeicoli->clearSelection(); // deseleziono i veicoli selezionati
    info_veicolo->hide(); // nascondo le info a dx
}

void Liberty::visibilitaInfoVeicolo()
{
    QList<QListWidgetItem *> items = listaWidgetVeicoli->selectedItems();
    if ((!info_veicolo->isHidden()) && items.count()!=1)
        info_veicolo->hide(); // nascondo se non ho selezionato un numero di elementi diverso da 1
    else if(info_veicolo->isHidden() && items.count()==1)
        info_veicolo->show(); // altrimenti mostro
}


void Liberty::setStyle()
{
    setMinimumSize(QSize(970,500)); // dimensioni minime
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    listaWidgetVeicoli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding); // la colonna di sx resta "piccola" se si allarga la schermata
}

void Liberty::addMenu()
{
    QMenuBar* menubar = new QMenuBar(this);
    QMenu* menu = new QMenu("File", menubar);

    QAction* nuovoVeicolo = new QAction("Nuovo veicolo", menu);

    QAction* elimina = new QAction("Elimina selezionati", menu);
    QAction* exit = new QAction("Esci", menu);

    connect(nuovoVeicolo, SIGNAL(triggered()), this, SLOT(windowNuovoVeicolo()));
    connect(elimina, SIGNAL(triggered()), this, SLOT(askEliminaVeicolo()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(nuovoVeicolo);
    menu->addAction(elimina);
    menu->addAction(exit);

    menubar->addMenu(menu);

    menubar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);

    mainLayout->addWidget(menubar);
}

