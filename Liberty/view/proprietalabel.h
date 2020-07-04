#ifndef PROPRIETAVEICOLOLABEL_H
#define PROPRIETAVEICOLOLABEL_H

#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>

class ProprietaLabel : public QHBoxLayout
{
        Q_OBJECT
    public:
        ProprietaLabel(const QString & n, const bool & m = false, QWidget *parent = nullptr);
        ProprietaLabel(const QString & n, QWidget *parent = nullptr);

        QString getTextModifica() const;
        const bool& visible() const;

        void setProprietaText(const QString&);
        void setProprietaNumber(const double&);
        void setProprietaNumber(const double&, const QString&);
        void hide();
        void show();
    public slots:
        void permettiModifica();

    private:
        void addWidgets();

        QWidget * parent;

        bool isVisible;
        bool isModificabile;

        // tutti gli oggetti puntati dai puntatori li elimina qt
        QLabel * nome;
        QLabel * valore;
        QLineEdit * modificaValore;
};

#endif // PROPRIETAVEICOLOLABEL_H
