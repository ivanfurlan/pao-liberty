#include "liberty.h"

#include "../controller/controller.h"

Liberty::Liberty(Controller * c, QWidget *parent) : QWidget(parent), controller(c), rifornimenti(new RifornimentiVeicoloWidget(this)), listaWidgetVeicoli(new QListWidget(this)), dettagli(new DettagliVeicoliWidget(this)), info_veicolo(new QTabWidget(this))
{
    mainLayout = new QVBoxLayout(this);
    addMenu();

    QHBoxLayout* veicoliLayout = new QHBoxLayout();
    veicoliLayout->setAlignment(Qt::AlignLeft);

    listaWidgetVeicoli->setSelectionMode(QListWidget::SelectionMode::ExtendedSelection);

    updateLista();

    veicoliLayout->addWidget(listaWidgetVeicoli);

    veicoliLayout->addWidget(info_veicolo);
    info_veicolo->addTab(dettagli,"Veicolo");
    info_veicolo->addTab(rifornimenti,"Rifornimenti");

    mainLayout->addLayout(veicoliLayout);

    setStyle();
    setLayout(mainLayout);

    connect(info_veicolo, SIGNAL(currentChanged(int)), dettagli, SLOT(updateDati()));
    connect(info_veicolo, SIGNAL(currentChanged(int)), rifornimenti, SLOT(updateDati()));

    connect(listaWidgetVeicoli, SIGNAL(itemClicked(QListWidgetItem *)), dettagli, SLOT(updateDati(QListWidgetItem *)));
    connect(listaWidgetVeicoli, SIGNAL(itemClicked(QListWidgetItem *)), rifornimenti, SLOT(updateDati(QListWidgetItem *)));
    connect(listaWidgetVeicoli, SIGNAL(itemSelectionChanged()), this, SLOT(visibilitaInfoVeicolo())); // sennò se si deselezionano tutti resta comunque una scheda aperta

    connect(dettagli, SIGNAL(richiestaSalvataggio(u_int, string, string, u_int, u_short, u_int, u_short, u_short, float, float, u_int)), controller, SLOT(salvaModificheVeicolo(u_int, string, string, u_int, u_short, u_int, u_short, u_short, float, float, u_int)));

    connect(rifornimenti, SIGNAL(eliminareRifornimento(u_int,u_int)), controller, SLOT(eliminaRifornimento(u_int,u_int)));
    connect(rifornimenti, SIGNAL(aggiungereRifornimento(u_int, Rifornimento::tipo_r,float,float,float)), controller, SLOT(aggiungiRifornimento(u_int, Rifornimento::tipo_r,float,float,float)));
    connect(rifornimenti, SIGNAL(modificareRifornimento(u_int, u_int, Rifornimento::tipo_r,float,float,float)), controller, SLOT(modificaRifornimento(u_int, u_int, Rifornimento::tipo_r,float,float,float)));
}

Liberty::~Liberty()
{
}

void Liberty::updateLista() // TO DO: da Togliere e far fare al controller?
{
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
    SetVeicoloWidget * add = new SetVeicoloWidget();
    connect(add,SIGNAL(salvare(QString,QString,QString,float,Rifornimento::tipo_r,float,u_short,u_int,u_int,float,float)),controller,SLOT(aggiungiVeicolo(QString,QString,QString,float,Rifornimento::tipo_r,float,u_short,u_int,u_int,float,float)));
    add->show();
}

void Liberty::askEliminaVeicolo()
{
    QList<QListWidgetItem *> item = listaWidgetVeicoli->selectedItems();
    if (item.empty()) return;
    if (QMessageBox::question(this, "Elimina", "Eliminare TUTTI gli elementi selezionati?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        // TO DO: sarebbe da fare gl iiteratori con il puntatore non con la posizione
        u_short count=0;
        for (QListWidgetItem * i : item) {
            auto vlwi=dynamic_cast<VeicoloListWidgetItem *>(i);
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
    VeicoloListWidgetItem* vItem = new VeicoloListWidgetItem(v, posizione);
    vItem->setText(controller->getNomeVeicolo(posizione));
    listaWidgetVeicoli->addItem(vItem);
}

void Liberty::visibilitaInfoVeicolo()
{
    QList<QListWidgetItem *> item = listaWidgetVeicoli->selectedItems();
    if (item.empty() && !info_veicolo->isHidden())
        info_veicolo->hide();
    else if(!item.empty() && info_veicolo->isHidden())
        info_veicolo->show();
}


void Liberty::setStyle()
{
    setMinimumSize(QSize(970,500));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    listaWidgetVeicoli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
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

