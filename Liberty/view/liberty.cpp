#include "liberty.h"
#include "../controller/controller.h"
#include "dettagliveicoliwidget.h"
#include "veicololistwidgetitem.h"
#include <QMessageBox>

Liberty::Liberty(Controller * c, QWidget *parent) : QWidget(parent), controller(c), listaWidgetVeicoli(new QListWidget(this)), dettagli(new DettagliVeicoliWidget(this))
{
    mainLayout = new QVBoxLayout(this);
    addMenu();

    QHBoxLayout* veicoliLayout = new QHBoxLayout();
    //QSplitter* veicoliLayout = new QSplitter(Qt::Horizontal);
    //veicoliLayout->setMinimumWidth(300);

    updateLista();

    // connect(listaWidgetVeicoli, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(updateDettagli(QListWidgetItem *))); // Viene già fatto dal click singolo
    connect(listaWidgetVeicoli, SIGNAL(itemClicked(QListWidgetItem *)), dettagli, SLOT(updateDati(QListWidgetItem *)));

    veicoliLayout->addWidget(listaWidgetVeicoli);

    //QWidget * dettagliWidget= new QWidget;
    //dettagliWidget->setLayout(dettagli);

    //veicoliLayout->addWidget(dettagliWidget);
    veicoliLayout->addWidget(dettagli);
    mainLayout->addLayout(veicoliLayout);

    setStyle();
    setLayout(mainLayout);
}

Liberty::~Liberty()
{
}

void Liberty::updateLista() // TO DO: da Togliere e far fare al controller?
{
    int num = controller->getNumVeicoli();
    int i = 0;
    for(i = 0; i<listaWidgetVeicoli->count(); ++i){
        auto veicoloItem = dynamic_cast<VeicoloListWidgetItem*>(listaWidgetVeicoli->takeItem(i));
        if(i<num){
            veicoloItem->setPosizione(i);
            veicoloItem->setVeicolo(controller->getVeicoloAt(i));
            veicoloItem->setText(controller->getNomeVeicolo(i));
        }else{
            listaWidgetVeicoli->removeItemWidget(veicoloItem);
        }
    }
    for(; i<num; ++i){
        VeicoloListWidgetItem* vItem = new VeicoloListWidgetItem(controller->getVeicoloAt(i), i);
        vItem->setText(controller->getNomeVeicolo(i));
        listaWidgetVeicoli->addItem(vItem);
    }
}

void Liberty::askRifornisciVeicolo()
{

}

void Liberty::askModificaVeicolo()
{

}

void Liberty::askEliminaVeicolo()
{
    QListWidgetItem * item = listaWidgetVeicoli->currentItem();
    if (!item) return;
    if (QMessageBox::question(this, "Elimina", "Eliminare l'elemento selezionato?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
        // TO DO: segnale per eliminare
    }

}

void Liberty::veicoloAggiunto(const Veicolo * v, const u_int & posizione)
{
    VeicoloListWidgetItem* vItem = new VeicoloListWidgetItem(v, posizione);
    vItem->setText(controller->getNomeVeicolo(posizione));
    listaWidgetVeicoli->addItem(vItem);
}


void Liberty::setStyle()
{
    setMinimumSize(QSize(600,500));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QFile file(":/resources/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}

void Liberty::addMenu()
{
    QMenuBar* menubar = new QMenuBar(this);
    QMenu* menu = new QMenu("File", menubar);

    QMenu* menuNuovoVeicolo = new QMenu("Nuovo veicolo", menu);

    QAction* autoElettrica = new QAction("Auto elettrica", menuNuovoVeicolo);
    QAction* autoTermica = new QAction("Auto termica", menuNuovoVeicolo);
    QAction* autoIbrida = new QAction("Auto ibrida", menuNuovoVeicolo);

    QAction* exit = new QAction("Esci", menu);

    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

    menuNuovoVeicolo->addAction(autoElettrica);
    menuNuovoVeicolo->addAction(autoTermica);
    menuNuovoVeicolo->addAction(autoIbrida);

    menu->addMenu(menuNuovoVeicolo);
    menu->addAction(exit);

    menubar->addMenu(menu);

    mainLayout->addWidget(menubar);
}

