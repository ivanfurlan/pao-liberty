#ifndef LIBERTY_H
#define LIBERTY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QGridLayout>
#include <QMenuBar>
#include <QFile>
#include <QLabel>
#include <QSizeGrip>
#include <QSplitter>

#include <string>

using std::string;

class DettagliVeicoliWidget;
class Veicolo;
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
        void askRifornisciVeicolo();
        void askModificaVeicolo();
        void askEliminaVeicolo();
        void veicoloAggiunto(const Veicolo *, const u_int &);

    private:
        void setStyle();
        void addMenu();

        Controller* controller;

        QVBoxLayout* mainLayout;
        QListWidget* listaWidgetVeicoli;
        DettagliVeicoliWidget* dettagli;
};
#endif // LIBERTY_H
