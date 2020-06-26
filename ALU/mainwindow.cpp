#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alu.h"

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Denormal->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_Suma_clicked()
{
    ui->Denormal->hide();
    alu.infinito = false;
    union Code num1;
    union Code num2;
    union Code res;
    QString num1S;
    QString num2S;

    float var1 = 0.0;
    float var2 = 0.0;

    var1 = ui->lineEdit_in_Num1->text().toFloat();
    var2 = ui->lineEdit_in_Num2->text().toFloat();

    num1.numero = var1;
    num2.numero = var2;
    res.numero = 0.0;

    num1S = printNum(num1);
    num2S = printNum(num2);

    res = alu.suma(num1, num2);

    if(alu.infinito == true){
        ui->lineEdit_out_Resultado->setText("Infinito");

        ui->lineEdit_outIEEE_Resultado->setText("Infinito");
        ui->lineEdit_outHex_Resultado->setText("Infinito");

        alu.infinito = false; //la restauro
    }
    else
    {
        ui->lineEdit_out_Resultado->setText(QString::number(res.numero, 'G', 7));

        ui->lineEdit_outIEEE_Resultado->setText(printNum(res));
        ui->lineEdit_outHex_Resultado->setText("0x"+QString::number((int)res.numero, 16));

    }

    ui->lineEdit_outIEEE_Num1->setText(num1S);
    ui->lineEdit_outHex_Num1->setText("0x"+QString::number((long int)num1.numero, 16));

    ui->lineEdit_outIEEE_Num2->setText(num2S);
    ui->lineEdit_outHex_Num2->setText("0x"+QString::number((long int)num2.numero, 16));

}

void MainWindow::on_pushButton_Producto_clicked()
{
    ui->Denormal->hide();
    alu.infinito = false;
    alu.nan = false;
    alu.denormal = false;

    union Code num1;
    union Code num2;
    union Code res;
    QString num1S;
    QString num2S;

    float var1 = 0.0;
    float var2 = 0.0;

    var1 = ui->lineEdit_in_Num1->text().toFloat();
    var2 = ui->lineEdit_in_Num2->text().toFloat();

    num1.numero = var1;
    num2.numero = var2;
    res.numero = 0.0;

    num1S = printNum(num1);
    num2S = printNum(num2);

    ui->lineEdit_outIEEE_Num1->setText(num1S);
    ui->lineEdit_outIEEE_Num2->setText(num2S);

    res = alu.producto(num1, num2);

    if(alu.infinito == true)
    {
        ui->lineEdit_out_Resultado->setText("Infinito");

        ui->lineEdit_outIEEE_Resultado->setText("Infinito");

        ui->lineEdit_outHex_Resultado->setText("Infinito");
        alu.infinito = false;

    }else if(alu.nan == true){

        ui->lineEdit_out_Resultado->setText("NaN");

        ui->lineEdit_outIEEE_Resultado->setText("NaN");

        ui->lineEdit_outHex_Resultado->setText("NaN");
        alu.nan = false;

    }else if(alu.denormal == true){

        ui->Denormal->show();

        ui->lineEdit_out_Resultado->setText(QString::number(res.numero));

        ui->lineEdit_outIEEE_Resultado->setText(printNum(res));
        ui->lineEdit_outHex_Resultado->setText("0x"+QString::number((int)res.numero, 16));
        alu.denormal = false;
    }
    else
    {
        ui->lineEdit_out_Resultado->setText(QString::number(res.numero));
        ui->lineEdit_outIEEE_Resultado->setText(printNum(res));
        ui->lineEdit_outHex_Resultado->setText("0x"+QString::number((int)res.numero, 16));
    }

    ui->lineEdit_outIEEE_Num1->setText(num1S);
    ui->lineEdit_outHex_Num1->setText("0x"+QString::number((int)num1.numero, 16));
    ui->lineEdit_outIEEE_Num2->setText(num2S);
    ui->lineEdit_outHex_Num2->setText("0x"+QString::number((int)num2.numero, 16));

}



void MainWindow::on_pushButton_Division_clicked()
{
    ui->Denormal->hide();
    alu.infinito = false;
    alu.nan = false;
    alu.denormal = false;
    union Code num1;
    union Code num2;
    union Code res;
    QString num1S;
    QString num2S;

    float var1 = 0.0;
    float var2 = 0.0;

    var1 = ui->lineEdit_in_Num1->text().toFloat();
    var2 = ui->lineEdit_in_Num2->text().toFloat();

    num1.numero = var1;
    num2.numero = var2;
    res.numero = 0.0;

    num1S = printNum(num1);
    num2S = printNum(num2);

    ui->lineEdit_outIEEE_Num1->setText(num1S);
    ui->lineEdit_outIEEE_Num2->setText(num2S);

    res = alu.division(num1, num2);

    if(alu.infinito == true)
    {
        ui->lineEdit_out_Resultado->setText("Infinito");

        ui->lineEdit_outIEEE_Resultado->setText("Infinito");

        ui->lineEdit_outHex_Resultado->setText("Infinito");
        alu.infinito = false;

    }else if(alu.nan == true){

        ui->lineEdit_out_Resultado->setText("NaN");

        ui->lineEdit_outIEEE_Resultado->setText("NaN");

        ui->lineEdit_outHex_Resultado->setText("NaN");
        alu.nan = false;

    }else if(alu.denormal == true){

        ui->Denormal->show();


        ui->lineEdit_out_Resultado->setText(QString::number(res.numero));

        ui->lineEdit_outIEEE_Resultado->setText(printNum(res));
        ui->lineEdit_outHex_Resultado->setText("0x"+QString::number((int)res.numero, 16));
        alu.denormal = false;
    }
    else
    {


        ui->lineEdit_out_Resultado->setText(QString::number(res.numero));

        ui->lineEdit_outIEEE_Resultado->setText(printNum(res));
        ui->lineEdit_outHex_Resultado->setText("0x"+QString::number((int)res.numero, 16));


    }

    ui->lineEdit_outIEEE_Num1->setText(num1S);
    ui->lineEdit_outHex_Num1->setText("0x"+QString::number((int)num1.numero, 16));
    ui->lineEdit_outIEEE_Num2->setText(num2S);
    ui->lineEdit_outHex_Num2->setText("0x"+QString::number((int)num2.numero, 16));




}

QString MainWindow::printNum(union Code a)
{
    QString numIEEE;

    numIEEE = QString::number(a.IEEE754.signo);
    numIEEE = numIEEE + " ";

    for(int i = 7; i >= 0; i--)
    {
        numIEEE += QString::number(((a.IEEE754.expo >> i) & 1));
    }

    numIEEE = numIEEE + " ";

    for(int i = 22; i >= 0; i--)
    {
        numIEEE += QString::number(((a.IEEE754.partFrac >> i) & 1));
    }

    return numIEEE;
}

void MainWindow::on_pushButton_reset_clicked()
{
    ui->lineEdit_in_Num1->setText("");
    ui->Denormal->hide();
    ui->lineEdit_in_Num2->setText("");
    ui->lineEdit_outHex_Num1->setText("");
    ui->lineEdit_outHex_Num2->setText("");
    ui->lineEdit_out_Resultado->setText("");
    ui->lineEdit_outHex_Resultado->setText("");
    ui->lineEdit_outIEEE_Resultado->setText("");
    ui->lineEdit_outIEEE_Num1->setText("");
    ui->lineEdit_outIEEE_Num2->setText("");
}




