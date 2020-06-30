#ifndef PROPRIETAVEICOLOLABEL_H
#define PROPRIETAVEICOLOLABEL_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

class ProprietaLabel : public QHBoxLayout
{
        Q_OBJECT
    public:
        ProprietaLabel(const QString & n, const bool & m = false, QWidget *parent = nullptr);
        ProprietaLabel(const QString & n, QWidget *parent = nullptr);

        QString getTextModifica() const;
        bool visible() const;

        void setProprietaText(const QString&);
        void setProprietaNumber(const double&);
        void setProprietaNumber(const double&, const QString&);
        void hide();
        void show();
    public slots:
        void permettiModifica();

    private:
        void addWidgets();
        //void reset();
        QWidget * parent;

        bool isVisible;
        bool isModificabile;

        QLabel * nome;
        QLabel * valore;
        QLineEdit * modificaValore;
};

#endif // PROPRIETAVEICOLOLABEL_H
