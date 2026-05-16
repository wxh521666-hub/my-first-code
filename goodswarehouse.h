#ifndef GOODSWAREHOUSE_H
#define GOODSWAREHOUSE_H

#include <QWidget>

//数据库相关头文件
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>


//商品入库  入库时间
//商品入库可以设计一个表来存储
namespace Ui {
class GoodsWareHouse;
}

class GoodsWareHouse : public QWidget
{
    Q_OBJECT

public:
    explicit GoodsWareHouse(QWidget *parent = nullptr);
    ~GoodsWareHouse();

private slots:
    void on_pushButton_warehouse_clicked();
    void on_pushButton_exit_clicked();

private:
    Ui::GoodsWareHouse *ui;

public:
    void InitComboxFunc();
};

#endif // GOODSWAREHOUSE_H
