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
        void windowRifornimento(const bool modifica = false);
        void prepareSignalAggiungere(const Rifornimento::tipo_r,const float,const float,const float);
        void convertSignalModifica();
        void prepareSignalModifica(const Rifornimento::tipo_r,const float,const float,const float);

    signals:
        void eliminareRifornimento(const u_int,list<Rifornimento *>::const_iterator);
        void aggiungereRifornimento(const u_int, const Rifornimento::tipo_r,const float,const float,const float);
        void modificareRifornimento(const u_int, list<Rifornimento *>::const_iterator, const Rifornimento::tipo_r,const float,const float,const float);

    private:
        // tutti gli oggetti puntati dai puntatori li elimina qt
        QListWidgetItem * current_item;

        QTableWidget * tableRifornimenti;
        QPushButton * aggiungi;
        QPushButton * modifica;
        QPushButton * elimina;



};

#endif // RIFORNIMENTIVEICOLOWIDGET_H
