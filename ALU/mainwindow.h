#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "alu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_Suma_clicked();

    void on_pushButton_Producto_clicked();

    void on_pushButton_Division_clicked();

    void on_pushButton_reset_clicked();


private:
    Ui::MainWindow *ui;
    alu alu;
    QString printNum(union Code a);
    int StringToFloat(char *dest, float x);

};

#endif // MAINWINDOW_H
