
#include "programming.h"
#include "Parser.h"
#include "greetingwindow.h"
//#include "ui_programming2.h"

#include "ui_form.h"



Programming::Programming(GreetingWindow *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    fromHead = parent;
    ui->setupUi(this);
    this->showMaximized();
    serial = new QSerialPort(this);
    connect(ui->comBox,SIGNAL(activated(int)),SLOT(comNameChanged1(int)));
    if(ui->stackedWidget->currentIndex() != 0){
        ui->stackedWidget->setCurrentIndex(0);

    }

    //CheckComs1();
    //comNameChanged1(0);
    //checkOutPage();
    //setIm();
}

Programming::~Programming()
{

    delete ui;
}




void Programming::comNameChanged1(int a)
{
    serial->close();
    serial->setPortName(ui->comBox->itemText(a));
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

}

void Programming::CheckComs1(){
ui->comBox->clear();
const auto infos = QSerialPortInfo::availablePorts();
for (const QSerialPortInfo &info:infos){
    QStringList list;
    list<< info.portName();
    ui->comBox->addItem(list.first());
}

}


void Programming::on_pushButton_2_clicked()
{
    serial->close();
}

/*void Programming::on_comBox_currentIndexChanged(int index)
{

    comNameChanged1(index);
}*/

void Programming::on_Task1_clicked()
{   ui->pushButton_7->setIcon(QPixmap(":/Icons/LampFire.png"));
    ui->pushButton_6->setIcon(QPixmap(":/Icons/LampDis2.png"));
    ui->pushButton_9->setIcon(QPixmap(":/Icons/Time.png"));

    ui->label_2->setPixmap(QPixmap(":/Icons/Strelka.png"));
    ui->label_4->setPixmap(QPixmap(":/Icons/StrelkaMini.png"));
    ui->label_6->setPixmap(QPixmap(":/Icons/StrelkaMini.png"));
    ui->label_8->setPixmap(QPixmap(":/Icons/StrelkaMini.png"));

    ui->label_2->setFixedSize(QSize(50,100));
    ui->label_4->setFixedSize(QSize(25,50));
    ui->label_6->setFixedSize(QSize(25,50));
    ui->label_8->setFixedSize(QSize(25,50));

    ui->pushButton_7->setIconSize(QSize(236,179));
    ui->pushButton_6->setIconSize(QSize(236,179));
    ui->pushButton_9->setIconSize(QSize(236,179));
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_3->setEnabled(1);

}

void Programming::on_Task2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->label_14->setPixmap(QPixmap(":/Icons/TrueFalse.png"));
    ui->label_17->setPixmap(QPixmap(":/Icons/EndTrueFalse.png"));
    ui->label_14->setFixedSize(QSize(400,200));
    ui->label_17->setFixedSize(QSize(400,200));
    ui->pushButton_16->setIcon(QPixmap(":/Icons/R.png"));
    ui->pushButton_15->setIcon(QPixmap(":/Icons/Green.png"));
    ui->pushButton_18->setIcon(QPixmap(":/Icons/B.png"));
    ui->pushButton_17->setIcon(QPixmap(":/Icons/Temp.png"));
    ui->pushButton_20->setIcon(QPixmap(":/Icons/More.png"));

    ui->pushButton_16->setIconSize(QSize(236,179));
    ui->pushButton_15->setIconSize(QSize(236,179));
    ui->pushButton_18->setIconSize(QSize(236,179));
    ui->pushButton_17->setIconSize(QSize(236,179));
    ui->pushButton_20->setIconSize(QSize(236,179));
    ui->pushButton_3->setEnabled(1);
    Programming::RightAns = {3,6};
}





void Programming::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_3->setEnabled(0);
}

void Programming::on_pushButton_7_clicked()
{
    Programming::SuggestedAns.push_back(1);
    pushIcon(1);
}

void Programming::on_pushButton_9_clicked()
{
    Programming::SuggestedAns.push_back(2);
    pushIcon(2);
}

void Programming::on_pushButton_6_clicked()
{
    Programming::SuggestedAns.push_back(3);
    pushIcon(3);
}

void Programming::on_pushButton_11_clicked()    //Clear on page Task 1
{
    ui->label_3->setPixmap(QPixmap());
    ui->label_5->setPixmap(QPixmap());
    ui->label_7->setPixmap(QPixmap());
    ui->label_9->setPixmap(QPixmap());
    Programming::IconNum=0;
    Programming::SuggestedAns.clear();
}


void Programming::on_pushButton_13_clicked()
{   bool wrongAns=0;
    if(Programming::SuggestedAns.empty())QMessageBox::information(0,"Ошибка","Заполни ячейки");
    else{
        for(int i=0;i<2;i++){
            if(Programming::RightAns[i] != Programming::SuggestedAns[i] || Programming::IconNum !=4){
                QMessageBox::information(0,"Ошибка","Неверно. Попробуй еще раз");
                ui->label_12->setPixmap(QPixmap());
                ui->label_13->setPixmap(QPixmap());
                ui->label_15->setPixmap(QPixmap());
                ui->label_16->setPixmap(QPixmap());
                Programming::IconNum=0;
                Programming::SuggestedAns.clear();
                serial->write("2,0,0,0");
                wrongAns=1;
                break;
            }
        }
        if(!serial->bytesAvailable()){
            QMessageBox::information(0,"Ошибка","Порт не подключен");
        }
        else if(!wrongAns){
            Temp(Programming::SuggestedAns[2],Programming::SuggestedAns[3],8);
        }
    }

}

void Programming::Temp(int first, int sec, int count){
    serial->write("6;0;");
    //serial->QSerialPort::waitForBytesWritten(-1);

    if (serial->bytesAvailable()/*(am & millis() - tmr >50) || am > 30*/){
       char str[30];
       int amount = serial->read(str,30);   // TERMINATOR = ';'
       str[amount] = NULL;

       Parser cata(str,',');
       cata.split();
       ui->TempValue->insert(cata[0]);
       if(atoi(cata[0]) > 25){
           switch(first){
           case(1):
               serial->write("2,0,254,0");
               serial->QSerialPort::waitForBytesWritten(-1);
               break;
           case(2):
               serial->write("2,254,0,0");
               serial->QSerialPort::waitForBytesWritten(-1);
               break;
           case(4):
               serial->write("2,0,0,254");
               serial->QSerialPort::waitForBytesWritten(-1);
               break;
           }
       }
       else{
           switch(sec){
           case(1):
               serial->write("2,0,254,0");
               serial->QSerialPort::waitForBytesWritten(-1);
               break;
           case(2):
               serial->write("2,254,0,0");
               serial->QSerialPort::waitForBytesWritten(-1);
               break;
           case(4):
               serial->write("2,0,0,254");
               serial->QSerialPort::waitForBytesWritten(-1);
               break;
           }
       }
    }
    auto time2 = std::chrono::system_clock::now();
    while(std::chrono::system_clock::now() - time2 < std::chrono::milliseconds(400) ){}
    count--;
    if(count > 0) Temp(first, sec, count);
    else if(count ==0) serial->write("2,0,0,0;");
}

void Programming::on_pushButton_10_clicked()
{
    bool ans1, ans2;
    if(Programming::SuggestedAns.empty()) QMessageBox::information(0,"Ошибка","Заполни ячейки");
    else {
    ans1 = ((Programming::SuggestedAns[0] == Programming::SuggestedAns[2]) && (Programming::SuggestedAns[1] != Programming::SuggestedAns[3])
            && (Programming::SuggestedAns[1] != 2) && (Programming::SuggestedAns[3] != 2));
    ans2 = ((Programming::SuggestedAns[1] == Programming::SuggestedAns[3]) && (Programming::SuggestedAns[0] != Programming::SuggestedAns[2])
            && (Programming::SuggestedAns[0] != 2) && (Programming::SuggestedAns[2] != 2));
    if(!(ans1 || ans2)){
        QMessageBox::information(0, "Ошибка", "Неверно. Попробуй еще раз");
        ui->label_3->setPixmap(QPixmap());
        ui->label_5->setPixmap(QPixmap());
        ui->label_7->setPixmap(QPixmap());
        ui->label_9->setPixmap(QPixmap());
        Programming::IconNum=0;
        Programming::SuggestedAns.clear();

    }
    else if(!serial->bytesAvailable()) QMessageBox::information(0,"Ошибка","Порт не подключен");
    else
    {
        sendRGB("2,244,244,244;",9);
    }
    }

}

void Programming::on_pushButton_12_clicked()
{
    Programming::CheckComs1();
}

void Programming::sendRGB(std::string data,int count){
    if(count==0){
        auto time2 = std::chrono::system_clock::now();
        while(std::chrono::system_clock::now() - time2 < std::chrono::milliseconds(1000) ){}
        serial->write(data.c_str());
        serial->QSerialPort::waitForBytesWritten(-1);
    }
    else{
        auto time2 = std::chrono::system_clock::now();
        while(std::chrono::system_clock::now() - time2 < std::chrono::milliseconds(1000) ){}
        serial->write(data.c_str());
        serial->QSerialPort::waitForBytesWritten(-1);

        if(data == "2,244,244,244;")
        {
            sendRGB("2,0,0,0;",count-1);
        }
        else sendRGB("2,244,244,244;",count-1);
    }
}

void Programming::pushIcon(int n){

    switch(ui->stackedWidget->currentIndex())
    {
    case(1):
        switch(n){
        case(1):
            switch(Programming::IconNum){
            case(0):
                ui->label_3->setPixmap(QPixmap(":/Icons/LampFireMini.png"));
                ui->label_3->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_5->setPixmap(QPixmap(":/Icons/LampFireMini.png"));
                ui->label_5->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;

            case(2):
                ui->label_7->setPixmap(QPixmap(":/Icons/LampFireMini.png"));
                ui->label_7->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_9->setPixmap(QPixmap(":/Icons/LampFireMini.png"));
                ui->label_9->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            }
            break;
        case(2):
            switch(Programming::IconNum){
            case(0):
                ui->label_3->setPixmap(QPixmap(":/Icons/TimeMini.png"));
                ui->label_3->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_5->setPixmap(QPixmap(":/Icons/TimeMini.png"));
                ui->label_5->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(2):
                ui->label_7->setPixmap(QPixmap(":/Icons/TimeMini.png"));
                ui->label_7->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_9->setPixmap(QPixmap(":/Icons/TimeMini.png"));
                ui->label_9->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            }
            break;
        case(3):
            switch(Programming::IconNum){
            case(0):
                ui->label_3->setPixmap(QPixmap(":/Icons/LampDisMini2.png"));
                ui->label_3->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_5->setPixmap(QPixmap(":/Icons/LampDisMini2.png"));
                ui->label_5->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(2):
                ui->label_7->setPixmap(QPixmap(":/Icons/LampDisMini2.png"));
                ui->label_7->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_9->setPixmap(QPixmap(":/Icons/LampDisMini2.png"));
                ui->label_9->setFixedSize(QSize(103,79));
                Programming::IconNum++;
                break;
            }
            break;

        }
            break;
    case(2):
        switch(n){
        case(1):
            switch(Programming::IconNum){
            case(0):
                ui->label_12->setPixmap(QPixmap(":/Icons/GreenMini.png"));
                ui->label_12->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_13->setPixmap(QPixmap(":/Icons/GreenMini.png"));
                ui->label_13->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;

            case(2):
                ui->label_15->setPixmap(QPixmap(":/Icons/GreenMini.png"));
                ui->label_15->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_16->setPixmap(QPixmap(":/Icons/GreenMini.png"));
                ui->label_16->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            }
            break;
        case(2):
            switch(Programming::IconNum){
            case(0):
                ui->label_12->setPixmap(QPixmap(":/Icons/RMini.png"));
                ui->label_12->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_13->setPixmap(QPixmap(":/Icons/RMini.png"));
                ui->label_13->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;

            case(2):
                ui->label_15->setPixmap(QPixmap(":/Icons/RMini.png"));
                ui->label_15->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_16->setPixmap(QPixmap(":/Icons/RMini.png"));
                ui->label_16->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            }
            break;
        case(3):
            switch(Programming::IconNum){
            case(0):
                ui->label_12->setPixmap(QPixmap(":/Icons/TempMini.png"));
                ui->label_12->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_13->setPixmap(QPixmap(":/Icons/TempMini.png"));
                ui->label_13->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;

            case(2):
                ui->label_15->setPixmap(QPixmap(":/Icons/TempMini.png"));
                ui->label_15->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_16->setPixmap(QPixmap(":/Icons/TempMini.png"));
                ui->label_16->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            }
            break;
        case(4):
            switch(Programming::IconNum){
            case(0):
                ui->label_12->setPixmap(QPixmap(":/Icons/BMini.png"));
                ui->label_12->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_13->setPixmap(QPixmap(":/Icons/BMini.png"));
                ui->label_13->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;

            case(2):
                ui->label_15->setPixmap(QPixmap(":/Icons/BMini.png"));
                ui->label_15->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_16->setPixmap(QPixmap(":/Icons/BMini.png"));
                ui->label_16->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            }
            break;

        case(6):
            switch(Programming::IconNum){
            case(0):
                ui->label_12->setPixmap(QPixmap(":/Icons/MoreMini.png"));
                ui->label_12->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(1):
                ui->label_13->setPixmap(QPixmap(":/Icons/MoreMini.png"));
                ui->label_13->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;

            case(2):
                ui->label_15->setPixmap(QPixmap(":/Icons/MoreMini.png"));
                ui->label_15->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            case(3):
                ui->label_16->setPixmap(QPixmap(":/Icons/MoreMini.png"));
                ui->label_16->setFixedSize(QSize(75,75));
                Programming::IconNum++;
                break;
            }
            break;

            }


    }
}

void Programming::on_pushButton_14_clicked()        //Clear on page Task_2
{
    ui->label_12->setPixmap(QPixmap());
    ui->label_13->setPixmap(QPixmap());
    ui->label_15->setPixmap(QPixmap());
    ui->label_16->setPixmap(QPixmap());
    Programming::IconNum=0;
    Programming::SuggestedAns.clear();
}



void Programming::on_pushButton_15_clicked()
{

    Programming::SuggestedAns.push_back(1);
    pushIcon(1);
}

void Programming::on_pushButton_16_clicked()
{

    Programming::SuggestedAns.push_back(2);
    pushIcon(2);

}

void Programming::on_pushButton_17_clicked()
{

    Programming::SuggestedAns.push_back(3);
    pushIcon(3);
}

void Programming::on_pushButton_18_clicked()
{

    Programming::SuggestedAns.push_back(4);
    pushIcon(4);
}

void Programming::on_pushButton_19_clicked()
{

    Programming::SuggestedAns.push_back(5);
    pushIcon(5);
}

void Programming::on_pushButton_20_clicked()
{

    Programming::SuggestedAns.push_back(6);
    pushIcon(6);
}


