#include "setrifornimentowidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QComboBox>
#include "../model/rifornimento.h"

SetRifornimentoWidget::SetRifornimentoWidget(QList<std::string> tipi_concessi, QWidget *parent) : QWidget(parent), tipo(new QComboBox(this)), quantita(new QLineEdit(this)), km(new QLineEdit(this)), totale(new QLineEdit(this))
{
    QHBoxLayout * layout = new QHBoxLayout();
    setLayout(layout);

    QVBoxLayout * labelLayout = new QVBoxLayout();
    QVBoxLayout * editLayout = new QVBoxLayout();

    QLabel * tipoLabel = new QLabel("Tipo",this);
    QLabel * quantitaLabel = new QLabel("Quantita",this);
    QLabel * kmLabel = new QLabel("Km",this);
    QLabel * totaleLabel = new QLabel("Totale",this);

    for (auto t : tipi_concessi) {
        tipo->addItem(QString::fromStdString(t));
    }

    QRegExp validator;
    validator.setPattern("[0-9]+([/.|/,][0-9]+)?");
    quantita->setValidator(new QRegExpValidator(validator,this));
    km->setValidator(new QRegExpValidator(validator,this));
    totale->setValidator(new QRegExpValidator(validator,this));

    labelLayout->addWidget(tipoLabel);
    labelLayout->addWidget(quantitaLabel);
    labelLayout->addWidget(kmLabel);
    labelLayout->addWidget(totaleLabel);
    editLayout->addWidget(tipo);
    editLayout->addWidget(quantita);
    editLayout->addWidget(km);
    editLayout->addWidget(totale);
    editLayout->addWidget(tipo);

    QPushButton * annulla = new QPushButton("Annulla", this);
    QPushButton * salva = new QPushButton("Salva", this);
    labelLayout->addWidget(annulla);
    editLayout->addWidget(salva);

    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));
    connect(salva,SIGNAL(clicked()),this,SLOT(prepareSignal()));

    layout->addLayout(labelLayout);
    layout->addLayout(editLayout);

    show();
}

void SetRifornimentoWidget::setValues(float q, float k, float t)
{
    quantita->setText(QString::number(q));
    km->setText(QString::number(k));
    totale->setText(QString::number(t));
}

void SetRifornimentoWidget::prepareSignal()
{
    emit salvare(Rifornimento::string_tipo[tipo->currentText().toStdString()],quantita->text().toFloat(), km->text().toFloat(),totale->text().toFloat());
    close();
}
