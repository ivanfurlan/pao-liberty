#ifndef LIBERTY_H
#define LIBERTY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMenuBar>
#include <QTabWidget>
#include <QMessageBox>
#include <QFile>
#include <QErrorMessage>

#include "dettagliveicoliwidget.h"
#include "rifornimentiveicolowidget.h"
#include "setveicolowidget.h"

class Controller;

class Liberty : public QWidget
{
        Q_OBJECT
    public:
        Liberty(Controller* c,QWidget *parent = nullptr);

        void mostraErrore(const QString& = "Si è verificato un errore nell'eseguire l'operazione richiesta");
        void updateDetagli();

    public slots:
        void updateLista();
        void windowNuovoVeicolo();
        void askEliminaVeicolo();
        void veicoloAggiunto(const Veicolo *, const u_int &);
        void visibilitaInfoVeicolo();

    signals:
        void selezionatoVeicolo(const Veicolo *);

    private:
        void setStyle();
        void addMenu();

        Controller* controller;

        // tutti gli oggetti puntati dai puntatori li elimina qt
        QVBoxLayout* mainLayout;
        QListWidget* listaWidgetVeicoli;
        QTabWidget * info_veicolo;
        DettagliVeicoliWidget* dettagli;
        RifornimentiVeicoloWidget* rifornimenti;
        QErrorMessage * errMess;
};
#endif // LIBERTY_H
