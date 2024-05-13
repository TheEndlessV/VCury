#include "widget.h"
#include "ui_widget.h"
#include "vcury.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("VCury v1.0.1");

    ui->plainText->setWordWrapMode(QTextOption::NoWrap);
    ui->cipherText->setWordWrapMode(QTextOption::NoWrap);
    ui->logOutput->setWordWrapMode(QTextOption::NoWrap);

    connect(ui->encButton, &QPushButton::clicked,
            [=](){
                plaintext = ui->plainText->toPlainText();
                key = ui->keyInput->text();
                iv = ui->ivInput->text();
                ciphertext = toQstr(AESEncrypt(
                                        toStdStr(plaintext),
                                        toStdStr(key),
                                        toStdStr(iv)
                                               ));
                ui->cipherText->setText(ciphertext);

                log("ENC", "plaintext(input)", plaintext);
                log("ENC", "key", key);
                log("ENC", "iv", iv);
                log("ENC", "ciphertext(output)", ciphertext);
            }
            );

    connect(ui->decButton, &QPushButton::clicked,
            [=](){
                ciphertext = ui->cipherText->toPlainText();
                key = ui->keyInput->text();
                iv = ui->ivInput->text();
                plaintext = toQstr(AESDecrypt(
                                        toStdStr(ciphertext),
                                        toStdStr(key),
                                        toStdStr(iv)
                                               ));
                ui->plainText->setText(plaintext);

                log("ENC", "ciphertext(input)", ciphertext);
                log("ENC", "key", key);
                log("ENC", "iv", iv);
                log("ENC", "plaintext(output)", plaintext);
            }
            );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::log(QString type, QString message, QString content){
    QString group = "[" + type + "] " + message + ": \"" + content + "\"";
    qDebug()<<group;
    ui->logOutput->append(group);
}
