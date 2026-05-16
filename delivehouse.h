#ifndef DELIVEHOUSE_H
#define DELIVEHOUSE_H

#include <QWidget>


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
namespace Ui {
class DeliveHouse;
}

class DeliveHouse : public QWidget
{
    Q_OBJECT

public:
    explicit DeliveHouse(QWidget *parent = nullptr);
    ~DeliveHouse();

private slots:
    void on_pushButton_delive_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::DeliveHouse *ui;
public:
    void InitComboxFunc();
};

#endif // DELIVEHOUSE_H
