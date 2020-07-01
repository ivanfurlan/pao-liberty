#include "proprietalabel.h"

ProprietaLabel::ProprietaLabel(const QString &n, const bool & m, QWidget *parent) : parent(parent), isModificabile(m), nome(new QLabel(n + ": ", parent)), valore(new QLabel(parent)), modificaValore(new QLineEdit(parent))
{
    connect(parent, SIGNAL(startModifica()), this, SLOT(permettiModifica()));
    addWidgets();
}

ProprietaLabel::ProprietaLabel(const QString &n, QWidget *parent) : parent(parent), isModificabile(false), nome(new QLabel(n + ": ", parent)), valore(new QLabel(parent)), modificaValore(new QLineEdit(parent))
{
    connect(parent, SIGNAL(startModifica()), this, SLOT(permettiModifica()));
    addWidgets();
}

QString ProprietaLabel::getTextModifica() const
{
    return modificaValore->text();
}

bool ProprietaLabel::visible() const
{
    return isVisible;
}


void ProprietaLabel::setProprietaText(const QString & valore)
{
    show();
    modificaValore->clear();
    this->valore->setText(valore);
    modificaValore->setText(valore);

    QRegExp validator;
    validator.setPattern(".*");
    modificaValore->setValidator(new QRegExpValidator(validator,parent));
}

void ProprietaLabel::setProprietaNumber(const double & valore)
{
    show();

    if(valore-static_cast<int>(valore)<0.001){
        this->valore->setText(QString::number(valore));
        modificaValore->setText(QString::number(valore));
    }else{
        this->valore->setText(QString::number(valore,'f',2));
        modificaValore->setText(QString::number(valore,'f',2));
    }


    QRegExp validator;
    validator.setPattern("[0-9]+([/.|/,][0-9]+)?");
    modificaValore->setValidator(new QRegExpValidator(validator,parent));
}

void ProprietaLabel::setProprietaNumber(const double & valore, const QString & unita)
{
    show();

    if(valore-static_cast<int>(valore)<0.001){
        this->valore->setText(QString::number(valore)+" "+unita);
        modificaValore->setText(QString::number(valore));
    }else{
        this->valore->setText(QString::number(valore,'f',2)+" "+unita);
        modificaValore->setText(QString::number(valore,'f',2));
    }


    QRegExp validator;
    validator.setPattern("[0-9]+([/.|/,][0-9]+)?");
    modificaValore->setValidator(new QRegExpValidator(validator,parent));

}


void ProprietaLabel::hide()
{
    modificaValore->hide();
    isVisible=false;
    //if(!nome->isHidden()){
    nome->setHidden(true);
    valore->setHidden(true);
    //}
}

void ProprietaLabel::show()
{
    modificaValore->hide();
    isVisible=true;
    //if(nome->isHidden()){
    nome->setHidden(false);
    valore->setHidden(false);
    //}
}

void ProprietaLabel::permettiModifica()
{
    if(isVisible && isModificabile){
        valore->hide();
        modificaValore->show();
    }
}

void ProprietaLabel::addWidgets()
{
    align = Qt::AlignLeft;

    nome->setAlignment(Qt::AlignLeft);
    nome->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    valore->setAlignment(Qt::AlignLeft);
    valore->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    modificaValore->setAlignment(Qt::AlignLeft);
    modificaValore->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    modificaValore->hide();
    addWidget(nome);
    addWidget(valore);
    addWidget(modificaValore);
}
/*
void ProprietaLabel::reset()
{
    //valore->clear();
    show();
}
*/
