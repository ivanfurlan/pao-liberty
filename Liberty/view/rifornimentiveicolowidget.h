#ifndef RIFORNIMENTIVEICOLOWIDGET_H
#define RIFORNIMENTIVEICOLOWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "veicololistwidgetitem.h"
#include "setrifornimentowidget.h"
#include "../model/autoibrida.h"
#include "../model/rifornimento.h"

using std::list;

class RifornimentiVeicoloWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit RifornimentiVeicoloWidget(QWidget *parent = nullptr);

    public slots:
        void updateDati(QListWidgetItem* = nullptr);
        void askEliminaRifornimento();
        void windowRifornimento(bool modifica = false);
        void prepareSignalAggiungere(Rifornimento::tipo_r,float,float,float);
        void convertSignalModifica();
        void prepareSignalModifica(Rifornimento::tipo_r,float,float,float);

    signals:
        void eliminareRifornimento(u_int,u_int);
        void aggiungereRifornimento(u_int, Rifornimento::tipo_r,float,float,float);
        void modificareRifornimento(u_int, u_int, Rifornimento::tipo_r,float,float,float);

    private:
        QListWidgetItem * current_item;

        QTableWidget * tableRifornimenti;
        QPushButton * aggiungi;
        QPushButton * modifica;
        QPushButton * elimina;



};

#endif // RIFORNIMENTIVEICOLOWIDGET_H
