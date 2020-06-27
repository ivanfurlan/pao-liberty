#include "proprietaveicololabel.h"

ProprietaVeicoloLabel::ProprietaVeicoloLabel(const QString &n, const bool & m, QWidget *parent) : parent(parent), isModificabile(m), nome(new QLabel(n + ": ", parent)), valore(new QLabel(parent)), modificaValore(new QLineEdit(parent))
{
    connect(parent, SIGNAL(startModifica()), this, SLOT(permettiModifica()));
    addWidgets();
}

ProprietaVeicoloLabel::ProprietaVeicoloLabel(const QString &n, QWidget *parent) : parent(parent), isModificabile(false), nome(new QLabel(n + ": ", parent)), valore(new QLabel(parent)), modificaValore(new QLineEdit(parent))
{
    connect(parent, SIGNAL(startModifica()), this, SLOT(permettiModifica()));
    addWidgets();
}


void ProprietaVeicoloLabel::setProprietaText(const QString & valore)
{
    reset();
    modificaValore->clear();
    this->valore->setText(valore);
    modificaValore->setText(valore);
}

void ProprietaVeicoloLabel::setProprietaNumber(const double & valore)
{
    reset();
    this->valore->setNum(valore);
}

void ProprietaVeicoloLabel::setProprietaNumber(const double & valore, const QString & unita)
{
    reset();

    if(valore-static_cast<int>(valore)<0.001){
        this->valore->setText(QString::number(valore)+" "+unita);
        modificaValore->setText(QString::number(valore));
    }else{
        this->valore->setText(QString::number(valore,'f',2)+" "+unita);
        modificaValore->setText(QString::number(valore,'f',2));
    }

}


void ProprietaVeicoloLabel::hide()
{
    modificaValore->hide();
    isVisible=false;
    //if(!nome->isHidden()){
    nome->setHidden(true);
    valore->setHidden(true);
    //}
}

void ProprietaVeicoloLabel::show()
{
    modificaValore->hide();
    isVisible=true;
    //if(nome->isHidden()){
    nome->setHidden(false);
    valore->setHidden(false);
    //}
}

void ProprietaVeicoloLabel::permettiModifica()
{
    if(isVisible && isModificabile){
        valore->hide();
        modificaValore->show();
    }
}

void ProprietaVeicoloLabel::addWidgets()
{
    align= Qt::AlignLeft;
    nome->setAlignment(Qt::AlignRight);
    nome->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    nome->setAlignment(Qt::AlignLeft);
    valore->setAlignment(Qt::AlignLeft);
    valore->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    modificaValore->setAlignment(Qt::AlignLeft);
    modificaValore->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    modificaValore->hide();
    addWidget(nome);
    addWidget(valore);
    addWidget(modificaValore);
}

void ProprietaVeicoloLabel::reset()
{
    //valore->clear();
    show();
}
