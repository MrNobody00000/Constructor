#include "testing.h"
#include "greetingwindow.h"
#include "Parser.h"

QString com = "COM3";
Testing::Testing(GreetingWindow *parent) : QWidget(parent)
{
    fromHead = parent;
    serial = new QSerialPort(this);
    //create, layout and settings of testing widgets
    createWidgets();
    layoutWidgets();
    widgetSettings();
   // CheckComs();
    //comNameChanged(0);
    this->setLayout(testLayout);


    //connect to slots
    connect(getValuesButton,SIGNAL(clicked()),SLOT(getValuesButtonS()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readSerialPortS()));
    connect(comNumber,SIGNAL(activated(int)),SLOT(comNameChanged(int)));
    QObject::connect(sdControl, SIGNAL(sliderReleased()), SLOT(sdStart()));
    QObject::connect(ledColor,SIGNAL(clicked()),this,SLOT(clickedaction()));
    connect(getValuesButton,SIGNAL(clicked()),SLOT(Get()));
    connect(inCom,SIGNAL(clicked()),SLOT(CheckComs()));
    connect(breakBut,SIGNAL(clicked()),SLOT(breakConnect()));



}
void Testing::createWidgets()
{
    testLayout      = new QGridLayout;
    comNumber       = new QComboBox;
    getValuesButton = new QPushButton("Опросить");
    //Input vars
    inputBox = new QGroupBox;
    inputLayout = new QGridLayout;
    tempLabel   = new QLabel;
    tempValue   = new QLineEdit;
    tempCheck   = new QCheckBox;
    //dcLabel     = new QLabel;
    //dcValue     = new QLineEdit;
    //dcCheck     = new QCheckBox;
    //motioLabel  = new QLabel;
    //motioValue  = new QLineEdit;
    //motioCheck  = new QCheckBox;
    moistLabel  = new QLabel;
    moistValue  = new QLineEdit;
    moistCheck  = new QCheckBox;
   //voiceLabel  = new QLabel;
   // voiceValue  = new QLineEdit;
    //voiceCheck  = new QCheckBox;
    levelLabel  = new QLabel;
    levelValue  = new QLineEdit;
    levelCheck  = new QCheckBox;
    //Output vars
    outputBox       = new QGroupBox;
    outputLayout    = new QGridLayout;
    //pumpLabel   = new QLabel;
    //pumpSwitch  = new QPushButton;
    sdLabel     = new QLabel;
    //sdAngle     = new QPushButton("Отправить пакет");
    sdControl   = new QDial;
    ledLabel    = new QLabel;
    ledColor    = new QPushButton("Отправить пакет");
    RColor      = new QSlider(Qt::Horizontal, this);
    GColor      = new QSlider(Qt::Horizontal, this);
    BColor      = new QSlider(Qt::Horizontal, this);
    RLabel      = new QLabel("                              R");
    GLabel      = new QLabel("                              G");
    BLabel      = new QLabel("                              B");
    inCom    = new QPushButton("Find coms");
    breakBut = new QPushButton("Разорвать");

}
void Testing::layoutWidgets()
{
    testLayout->addWidget(inputBox,0,0);
    testLayout->addWidget(outputBox,1,0);

    inputBox->setLayout(inputLayout);
    inputLayout->addWidget(tempLabel,0,0);
    inputLayout->addWidget(tempValue,0,0,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(moistLabel,0,1);
    inputLayout->addWidget(moistValue,0,1,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(levelLabel,0,2);
    inputLayout->addWidget(levelValue,0,2,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(comNumber,1,2,Qt::AlignBottom | Qt::AlignCenter);

    inputLayout->addWidget(getValuesButton,1,2,Qt::AlignRight);

    outputBox->setLayout(outputLayout);
    outputLayout->addWidget(sdLabel,0,1);
    outputLayout->addWidget(sdControl,2,1,Qt::AlignBottom | Qt::AlignCenter);
    outputLayout->addWidget(ledLabel,0,2);
    outputLayout->addWidget(ledColor,1,2,Qt::AlignBottom | Qt::AlignRight);
    outputLayout->addWidget(RColor,1,2,Qt::AlignCenter | Qt::AlignCenter);
    outputLayout->addWidget(GColor,2,2,Qt::AlignCenter | Qt::AlignCenter);
    outputLayout->addWidget(BColor,3,2,Qt::AlignCenter | Qt::AlignCenter);
    outputLayout->addWidget(RLabel,1,2,Qt::AlignCenter | Qt::AlignLeft);
    outputLayout->addWidget(GLabel,2,2,Qt::AlignCenter | Qt::AlignLeft);
    outputLayout->addWidget(BLabel,3,2,Qt::AlignCenter | Qt::AlignLeft);
    inputLayout->addWidget(inCom,1,2,Qt::AlignBottom | Qt::AlignLeft);
    inputLayout->addWidget(breakBut,1,2,Qt::AlignBottom | Qt::AlignLeft);


}
void Testing::widgetSettings()
{
    //serial->setPortName(comNumber->text());
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

    QFont font;
    font.setPixelSize(15);
    inputBox->setFont(font);
    outputBox->setFont(font);
    inputBox->setTitle("Датчики");
    outputBox->setTitle("Исполнительные механизмы");
    inputBox->setAlignment(Qt::AlignCenter);
    outputBox->setAlignment(Qt::AlignCenter);

    tempLabel->setAlignment(Qt::AlignCenter);
    moistLabel->setAlignment(Qt::AlignCenter);
    levelLabel->setAlignment(Qt::AlignCenter);

    sdLabel->setAlignment(Qt::AlignCenter);
    ledLabel->setAlignment(Qt::AlignCenter);

    tempValue->setReadOnly(true);
    moistValue->setReadOnly(true);
    levelValue->setReadOnly(true);

    tempValue->setFixedWidth(100);
    moistValue->setFixedWidth(100);
    levelValue->setFixedWidth(100);

    sdControl->setRange(0,180);


    RColor->setRange(0, 255);
    RColor->setFixedWidth(200);


    GColor->setRange(0, 255);
    GColor->setFixedWidth(200);


    BColor->setRange(0, 255);
    BColor->setFixedWidth(200);


    QSize size = qApp->screens()[0]->size();
    tempLabel->setPixmap(QPixmap(":/Icons/tempL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    moistLabel->setPixmap(QPixmap(":/Icons/moistL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    levelLabel->setPixmap(QPixmap(":/Icons/levelL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));

    sdLabel->setPixmap(QPixmap(":/Icons/sdL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ledLabel->setPixmap(QPixmap(":/Icons/ledL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
void Testing::comNameChanged(int a)
{
    serial->close();
    serial->setPortName(comNumber->itemText(a));
    serial->setBaudRate(9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setStopBits(QSerialPort::OneStop);
    serial->open(QIODevice::ReadWrite);

}
void Testing::getValuesButtonS()
{

   // serial->write(char'');
}
void Testing::readSerialPortS()
{
  /*  if(fromHead->mainStack->currentWidget()==fromHead->testWindow)
    {

    }*/
}
void Testing::sdStart()
{
    if(serial->bytesAvailable()){
    int i=0;
    char str[30];
    std::string data = {"1,"+std::to_string(sdControl->value())+';'};
    while (data[i] != ';') {
            str[i] = data[i];
            i++;

        }
    str[i] = data[i];
    serial->write(str);
    }
    else QMessageBox::information(0,"Ошибка","Порт не подключен");
}

void Testing::Get(){
    if(serial->bytesAvailable()){
    serial->setPortName(comNumber->currentText());
    tempValue->clear();
    moistValue->clear();
    levelValue->clear();
    QString data[4];
    //int counter = 0;
    //char getData[30];
    //int i=0;

    //char str[] ={'6',';'};
    serial->write("6;0;");
    serial->waitForReadyRead(1500);

    if (serial->bytesAvailable()/*(am & millis() - tmr >50) || am > 30*/){
       char str[30];
       int amount = serial->read(str,30);   // TERMINATOR = ';'
       str[amount] = NULL;

       Parser cata(str,',');
       int am = cata.split();
       for (int i =0; i<am;i++) data[i] = (cata[i]);
       for (int i=0;i<30;i++) str[i] = ' ';
    }

    tempValue->insert(data[0]);
    levelValue->insert(data[1]);
    moistValue->insert(data[2]);
    data[0].clear();
    data[1].clear();
    data[2].clear();
    data[3].clear();

    }
    else QMessageBox::information(0,"Ошибка","Порт не подключен");
}


void Testing::clickedaction(){
    if(serial->bytesAvailable()){
    int i=0;
    char str[30];
    std::string data = {"2,"+std::to_string(RColor->value())+','+std::to_string(GColor->value())+','+std::to_string(BColor->value())+';'};
    while (data[i] != ';') {
            str[i] = data[i];
            i++;

        }
    str[i] = data[i];
    serial->write(str);
    }
    else QMessageBox::information(0,"Ошибка","Порт не подключен");
}

void Testing::CheckComs(){
comNumber->clear();
const auto infos = QSerialPortInfo::availablePorts();
for (const QSerialPortInfo &info:infos){
    QStringList list;
    list<< info.portName();
    comNumber->addItem(list.first());
}

}

void Testing::breakConnect(){
    serial->close();
}
