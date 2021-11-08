#include "programming.h"
#include "greetingwindow.h"
#include "ui_programming.h"



QTreeWidgetItem *child11 = new QTreeWidgetItem();
QTreeWidgetItem *child12 = new QTreeWidgetItem();
QTreeWidgetItem *child13 = new QTreeWidgetItem();
QTreeWidgetItem *child14 = new QTreeWidgetItem();

QTreeWidgetItem *child21 = new QTreeWidgetItem();
QTreeWidgetItem *child22 = new QTreeWidgetItem();

QTreeWidgetItem *child31 = new QTreeWidgetItem();
QTreeWidgetItem *child32 = new QTreeWidgetItem();
QTreeWidgetItem *child33 = new QTreeWidgetItem();

QTreeWidgetItem *child411 = new QTreeWidgetItem();
QTreeWidgetItem *child412 = new QTreeWidgetItem();
QTreeWidgetItem *child413 = new QTreeWidgetItem();
QTreeWidgetItem *child42 = new QTreeWidgetItem();
QTreeWidgetItem *child43 = new QTreeWidgetItem();
QTreeWidgetItem *child44 = new QTreeWidgetItem();
QTreeWidgetItem *child45 = new QTreeWidgetItem();
QTreeWidgetItem *child46 = new QTreeWidgetItem();

QTreeWidgetItem *child51 = new QTreeWidgetItem();
QTreeWidgetItem *child52 = new QTreeWidgetItem();
QTreeWidgetItem *child53 = new QTreeWidgetItem();

QTreeWidgetItem *child311 = new QTreeWidgetItem();
QTreeWidgetItem *child312 = new QTreeWidgetItem();


QTreeWidgetItem *child321 = new QTreeWidgetItem();

QTreeWidgetItem *child331 = new QTreeWidgetItem();
QTreeWidgetItem *child332 = new QTreeWidgetItem();
QTreeWidgetItem *child333 = new QTreeWidgetItem();

QTreeWidgetItem *child34 = new QTreeWidgetItem();

std::vector<std::string> command;
int millis;

QString servoObject;
QString rgbObject;
QString tempObject;

bool libraryFlagrgb=0;
bool libraryFlagServo=0;
bool libraryFlagTemp=0;

bool pinFlagrgb=0;
bool pinFlagServo=0;
bool pinFlagTemp=0;
bool stop=0;





Programming::Programming(GreetingWindow *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    fromHead = parent;
    ui->setupUi(this);
    serial = new QSerialPort(this);

    CheckComs1();
    //comNameChanged1(0);
    ui->treeWidget->clear();

    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0,"Циклы");

    child11->setText(0,"Сделать N раз");
    child12->setText(0,"Делать пока (true)");
    child13->setText(0,"Делать { } пока (true)");
    child14->setText(0,"Закрыть тело цикла");
    QList <QTreeWidgetItem*> children1{child11,child12,child13,child14};
    itm->addChildren(children1);

    QTreeWidgetItem *itm1 = new QTreeWidgetItem();
    itm1->setText(0,"Условие");

    child21->setText(0,"Сделать если (true)");
    child22->setText(0,"Закрыть тело условия");
    itm1->addChild(child21);
    itm1->addChild(child22);

    QTreeWidgetItem *itm2 = new QTreeWidgetItem();
    itm2->setText(0,"Действия");
    QTreeWidgetItem *child31 = new QTreeWidgetItem();
    QTreeWidgetItem *child32 = new QTreeWidgetItem();
    QTreeWidgetItem *child33 = new QTreeWidgetItem();
    child31->setText(0,"Светодиод");
    child32->setText(0,"Сервопривод");
    child33->setText(0,"Получить значения с датчика");
    QList <QTreeWidgetItem*> children3{child31,child32,child33};
    itm2->addChildren(children3);
    child311->setText(0,"Включить");
    child312->setText(0,"Выключить");
    child31->addChild(child311);
    child31->addChild(child312);
    child321->setText(0,"Повернуть на N градусов");
    child32->addChild(child321);
    child331->setText(0,"Температура");
    child332->setText(0,"Влажность");
    child333->setText(0,"Уровень жидкости");
    QList <QTreeWidgetItem*> children4{child331,child332,child333};
    child33->addChildren(children4);
    child34->setText(0,"Ждать N миллисекунд");
    itm2->addChild(child34);




    QTreeWidgetItem *itm3 = new QTreeWidgetItem();
    itm3->setText(0,"Подключить");
    QTreeWidgetItem *child41 = new QTreeWidgetItem();
    child41->setText(0,"Добавить библиотеку");
    child411->setText(0,"Добавить библиотеку для сервопривода");
    child412->setText(0,"Добавить библиотеку для датчика температуры");
    child413->setText(0,"Добавить библиотеку для RGB ленты");
    child42->setText(0,"Задать пин RGB ленты");
    child43->setText(0,"Задать пин сервопривода");
    child44->setText(0,"Задать пин датчика температуры");
    child45->setText(0,"Задать пин датчика влажности + инициализировать");
    itm3->addChild(child41);
    QList <QTreeWidgetItem*> children41{child411,child412,child413};
    child41->addChildren(children41);
    itm3->addChild(child42);
    itm3->addChild(child43);
    itm3->addChild(child44);
    itm3->addChild(child45);

    QTreeWidgetItem *itm4 = new QTreeWidgetItem();
    itm4->setText(0,"Object");
    child51->setText(0,"Создать объект класса (RGB) + инициализировать");
    child52->setText(0,"Создать объект класса (Servo) + инициализировать");
    child53->setText(0,"Создать объект класса (Temp) + инициализировать");
    itm4->addChild(child51);
    itm4->addChild(child52);


    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->addTopLevelItem(itm);
    ui->treeWidget->addTopLevelItem(itm1);
    ui->treeWidget->addTopLevelItem(itm2);
    ui->treeWidget->addTopLevelItem(itm3);
    ui->treeWidget->addTopLevelItem(itm4);



}

Programming::~Programming()
{
    delete ui;
}



void Programming::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{    QMessageBox msg;
     if (item == child11){
         bool ok;
            /*int text = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                                 tr("N:"), 0,0,500,1, &ok);*/
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("N:"), QLineEdit::Normal,
                                                 "", &ok);
            if (ok && text !=0)
                {ui->textBrowser_3->append("for(int i=0;i<"+text+";i++)\n{");
                //command.push_back(text.toInt());}

    }
     }
     if (item == child12){
         bool ok;

         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Условие:"), QLineEdit::Normal,
                                                 "", &ok);
            if (ok && text !=0)
                {ui->textBrowser_3->append("while("+text+")\n{");
                //command.push_back(text.toInt());
            }
    }
     if (item == child13){
         // пока не ясно, как использовать
     }
     if (item == child14){

         ui->textBrowser_3->append("\n}");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);

     }
     if (item == child21){
         bool ok;

         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Условие:"), QLineEdit::Normal,
                                                 "", &ok);
            if (ok && text !=0)
                {ui->textBrowser_3->append("if("+text+")\n{");
                //command.push_back(text.toInt());
            }
    }
     if (item == child22){

         ui->textBrowser_3->append("\n}");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);

     }
     if (item == child311){
         QMessageBox msg;
         if (rgbObject.isEmpty()){
             msg.setText("Сначала создай объект класса");
             if(!libraryFlagrgb)msg.setText("Сначала создай объект класса и добавь библиотеку");
             msg.exec();
         }
         else if(!libraryFlagrgb){msg.setText("Cначала добавь библиотеку");
             msg.exec();}
         else{
         ui->textBrowser_3->append("\n(int i = 0; i < LED_COUNT; i++)\n{\n"+rgbObject+".setPixelColor(i, "+rgbObject+".Color(255,0,0));\n}\n"+rgbObject+".show();");
         command.push_back("2,255,0,0;");
         }

     }
     if (item == child312){

         QMessageBox msg;
         if (rgbObject.isEmpty()){
             msg.setText("Сначала создай объект класса");
             if(!libraryFlagrgb)msg.setText("Сначала создай объект класса и добавь библиотеку");
             msg.exec();
         }
         else if(!libraryFlagrgb){msg.setText("Cначала добавь библиотеку");
             msg.exec();}
         else{
         ui->textBrowser_3->append("\n(int i = 0; i < LED_COUNT; i++)\n{\n"+rgbObject+".setPixelColor(i, "+rgbObject+".Color(0,0,0));\n}\n"+rgbObject+".show();");
         command.push_back("2,0,0,0;");
         }

     }
     if (item == child321){
         QMessageBox msg;
         if (servoObject.isEmpty()){
             msg.setText("Сначала создай объект класса");
             if(!libraryFlagServo)msg.setText("Сначала создай объект класса и добавь библиотеку");
             msg.exec();
         }
         else if(!libraryFlagServo){msg.setText("Cначала добавь библиотеку");
             msg.exec();}
         else{
         bool ok;
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("N:"), QLineEdit::Normal,
                                                 "", &ok);
         ui->textBrowser_3->append("\n"+servoObject+".write("+text+");");
         command.push_back("1,");
         command.push_back(text.toStdString());
         command.push_back(";");

        }
     }
     if (item == child34){

         bool ok;
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("N:"), QLineEdit::Normal,
                                                 "", &ok);
         ui->textBrowser_3->append("\ndelay("+text+");");
         command.push_back("7,");
         command.push_back(text.toStdString());
         command.push_back(";");

     }
     if (item == child411){
         libraryFlagServo=1;
         ui->textBrowser->append("\n#include <Servo.h>");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);

     }
     if (item == child412){
         libraryFlagTemp=1;
         ui->textBrowser->append("\n#include <OneWire.h>\n#include <DallasTemperature.h>");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);

     }
     if (item == child413){
         libraryFlagrgb=1;
         ui->textBrowser->append("\n#include ''Adafruit_NeoPixel.h''");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);

     }
     if (item == child42){

         QMessageBox msg;
         if(!libraryFlagrgb){msg.setText("Cначала добавь библиотеку");
             msg.exec();}
         else{
         pinFlagrgb=1;
         bool ok;
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Пин:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\n#define LED_COUNT 2\n#define LED_PIN "+text);
         //ui->textBrowser_2->append("\n"+rgbObject+".begin();");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);
         }

     }
     if (item == child43){
         QMessageBox msg;
         if(!libraryFlagServo){msg.setText("Cначала добавь библиотеку");
             msg.exec();}
         else{
         pinFlagServo=1;
         bool ok;
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Пин:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\n#define servoPin "+text);
        // ui->textBrowser_2->append("\n"+servoObject+".attach(servoPin);");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);
         }

     }
     if (item == child44){
        QMessageBox msg;
        if(!libraryFlagTemp){msg.setText("Сначала добавь библиотеку");
        msg.exec();}
        else{
            pinFlagTemp=1;
           //  bool kk;
           //  QString tempObject = QInputDialog::getText(this, tr("QInputDialog::getText()"),
           //                                          tr("Имя объкта класса:"), QLineEdit::Normal,
           //                                          " ", &kk);
         bool ok;
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Пин:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\n#define TPin "+text+"\n#define sensorPower 2");
         //ui->textBrowser_2->append("\n"+tempObject+".begin();\npinMode(TPin,INPUT);");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);
        }

     }
     if (item == child45){

         bool ok;
         QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Пин:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\n#define MSPin "+text+"\nint MSValue=0;");
         //ui->textBrowser_2->append("\n"+tempObject+".begin();");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);

     }


     if (item == child51){
         QMessageBox msg;
         if(!pinFlagrgb){
             msg.setText("Сначала задай пин");
             msg.exec();
         }
         else{
         bool ok;
         rgbObject = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Имя объекта:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\nAdafruit_NeoPixel "+rgbObject+"= Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);");
         ui->textBrowser_2->append("\n"+rgbObject+".begin();");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);
         }

     }
     if (item == child52){
         QMessageBox msg;
         if(!pinFlagServo){
             msg.setText("Сначала задай пин");
             msg.exec();
         }
         else{
         bool ok;
         servoObject = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Имя объекта:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\nServo "+servoObject+";");
         ui->textBrowser_2->append("\n"+servoObject+".attach(servoPin);");
         //command.push_back(/*номер команды для послед сравнения с эталоном */0);
         }

     }

     if (item == child53){
         QMessageBox msg;
         if(!pinFlagTemp){
             msg.setText("Сначала задай пин");
             msg.exec();
         }
         else{
         bool ok;
         tempObject = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Имя объекта:"), QLineEdit::Normal,
                                                 " ", &ok);
         ui->textBrowser->append("\nOneWire TempValue(TPin);\nDallasTemperature "+tempObject+"(&TempValue);");
         ui->textBrowser_2->append("\n"+tempObject+".begin();\npinMode(TPin,INPUT);");

         //command.push_back(/*номер команды для послед сравнения с эталоном */0);
         }

     }

}




void Programming::on_pushButton_2_clicked()
{
    stop=1;
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
    ui->textBrowser_3->clear();
    ui->textBrowser->append("#include <stdio.h>\n");
    ui->textBrowser_2->append("Serial.begin(9600);\n");
     libraryFlagrgb=0;
     libraryFlagServo=0;
     libraryFlagTemp=0;

     pinFlagrgb=0;
     pinFlagServo=0;
     pinFlagTemp=0;

     tempObject="";
     rgbObject="";
     servoObject="";
     command.clear();

}

void Programming::on_pushButton_clicked()
{
    for(int h=0;h<40;h++){
    int i=0;
    std::string data{};
    char str[30];
    char str1[30];
    char str2[30];
    for(int c=0;c<command.size();c++){
    data.append(command[c]);

    }
    while (data[i] != ';') {
            str[i] = data[i];
            i++;

        }
    str[i] = data[i];
    data.erase(0,i+1);
    //ui->textEdit->append(QString::fromUtf8(data.data(), int(data.size())));
    i=0;
    while (data[i] != ';') {
            str1[i] = data[i];
            i++;

        }
    str1[i] = data[i];
    data.erase(0,i+1);
   // ui->textEdit->append(QString::fromUtf8(data.data(), int(data.size())));
    i=0;
    while (data[i] != ';') {
            str2[i] = data[i];
            i++;

        }
    str2[i] = data[i];
    data.erase(0,i+1);
    //ui->textEdit->append(QString::fromUtf8(data.data(), int(data.size())));
    serial->write(str);
    QEventLoop loop;

        QTimer::singleShot(500, &loop, &QEventLoop::quit);

        loop.exec();
    serial->write(str1);
    //Sleep(10);
    serial->write(str2);
     ui->textEdit->append(str);
    ui->textEdit->append(str1);
     ui->textEdit->append(str2);
    //command.clear();
    }
}

void Programming::comNameChanged1(int a)
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
