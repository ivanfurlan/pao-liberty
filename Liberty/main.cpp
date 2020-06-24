#include "view/liberty.h"
#include "model/model.h"
#include "controller/controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Liberty view;
    view.show();
    return a.exec();
}
