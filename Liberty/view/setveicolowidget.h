#ifndef SETVEICOLOWIDGET_H
#define SETVEICOLOWIDGET_H

#include <QWidget>
#include <QComboBox>

class SetVeicoloWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit SetVeicoloWidget(QWidget *parent = nullptr);

    public slots:
        //void prepareSignal();
    signals:
        //void salvare(float,float,float);
    private:
        QComboBox * tipo;
        QLineEdit * quantita;
        QLineEdit * km;
        QLineEdit * totale;

};

#endif // SETVEICOLOWIDGET_H
