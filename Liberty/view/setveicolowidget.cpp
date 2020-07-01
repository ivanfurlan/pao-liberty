#include "setveicolowidget.h"

Q_DECLARE_METATYPE(Rifornimento::tipo_r)

SetVeicoloWidget::SetVeicoloWidget(QWidget *parent) : QWidget(parent), cavalli_tLabel(new QLabel("Cavalli termici",this)), cavalli_eLabel(new QLabel("Cavalli elettrici",this)), serbatoioLabel(new QLabel("Capacità serbatoio",this)), batteriaLabel(new QLabel("Capacità batteria",this)), tipo(new QComboBox(this)), marca(new QLineEdit(this)), modello(new QLineEdit(this)), tipo_carburante(new QComboBox(this)), peso(new QLineEdit(this)), posti_sedere(new QLineEdit(this)), cavalli_t(new QLineEdit(this)), cavalli_e(new QLineEdit(this)), serbatoio(new QLineEdit(this)), batteria(new QLineEdit(this))
{

    QGridLayout * layout = new QGridLayout();
    setLayout(layout);

    tipo->addItem("Auto Termica");
    tipo->addItem("Auto Elettrica");
    tipo->addItem("Auto Ibrida");

    for (auto t : Rifornimento::tipo_string) {
        tipo_carburante->addItem(QString::fromStdString(t.second),t.first);
    }

    QLabel * tipoLabel = new QLabel("Tipo di veicolo",this);
    QLabel * marcaLabel = new QLabel("Marca",this);
    QLabel * modelloLabel = new QLabel("Modello",this);
    QLabel * tipo_carburanteLabel = new QLabel("Tipo di carburante",this);
    QLabel * pesoLabel = new QLabel("Peso",this);
    QLabel * posti_sedereLabel = new QLabel("Posti",this);

    QRegExp validator;
    validator.setPattern("[0-9]+([/.][0-9]+)?");
    QRegExpValidator * regValidator = new QRegExpValidator(validator,this);
    peso->setValidator(regValidator);
    posti_sedere->setValidator(regValidator);
    cavalli_t->setValidator(regValidator);
    cavalli_e->setValidator(regValidator);
    serbatoio->setValidator(regValidator);
    batteria->setValidator(regValidator);

    u_short riga=0;

    layout->addWidget(tipoLabel,riga++,0);
    layout->addWidget(marcaLabel,riga++,0);
    layout->addWidget(modelloLabel,riga++,0);
    layout->addWidget(tipo_carburanteLabel,riga++,0);
    layout->addWidget(pesoLabel,riga++,0);
    layout->addWidget(posti_sedereLabel,riga++,0);
    layout->addWidget(cavalli_tLabel,riga++,0);
    layout->addWidget(cavalli_eLabel,riga++,0);
    layout->addWidget(serbatoioLabel,riga++,0);
    layout->addWidget(batteriaLabel,riga++,0);
    riga=0;
    layout->addWidget(tipo,riga++,1);
    layout->addWidget(marca,riga++,1);
    layout->addWidget(modello,riga++,1);
    layout->addWidget(tipo_carburante,riga++,1);
    layout->addWidget(peso,riga++,1);
    layout->addWidget(posti_sedere,riga++,1);
    layout->addWidget(cavalli_t,riga++,1);
    layout->addWidget(cavalli_e,riga++,1);
    layout->addWidget(serbatoio,riga++,1);
    layout->addWidget(batteria,riga++,1);

    QPushButton * annulla = new QPushButton("Annulla", this);
    QPushButton * salva = new QPushButton("Salva", this);
    layout->addWidget(annulla,riga,0);
    layout->addWidget(salva,riga,1);

    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));
    connect(tipo,SIGNAL(currentTextChanged(const QString &)),this, SLOT(tipoCambiato()));
    connect(salva,SIGNAL(clicked()),this,SLOT(prepareSignal()));

    tipoCambiato();
    show();
}

void SetVeicoloWidget::tipoCambiato()
{
    tipo_carburante->clear();
    for (auto t : Rifornimento::tipo_string) {
        tipo_carburante->addItem(QString::fromStdString(t.second),t.first);
    }
    QString tipoV=tipo->currentText();
    if(tipoV=="Auto Termica"){
        tipo_carburante->removeItem(tipo_carburante->findData(Rifornimento::ELETTRICITA));
        cavalli_e->hide();
        batteria->hide();
        cavalli_t->show();
        serbatoio->show();
        cavalli_eLabel->hide();
        batteriaLabel->hide();
        cavalli_tLabel->show();
        serbatoioLabel->show();
    }
    if(tipoV=="Auto Elettrica"){
        tipo_carburante->removeItem(tipo_carburante->findData(Rifornimento::BENZINA));
        tipo_carburante->removeItem(tipo_carburante->findData(Rifornimento::DIESEL));
        cavalli_e->show();
        batteria->show();
        cavalli_t->hide();
        serbatoio->hide();
        cavalli_eLabel->show();
        batteriaLabel->show();
        cavalli_tLabel->hide();
        serbatoioLabel->hide();
    }
    if(tipoV=="Auto Ibrida"){
        tipo_carburante->removeItem(tipo_carburante->findData(Rifornimento::ELETTRICITA));
        cavalli_e->show();
        batteria->show();
        cavalli_t->show();
        serbatoio->show();
        cavalli_eLabel->show();
        batteriaLabel->show();
        cavalli_tLabel->show();
        serbatoioLabel->show();
    }
}

void SetVeicoloWidget::prepareSignal()
{
    emit salvare(tipo->currentText(),marca->text(),modello->text(),tipo_carburante->currentData().value<Rifornimento::tipo_r>(),peso->text().toFloat(),posti_sedere->text().toFloat(),cavalli_t->text().toFloat(),cavalli_e->text().toFloat(),serbatoio->text().toFloat(),batteria->text().toFloat());
    close();
}
