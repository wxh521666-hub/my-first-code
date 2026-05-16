#ifndef ADDCOMMODITY_H
#define ADDCOMMODITY_H

#include <QWidget>


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QDateTime>
#include <QMessageBox>
namespace Ui {
class AddCommodity;
}

class AddCommodity : public QWidget
{
    Q_OBJECT

public:
    explicit AddCommodity(QWidget *parent = nullptr);
    ~AddCommodity();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::AddCommodity *ui;
};

#endif // ADDCOMMODITY_H
