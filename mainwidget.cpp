#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ConnectmysqlDbFunc();//连接MYSQL数据库
    //禁止用户拖拉窗口改变大小
    setFixedSize(this->width(),this->height());

    TableWidgetListDataFunc();
    TableWidgetFunc();

    // on_pushButton_DataSelect_clicked();  //查询函数     没必要在构造函数加这个  点击那个按钮会自动调用函数
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::ConnectmysqlDbFunc()  //连接MySQL数据库函数
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");   //控制面板ODBC数据源保持一致
    db.setPort(3306); //此端口号为数据库安装时设定的端口
    db.setDatabaseName("stockmsdb");//ODBC数据源配置的名称
    db.setPassword("124627wang");//安装mysql时设置的密码

    bool bok = db.open();

    if(!bok)
    {
        QMessageBox::information(this,"提示","mysql数据库连接失败");

    }

}
//表格控件初始化操作
void MainWidget::TableWidgetListDataFunc()
{
    //编号 名称 数量 单价 供应商家 负责人 入库时间 出库时间 备注
    //设置表格控件   200行 9列

    ui->tableWidget_listdata->setColumnCount(9);
    ui->tableWidget_listdata->setRowCount(200);


    //设置表格控件字体大小
    ui->tableWidget_listdata->setFont(QFont("宋体",13));
    //设置表头
    ui->tableWidget_listdata->setHorizontalHeaderLabels
        (QStringList()<<"编号"<<"名称"<<"数量"<<"单价"<<"供应商家"<<"负责人"<<"入库时间"<<"出库时间"<<"备注");


    QSqlQuery sqlquery;
    //sql查询语句
    QString str= QString("select * from commoditydata");
    sqlquery.exec(str);  //执行 SQL 语句的核心方法
    int i = 0;
    while(sqlquery.next())
    {
        QString strid = sqlquery.value(0).toString();
        QString name = sqlquery.value(1).toString();
        QString mount = sqlquery.value(2).toString();
        QString price = sqlquery.value(3).toString();
        QString supplier = sqlquery.value(4).toString();
        QString derector = sqlquery.value(5).toString();
        QString warehousetime = sqlquery.value(6).toString();
        QString delivetime = sqlquery.value(7).toString();
        QString remarks = sqlquery.value(8).toString();

        //将字符串显示到表格空间中
        ui->tableWidget_listdata->setItem(i,0,new QTableWidgetItem(strid));
        ui->tableWidget_listdata->setItem(i,1,new QTableWidgetItem(name));
        ui->tableWidget_listdata->setItem(i,2,new QTableWidgetItem(mount));
        ui->tableWidget_listdata->setItem(i,3,new QTableWidgetItem(price));
        ui->tableWidget_listdata->setItem(i,4,new QTableWidgetItem(supplier));
        ui->tableWidget_listdata->setItem(i,5,new QTableWidgetItem(derector));
        ui->tableWidget_listdata->setItem(i,6,new QTableWidgetItem(warehousetime));
        ui->tableWidget_listdata->setItem(i,7,new QTableWidgetItem(delivetime));
        ui->tableWidget_listdata->setItem(i,8,new QTableWidgetItem(remarks));
        i++;
    }
}

//初始化表格控件列的宽度
void MainWidget::TableWidgetFunc()
{
    ui->tableWidget_listdata->setColumnWidth(0,80);
    ui->tableWidget_listdata->setColumnWidth(1,100);
    ui->tableWidget_listdata->setColumnWidth(2,80);
    ui->tableWidget_listdata->setColumnWidth(3,80);
    ui->tableWidget_listdata->setColumnWidth(4,120);
    ui->tableWidget_listdata->setColumnWidth(5,100);
    ui->tableWidget_listdata->setColumnWidth(6,250);
    ui->tableWidget_listdata->setColumnWidth(7,250);
    ui->tableWidget_listdata->setColumnWidth(8,80);

}
//调用新增商品的对话框
#include "addcommodity.h"

void MainWidget::on_pushButton_addGoods_clicked()
{
    //两行代码实现点击跳转
    AddCommodity *addlg = new AddCommodity;
    addlg->setFixedSize(this->width(),this->height());
    addlg->show();


}

//删除商品
void MainWidget::on_pushButton_DeleteGoods_clicked()
{
  //1 首先提醒用户是否确认删除此记录
    int iclick = QMessageBox::warning(this,"警告","删除操作是根据用户编号来删除的，请确认是否安全",QMessageBox::Yes|QMessageBox::No);

//2 判断用户是否点击 yes
    if(iclick == QMessageBox::Yes)
    {
        //3 获取当前选择进行删除商品数据
        int iRow = ui->tableWidget_listdata->currentRow();

        //4 根据索引 获取对应商品的编号
        QString strvalue = ui->tableWidget_listdata->model()->index(iRow,0).data().toString();
        QMessageBox::information(this,"提示","获取数据为Stockkid="+strvalue);

        QSqlQuery sqlquery;
        QString strdelete = QString("DELETE FROM commoditydata WHERE StockId = %1").arg(strvalue);

        //5判断删除数据是否为空
        if(strvalue=="")
        {
            QMessageBox::information(this,"提示","删除数据为空");
        }
        //6 进行删除 数据库sql语句
        sqlquery.exec(strdelete);

        if(sqlquery.exec(strdelete))
        {
            QMessageBox::information(this,"提示","删除成功");

        }
        else
        {
            QMessageBox::information(this,"提示","删除失败");
        }

    }

    else
    {
        return;
    }






}


//商品入库
#include "goodswarehouse.h"
void MainWidget::on_pushButton_GoodsWareHouse_clicked()
{
    GoodsWareHouse *gwdlg = new GoodsWareHouse;

    gwdlg->setFixedSize(this->width(),this->height());
    gwdlg->show();
}

//商品出库
#include "delivehouse.h"
void MainWidget::on_pushButton_GoodsDeliver_clicked()
{
    DeliveHouse *deldlg = new DeliveHouse;
    deldlg->setFixedSize(this->width(),this->height());
    deldlg->show();
}


//导出数据
#include <QFileDialog>
#include <QAxObject>
#include <QDesktopServices>
#include <QDir> // 必须加这个
#include <QMessageBox>

void MainWidget::on_pushButton_exportdata_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString strtmp = time.toString("yyyy--MM--dd hh-mm-ss");
    QMessageBox::information(this,"测试",strtmp);

    QString strsaveneme = strtmp+"_kcgl";
    QString strFileName = QFileDialog::getSaveFileName(this,
                                                       "保存Excel文件",
                                                       strsaveneme+".xls",
                                                       "Excel文件 (*.xls)");

    if(!strFileName.isEmpty())
    {
        QAxObject *excel = new QAxObject;

        if(excel->setControl("Excel.Application"))
        {
            excel->dynamicCall("SetVisible(bool)", false);
            excel->setProperty("DisplayAlerts", false);

            QAxObject *workbooks = excel->querySubObject("WorkBooks");
            workbooks->dynamicCall("Add");
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
            QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

            QAxObject *cell;

            // 写入表头
            for(int i=1; i<=ui->tableWidget_listdata->columnCount(); i++)
            {
                cell = worksheet->querySubObject("Cells(int,int)", 1, i);
                cell->setProperty("RowHeight", 38);
                cell->dynamicCall("SetValue(const QString&)",
                                  ui->tableWidget_listdata->horizontalHeaderItem(i-1)->text());
            }

            // 写入数据（安全版！不会崩溃！）
            int rowCount = ui->tableWidget_listdata->rowCount();
            for(int j=2; j<=rowCount+1; j++)
            {
                for(int k=1; k<=ui->tableWidget_listdata->columnCount(); k++)
                {
                    // 【关键修复】空单元格判断，防止崩溃！
                    QTableWidgetItem *item = ui->tableWidget_listdata->item(j-2, k-1);
                    QString text = item ? item->text() : "";

                    cell = worksheet->querySubObject("Cells(int,int)", j, k);
                    cell->dynamicCall("SetValue(const QString&)", text);
                }
            }

            // 保存
            workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(strFileName));
            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");
            delete excel;

            // 导出成功提示
            QMessageBox::information(this,"成功","Excel 已保存到：\n" + strFileName);
        }
        else
        {
            QMessageBox::warning(this,"错误","未安装 Microsoft Excel！");
        }
    }
}


void MainWidget::on_pushButton_DataSummary_clicked()
{

}




void MainWidget::on_pushButton_DataSelect_clicked()
{

    TableWidgetListDataFunc();

ui->tableWidget_listdata->clearContents();

    QSqlQuery sqlquery;
    QString strid = "StockId=";
    strid = strid+ui->lineEdit_GoodsNumber->text();

    //sql查询语句
    QString str= QString("select * from commoditydata where %1").arg(strid);// 占位符
    sqlquery.exec(str);  //执行 SQL 语句的核心方法
    int i = 0;
    while(sqlquery.next())
    {
        QString strid = sqlquery.value(0).toString();
        QString name = sqlquery.value(1).toString();
        QString mount = sqlquery.value(2).toString();
        QString price = sqlquery.value(3).toString();
        QString supplier = sqlquery.value(4).toString();
        QString derector = sqlquery.value(5).toString();
        QString warehousetime = sqlquery.value(6).toString();
        QString delivetime = sqlquery.value(7).toString();
        QString remarks = sqlquery.value(8).toString();

        //测试字符串
        QMessageBox::information(this,"测试",strid+name);
        //将字符串显示到表格空间中
        ui->tableWidget_listdata->setItem(i,0,new QTableWidgetItem(strid));
        ui->tableWidget_listdata->setItem(i,1,new QTableWidgetItem(name));
        ui->tableWidget_listdata->setItem(i,2,new QTableWidgetItem(mount));
        ui->tableWidget_listdata->setItem(i,3,new QTableWidgetItem(price));
        ui->tableWidget_listdata->setItem(i,4,new QTableWidgetItem(supplier));
        ui->tableWidget_listdata->setItem(i,5,new QTableWidgetItem(derector));
        ui->tableWidget_listdata->setItem(i,6,new QTableWidgetItem(warehousetime));
        ui->tableWidget_listdata->setItem(i,7,new QTableWidgetItem(delivetime));
        ui->tableWidget_listdata->setItem(i,8,new QTableWidgetItem(remarks));
    }










}

