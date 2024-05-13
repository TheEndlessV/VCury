#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void log(QString type, QString message, QString content);

private:
    Ui::Widget *ui;
    QString plaintext;
    QString ciphertext;
    QString key;
    QString iv;
};
#endif // WIDGET_H
