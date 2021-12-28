#ifndef TESTING_H
#define TESTING_H
#include <QWidget>
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QGroupBox>
#include <QIODevice>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QScreen>
#include <QDial>
#include <QDesktopWidget>
#include "greetingwindow.h"
#include<string.h>

class Testing : public QWidget
{
    Q_OBJECT
public:
    Testing(GreetingWindow *parent = 0);

    GreetingWindow  *fromHead;
    QGridLayout     *testLayout;
    QComboBox       *comNumber;
    QPushButton     *getValuesButton;
    QPushButton     *breakBut;
    QSerialPort     *serial;
    //Input vars
    QGroupBox       *inputBox;
    QGridLayout     *inputLayout;
    QLabel          *tempLabel;
    QLineEdit       *tempValue;
    QCheckBox       *tempCheck;
    //QLabel          *dcLabel;
    //QLineEdit       *dcValue;
    //QCheckBox       *dcCheck;
    //QLabel          *motioLabel;
    //QLineEdit       *motioValue;
    //QCheckBox       *motioCheck;
    QLabel          *moistLabel;
    QLineEdit       *moistValue;
    QCheckBox       *moistCheck;
    //QLabel          *voiceLabel;
    //QLineEdit       *voiceValue;
    //QCheckBox       *voiceCheck;
    QLabel          *levelLabel;
    QLineEdit       *levelValue;
    QCheckBox       *levelCheck;
    //Output vars
    QGroupBox       *outputBox;
    QGridLayout     *outputLayout;
    //QLabel          *pumpLabel;
    //QPushButton     *pumpSwitch;
    QLabel          *sdLabel;
   // QPushButton        *sdAngle;
    QLabel         *ledLabel;
    QPushButton       *ledColor;
    QSlider         *RColor;
    QLabel          *RLabel;
    QSlider         *GColor;
    QLabel          *GLabel;
    QSlider         *BColor;
    QLabel          *BLabel;
    QPushButton       *inCom;
    QDial             *sdControl;
private:
    void createWidgets();
    void layoutWidgets();
    void widgetSettings();
private slots:
    void comNameChanged(int);
    void CheckComs();
    void getValuesButtonS();
    void readSerialPortS();
    void sdStart();
    void clickedaction();
    void Get();
    void breakConnect();


};

#endif // TESTING_H
