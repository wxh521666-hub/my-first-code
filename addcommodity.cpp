#include "addcommodity.h"
#include "ui_addcommodity.h"

AddCommodity::AddCommodity(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddCommodity)
{
    ui->setupUi(this);
    ui->lineEdit_id->setFocus();
}

AddCommodity::~AddCommodity()
{
    delete ui;
}

void AddCommodity::on_pushButton_cancel_clicked()
{
    close();
}


void AddCommodity::on_pushButton_add_clicked()
{
    QSqlQuery sqlResult;
    QString strid,strname,strMount,strunitprice,strSupllier,strDirector,strInputTIME,stroutputtime,strRemark;
    strid = ui->lineEdit_id->text();
    strname = ui->lineEdit_name->text();
    strMount = ui->lineEdit_mount->text();
    strunitprice = ui->lineEdit_price->text();
    strSupllier = ui->lineEdit_Supplier->text();
    strDirector = ui->lineEdit_director->text();
    strRemark = ui->textEdit_beizhu->toPlainText();

    QDateTime datatime = QDateTime::currentDateTime();
    QString strnowinputtime = datatime.toString("yyyy-MM-dd HH:mm:ss");

    strInputTIME = strnowinputtime;
    stroutputtime = strnowinputtime;
    // QMessageBox::information(this,"测试",strid+strname+strRemark);

    if(ui->lineEdit_id->text().isEmpty())
    {
        QMessageBox::critical(this,"提示：：","编号不能为空 请重新输入 光标已定位至id");
        ui->lineEdit_id->setFocus();

    }

    QString sqlquery = QString("insert into commoditydata "
                                 "(StockId,StockName,StockMount,StockUnitPrice,Supplier,Director,WareHousetTime,DeliveTime,Remarks) "
                                 "values ('%1','%2','%3','%4','%5','%6','%7','%8','%9')")
                             .arg(strid).arg(strname).arg(strMount).arg(strunitprice).arg(strSupllier).arg(strDirector).arg(strInputTIME).arg(stroutputtime).arg(strRemark);


    if(sqlResult.exec(sqlquery))
    {
        QMessageBox::information(this,"提示","恭喜插入成功！！！");

    }
    else
    {
         QMessageBox::information(this,"提示","插入失败了");
    }
}

