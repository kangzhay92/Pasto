#include <QApplication>
#include "pasto.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Pasto win;
    win.show();
    return app.exec();
}
