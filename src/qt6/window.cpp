#include "ui_window.h"
#include "window.hpp"

AppWindow::AppWindow(QMainWindow *parent) : QMainWindow(parent) {
    ui = new Ui::AppWindow;
    ui->setupUi(parent);

    this->setAttribute(Qt::WA_DeleteOnClose);
    
    connect(ui->button, &QPushButton::pressed, this, &AppWindow::onButtonClick);
    this->parent = parent;
}

AppWindow::~AppWindow() {
    delete ui;
}

void AppWindow::onButtonClick() {
    ui->textbox->setText("CLIKED!");
}
