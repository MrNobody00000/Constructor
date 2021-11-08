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
    dcLabel     = new QLabel;
    dcValue     = new QLineEdit;
    dcCheck     = new QCheckBox;
    motioLabel  = new QLabel;
    motioValue  = new QLineEdit;
    motioCheck  = new QCheckBox;
    moistLabel  = new QLabel;
    moistValue  = new QLineEdit;
    moistCheck  = new QCheckBox;
    voiceLabel  = new QLabel;
    voiceValue  = new QLineEdit;
    voiceCheck  = new QCheckBox;
    levelLabel  = new QLabel;
    levelValue  = new QLineEdit;
    levelCheck  = new QCheckBox;
    //Output vars
    outputBox       = new QGroupBox;
    outputLayout    = new QGridLayout;
    pumpLabel   = new QLabel;
    pumpSwitch  = new QPushButton;
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
    inputLayout->addWidget(tempCheck,0,0,Qt::AlignTop | Qt::AlignRight);
    inputLayout->addWidget(dcLabel,0,1);
    inputLayout->addWidget(dcValue,0,1,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(dcCheck,0,1,Qt::AlignTop | Qt::AlignRight);
    inputLayout->addWidget(motioLabel,0,2);
    inputLayout->addWidget(motioValue,0,2,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(motioCheck,0,2,Qt::AlignTop | Qt::AlignRight);
    inputLayout->addWidget(moistLabel,0,3);
    inputLayout->addWidget(moistValue,0,3,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(moistCheck,0,3,Qt::AlignTop | Qt::AlignRight);
    inputLayout->addWidget(voiceLabel,0,4);
    inputLayout->addWidget(voiceValue,0,4,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(voiceCheck,0,4,Qt::AlignTop | Qt::AlignRight);
    inputLayout->addWidget(levelLabel,0,5);
    inputLayout->addWidget(levelValue,0,5,Qt::AlignBottom | Qt::AlignCenter);
    inputLayout->addWidget(levelCheck,0,5,Qt::AlignTop | Qt::AlignRight);
    inputLayout->addWidget(comNumber,1,5,Qt::AlignBottom | Qt::AlignCenter);

    inputLayout->addWidget(getValuesButton,1,5,Qt::AlignRight);

    outputBox->setLayout(outputLayout);
    outputLayout->addWidget(pumpLabel,0,0);
    outputLayout->addWidget(pumpSwitch,1,0,Qt::AlignBottom | Qt::AlignCenter);
    outputLayout->addWidget(sdLabel,0,1);
    //outputLayout->addWidget(sdAngle,1,1,Qt::AlignBottom | Qt::AlignCenter);
    outputLayout->addWidget(sdControl,2,1,Qt::AlignBottom | Qt::AlignCenter);
    outputLayout->addWidget(ledLabel,0,2);
    outputLayout->addWidget(ledColor,1,2,Qt::AlignBottom | Qt::AlignRight);

    outputLayout->addWidget(RColor,1,2,Qt::AlignCenter | Qt::AlignCenter);
    outputLayout->addWidget(GColor,2,2,Qt::AlignCenter | Qt::AlignCenter);
    outputLayout->addWidget(BColor,3,2,Qt::AlignCenter | Qt::AlignCenter);

    outputLayout->addWidget(RLabel,1,2,Qt::AlignCenter | Qt::AlignLeft);
    outputLayout->addWidget(GLabel,2,2,Qt::AlignCenter | Qt::AlignLeft);
    outputLayout->addWidget(BLabel,3,2,Qt::AlignCenter | Qt::AlignLeft);

    inputLayout->addWidget(inCom,1,5,Qt::AlignBottom | Qt::AlignLeft);
    inputLayout->addWidget(breakBut,1,4,Qt::AlignBottom | Qt::AlignLeft);

    //const QStringList text{"off","green","red","blue"};
    //ledColor->addItems(text);

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
    dcLabel->setAlignment(Qt::AlignCenter);
    motioLabel->setAlignment(Qt::AlignCenter);
    moistLabel->setAlignment(Qt::AlignCenter);
    voiceLabel->setAlignment(Qt::AlignCenter);
    levelLabel->setAlignment(Qt::AlignCenter);

    pumpLabel->setAlignment(Qt::AlignCenter);
    sdLabel->setAlignment(Qt::AlignCenter);
    ledLabel->setAlignment(Qt::AlignCenter);

    tempValue->setReadOnly(true);
    dcValue->setReadOnly(true);
    motioValue->setReadOnly(true);
    moistValue->setReadOnly(true);
    voiceValue->setReadOnly(true);
    levelValue->setReadOnly(true);

    tempValue->setFixedWidth(100);
    dcValue->setFixedWidth(100);
    motioValue->setFixedWidth(100);
    moistValue->setFixedWidth(100);
    voiceValue->setFixedWidth(100);
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
    dcLabel->setPixmap(QPixmap(":/Icons/dcL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    motioLabel->setPixmap(QPixmap(":/Icons/motioL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    moistLabel->setPixmap(QPixmap(":/Icons/moistL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    voiceLabel->setPixmap(QPixmap(":/Icons/voiceL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    levelLabel->setPixmap(QPixmap(":/Icons/levelL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));

    pumpLabel->setPixmap(QPixmap(":/Icons/pumpL.png").scaled(size.width()/8,size.height()/3,Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
void Testing::Get(){
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

   /* if (serial->bytesAvailable()){
        for (i=0; i<30;i++){
            serial->read(getData,30);
            data[3].push_back(getData[i]);*/
            //if (getData[i] == ';') break;
      //  }
       /* serial->read(getData,30);
        while(getData[i-1] !=';'){
            serial->read(getData,30);
            i++;
        }*/

    /*getData[i] = NULL;
    char  *rest = NULL;
    char *token;
    for (token = strtok_s(getData,",",&rest);   //DELIMITER = ","
    token!=NULL;
    token = strtok_s(NULL,",",&rest)){
       data[counter] = (token);
       counter++;
       }*/
    tempValue->insert(data[0]);
    levelValue->insert(data[1]);
    moistValue->insert(data[2]);
    data[0].clear();
    data[1].clear();
    data[2].clear();
    data[3].clear();

    }




/*void Testing::Get()
{   tempValue->clear();
    moistValue->clear();
    levelValue->clear();

    if (tempCheck->checkState()){
        serial->setPortName(com);
        char l[] = {'6','\n'};
        serial->write(l);
        serial->waitForReadyRead();

        char buffer[9];
        QString buff;
        for(int i=0;i<9;i++){
            serial->read(buffer,9);
            if ((int(buffer[i]) >= 48 && int(buffer[i]) <= 57) || (int(buffer[i]) == 46))
            {buff.push_back(buffer[i]);}
            else continue;

        }
        tempValue->insert(buff);
        buff.clear();
        Sleep(10);
    }


    if (moistCheck->checkState()){
        serial->setPortName(com);
        char l[] = {'8','\n'};
        serial->write(l);
        serial->waitForReadyRead();
        char buffer[11];
        QString buff;
        for(int i=0;i<11;i++){
            serial->read(buffer,11);
            if ((int(buffer[i]) >= 48 && int(buffer[i]) <= 57) || (int(buffer[i]) == 46))
            {buff.push_back(buffer[i]);}
            else continue;
        }
        moistValue->insert(buff);
        buff.clear();
        Sleep(10);
    }
    if (levelCheck->checkState()){
        serial->setPortName(com);
        char l[] = {'7','\n'};
        serial->write(l);
        serial->waitForReadyRead();

        char buffer[7];
        QString buff;
        for(int i=0;i<7;i++){
            serial->read(buffer,7);
            if ((int(buffer[i]) >= 48 && int(buffer[i]) <= 57) || (int(buffer[i]) == 46))
            {buff.push_back(buffer[i]);}
            else continue;
        }

        levelValue->insert(buff);

        buff.clear();
        Sleep(10);
    }

}*/

void Testing::clickedaction(){
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
