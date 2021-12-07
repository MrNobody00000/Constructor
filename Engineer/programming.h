#ifndef PROGRAMMING_H
#define PROGRAMMING_H

#include <QWidget>
#include <QGridLayout>
#include <QtGui>
#include <QTreeWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class GreetingWindow;
class Programming : public QWidget
{
    Q_OBJECT
public:
    Programming(GreetingWindow *parent = 0);

    GreetingWindow *fromHead;

    QSerialPort     *serial;

    ~Programming();

private slots:
    //void comNameChanged1(int);
    //void CheckComs1();
    //void on_comNumber1_activated(int index);

   // void on_pushButton_3_clicked();

private:
   Ui::Form *ui;

};

#endif // PROGRAMMING_H
