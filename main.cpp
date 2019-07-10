#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "main_widget.h"
#include "system_resouce_usage.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    MainWidget *widget = new MainWidget();
    window.setCentralWidget(widget);
    window.resize(900,600);
    window.show();
    return a.exec();
}
