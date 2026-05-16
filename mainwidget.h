#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>


//用到的数据库头文件
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QtDebug>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

public:
    void ConnectmysqlDbFunc();
    void TableWidgetListDataFunc();
    void TableWidgetFunc();  //初始化表格控件列的宽度
private slots:
    void on_pushButton_addGoods_clicked();
    void on_pushButton_DeleteGoods_clicked();
    void on_pushButton_GoodsWareHouse_clicked();
    void on_pushButton_GoodsDeliver_clicked();
    void on_pushButton_exportdata_clicked();
    void on_pushButton_DataSummary_clicked();
    void on_pushButton_DataSelect_clicked();
};
#endif // MAINWIDGET_H
