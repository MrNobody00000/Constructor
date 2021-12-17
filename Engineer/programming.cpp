#include "programming.h"
#include "greetingwindow.h"
#include "ui_programming2.h"


Programming::Programming(GreetingWindow *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    fromHead = parent;
    ui->setupUi(this);
    this->showMaximized();
    serial = new QSerialPort(this);

    //CheckComs1();
    //comNameChanged1(0);
}

Programming::~Programming()
{
    delete ui;
}



/*void Programming::comNameChanged1(int a)
{
    serial->close();
    serial->setPortName(ui->comNumber1->itemText(a));
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

}

void Programming::CheckComs1(){
ui->comNumber1->clear();
const auto infos = QSerialPortInfo::availablePorts();
for (const QSerialPortInfo &info:infos){
    QStringList list;
    list<< info.portName();
    ui->comNumber1->addItem(list.first());
}

}

void Programming::on_comNumber1_activated(int index)
{
    comNameChanged1(index);
}

void Programming::on_pushButton_3_clicked()
{
    serial->close();
}
*/
