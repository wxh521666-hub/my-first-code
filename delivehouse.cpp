#include "delivehouse.h"
#include "ui_delivehouse.h"

DeliveHouse::DeliveHouse(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeliveHouse)
{
    ui->setupUi(this);
    InitComboxFunc();
}

DeliveHouse::~DeliveHouse()
{
    delete ui;
}

void DeliveHouse::on_pushButton_delive_clicked()
{
    //1 判断出库数量是否为空
    if(ui->lineEdit_ammount->text().isEmpty())
    {
        QMessageBox::information(this,"提示","出库不能为空请重新输入");
        ui->lineEdit_ammount->setFocus();
        return;
    }

    //2 获取商品编号
    QString strdelive_id = ui->comboBox_id->currentText();

    //3 查询
    QString strselect = QString("select * from commoditydata where StockId= %1").arg(strdelive_id);
    QSqlQuery sqlqueryselect;
    sqlqueryselect.exec(strselect);

    int house_mount = 0;
    if(sqlqueryselect.next())
    {
        house_mount = sqlqueryselect.value(2).toInt();
    }
    else
    {
        QMessageBox::warning(this,"错误","未找到该商品！");
        return;
    }

    //4 计算库存
    int delive_mount = ui->lineEdit_ammount->text().toInt();
    int mountlast = house_mount - delive_mount;

    if(mountlast < 0)
    {
        QMessageBox::critical(this,"错误","库存不足");
        return;
    }

    //5 更新数据库
    QString strUpdate = QString("update commoditydata set StockMount=%1 where StockId=%2")
                            .arg(mountlast).arg(strdelive_id);
    sqlqueryselect.exec(strUpdate);

    QMessageBox::information(this,"成功","出库完成！");

}

void DeliveHouse::on_pushButton_exit_clicked()
{
    close();
}

void DeliveHouse::InitComboxFunc()
{
    QSqlQuery sqlquery;
    QString strselect = QString("select * from commoditydata");
    QString strid;
    sqlquery.exec(strselect);
    int i = 0;
    while(sqlquery.next())
    {
        strid = sqlquery.value(0).toString();
        ui->comboBox_id->insertItem(i,strid);
        i++;
    }
}
