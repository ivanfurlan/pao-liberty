#include "setrifornimentowidget.h"

SetRifornimentoWidget::SetRifornimentoWidget(QList<std::string> tipi_concessi, QWidget *parent) : QWidget(parent), tipo(new QComboBox(this)), quantita(new QLineEdit(this)), km(new QLineEdit(this)), totale(new QLineEdit(this))
{
    QGridLayout * layout = new QGridLayout();
    setLayout(layout);

    QLabel * tipoLabel = new QLabel("Tipo",this);
    QLabel * quantitaLabel = new QLabel("Quantita",this);
    QLabel * kmLabel = new QLabel("Km",this);
    QLabel * totaleLabel = new QLabel("Totale",this);

    for (auto t : tipi_concessi) {
        tipo->addItem(QString::fromStdString(t));
        tipo->setItemData(tipo->count()-1,Rifornimento::string_tipo[t]);
    }

    QRegExp validator;
    validator.setPattern("[0-9]+([/.][0-9]+)?");
    QRegExpValidator * regValidator = new QRegExpValidator(validator,this);
    quantita->setValidator(regValidator);
    km->setValidator(regValidator);
    totale->setValidator(regValidator);

    u_short riga=0;

    layout->addWidget(tipoLabel,riga++,0);
    layout->addWidget(quantitaLabel,riga++,0);
    layout->addWidget(kmLabel,riga++,0);
    layout->addWidget(totaleLabel,riga++,0);
    riga=0;
    layout->addWidget(tipo,riga++,1);
    layout->addWidget(quantita,riga++,1);
    layout->addWidget(km,riga++,1);
    layout->addWidget(totale,riga++,1);

    QPushButton * annulla = new QPushButton("Annulla", this);
    QPushButton * salva = new QPushButton("Salva", this);
    layout->addWidget(annulla,riga,0);
    layout->addWidget(salva,riga,1);

    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));
    connect(salva,SIGNAL(clicked()),this,SLOT(prepareSignal()));

    show();
}

void SetRifornimentoWidget::setValues(Rifornimento::tipo_r tr, float q, float k, float t)
{
    tipo->setCurrentIndex(tipo->findData(tr));
    quantita->setText(QString::number(q));
    km->setText(QString::number(k));
    totale->setText(QString::number(t));
}

void SetRifornimentoWidget::prepareSignal()
{
    emit salvare(Rifornimento::string_tipo[tipo->currentText().toStdString()],quantita->text().toFloat(), km->text().toFloat(),totale->text().toFloat());
    close();
}
