#ifndef WINDOW_INCLUDED_HPP
#define WINDOW_INCLUDED_HPP

#include "ui_window.h"

class AppWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit AppWindow(QMainWindow *parent = nullptr);
        ~AppWindow();

    private slots:
        void onButtonClick();

    private:
        Ui::AppWindow *ui;
        QMainWindow *parent;
};

#endif
