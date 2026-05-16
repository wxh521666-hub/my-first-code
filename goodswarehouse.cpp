#include "goodswarehouse.h"
#include "ui_goodswarehouse.h"

GoodsWareHouse::GoodsWareHouse(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GoodsWareHouse)
{
    ui->setupUi(this);
    InitComboxFunc();
}

GoodsWareHouse::~GoodsWareHouse()
{
    delete ui;
}

void GoodsWareHouse::on_pushButton_warehouse_clicked()
{
    //获取编号
    QString StrwarId = ui->comboBox_Id->currentText();

    //判断入库数量是否为空
    if(ui->lineEdit_GoodsMount->text().isEmpty())
    {
        QMessageBox::critical(this,"提示","入库数量为空请重新输入");
        ui->lineEdit_GoodsMount->setFocus();
        return;
    }

    //查询当前编号的  然后更新
    StrwarId = "StockId="+StrwarId;
    QString str = QString("select *from commoditydata where %1").arg(StrwarId);
    // QMessageBox::information(this,"提示",str);
    QSqlQuery sqlquery;
    sqlquery.exec(str);
    QString strAmount;

    while(sqlquery.next())
    {
        strAmount = sqlquery.value(2).toString();
    }
    int inputAmount = ui->lineEdit_GoodsMount->text().toInt();
    int tanleAmount = strAmount.toInt();
    int isum = inputAmount + tanleAmount;

    QString strresult = QString::number(isum);

    QString strdb = QString("update commoditydata set StockMount=%1 where %2").arg(strresult).arg(StrwarId);

    if(sqlquery.exec(strdb))
    {
        QMessageBox::information(this,"提示","入库成功！！");
    }
    else
    {
        QMessageBox::information(this,"提示","入库失败");
    }
}


void GoodsWareHouse::on_pushButton_exit_clicked()
{
    close();
}
 void GoodsWareHouse::InitComboxFunc()
{
     int i = 0;
    QSqlQuery sqlQuery;
     sqlQuery.exec("select * from commoditydata");
    QString Strid;

     while(sqlQuery.next())
    {
        Strid = sqlQuery.value(0).toString();
         ui->comboBox_Id->insertItem(i,Strid);
        i++;
     }

}
