#ifndef LIBERTY_H
#define LIBERTY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMenuBar>
#include <QTabWidget>
#include <QMessageBox>
#include <QFile>

#include "dettagliveicoliwidget.h"
#include "rifornimentiveicolowidget.h"

class Controller;

class Liberty : public QWidget
{
        Q_OBJECT
    public:
        Liberty(Controller* c,QWidget *parent = nullptr);
        ~Liberty();

        void updateLista();
    signals:
        void selezionatoVeicolo(const Veicolo *);

    public slots:
        void askEliminaVeicolo();
        void veicoloAggiunto(const Veicolo *, const u_int &);
        void visibilitaInfoVeicolo();

    private:
        void setStyle();
        void addMenu();

        Controller* controller;

        RifornimentiVeicoloWidget* rifornimenti;
        QVBoxLayout* mainLayout;
        QListWidget* listaWidgetVeicoli;
        DettagliVeicoliWidget* dettagli;
        QTabWidget * info_veicolo;
};
#endif // LIBERTY_H
