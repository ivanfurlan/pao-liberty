#include "proprietalabel.h"

ProprietaLabel::ProprietaLabel(const QString &n, const bool & m, QWidget *parent) : parent(parent), isModificabile(m), nome(new QLabel(n + ": ", parent)), valore(new QLabel(parent)), modificaValore(new QLineEdit(parent))
{
    // collego ogni oggetto di questa classe con il segnale del padre che viene emesso quando viene premuto il tasto modifica
    // così facendo anche gli elementi di questa classe permetteranno la modifica
    connect(parent, SIGNAL(startModifica()), this, SLOT(permettiModifica()));
    addWidgets();
}

ProprietaLabel::ProprietaLabel(const QString &n, QWidget *parent) : parent(parent), isModificabile(false), nome(new QLabel(n + ": ", parent)), valore(new QLabel(parent)), modificaValore(new QLineEdit(parent))
{
    // collego ogni oggetto di questa classe con il segnale del padre che viene emesso quando viene premuto il tasto modifica
    // così facendo anche gli elementi di questa classe permetteranno la modifica
    connect(parent, SIGNAL(startModifica()), this, SLOT(permettiModifica()));
    addWidgets();
}

const QString ProprietaLabel::getTextModifica() const
{
    return modificaValore->text();
}

const bool& ProprietaLabel::visible() const
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
    validator.setPattern(".*"); // accetto solo una stringa normale
    modificaValore->setValidator(new QRegExpValidator(validator,parent));
}

void ProprietaLabel::setProprietaNumber(const double & valore)
{
    show();

    if(valore-static_cast<int>(valore)<0.001){ // se è un numero "quasi intero", lo mostro come intero
        this->valore->setText(QString::number(valore));
        modificaValore->setText(QString::number(valore));
    }else{
        this->valore->setText(QString::number(valore,'f',2));
        modificaValore->setText(QString::number(valore,'f',2));
    }


    QRegExp validator;
    validator.setPattern("[0-9]+([/.][0-9]+)?"); // accetto solo numeri
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
    validator.setPattern("[0-9]+([/.][0-9]+)?"); // accetto solo numeri
    modificaValore->setValidator(new QRegExpValidator(validator,parent));

}


void ProprietaLabel::hide()
{
    modificaValore->hide();
    isVisible=false;
    nome->hide();
    valore->hide();
}

void ProprietaLabel::show()
{
    modificaValore->hide();
    isVisible=true;
    nome->show();
    valore->show();
}

void ProprietaLabel::permettiModifica()
{
    // permetto la modifica solo se l'oggetto è modificabile ed è attualmente visualizzato a schermo
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
