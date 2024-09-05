#include "cpu.hpp"
#include <QApplication>
#include <QPushButton>
#include "ui_window.h"
#include "window.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QMainWindow *mainWindow = new QMainWindow; // This gets freed internally by Qt, no need to free in main()

    AppWindow ui(mainWindow);

    mainWindow->show();
    int ret = app.exec();

    return ret;
}
