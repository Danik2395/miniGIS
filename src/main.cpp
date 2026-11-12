#include <QApplication>
#include "ui/gappwindow.h"

int main(int argc, char* argv[])
{
    QApplication qapp(argc, argv);

    GAppWindow g_app_window;
    g_app_window.show();

    return qapp.exec();
}
