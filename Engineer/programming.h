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

#include <vector>
#include <chrono>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class GreetingWindow;
class Programming : public QWidget
{
    Q_OBJECT
public:

    std::vector<int> RightAns;
    std::vector<int> SuggestedAns;
    int IconNum = 0;

    Programming(GreetingWindow *parent = 0);

    GreetingWindow *fromHead;

    QSerialPort     *serial;

    ~Programming();

private slots:
    void comNameChanged1(int);
    void CheckComs1();
    //void on_comNumber1_activated(int index);
    //void on_pushButton_3_clicked();

    //void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comBox_currentIndexChanged(int index);

    void on_Task1_clicked();

    void backClicked();

    void checkOutPage();

    void on_pushButton_3_clicked();

    //void setIm();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void sendRGB(std::string, int count);

    void pushIcon(int n);

    void on_Task2_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_13_clicked();

    void Temp(int first, int sec);

private:
   Ui::Form *ui;

};

#endif // PROGRAMMING_H
