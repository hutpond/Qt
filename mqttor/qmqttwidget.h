#ifndef QMQTTWIDGET_H
#define QMQTTWIDGET_H

#include <QWidget>
#include <MQTTClient.h>

namespace Ui {
class QMqttWidget;
}

class QMqttWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMqttWidget(QWidget *parent = nullptr);
    ~QMqttWidget();

    void setSubscribe(const QString &);

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_Subscribe_clicked();
    void on_pushButton_Send_clicked();

private:
    Ui::QMqttWidget *ui;

    MQTTClient client;
public:
    static QMqttWidget *ms_instance;
};

#endif // QMQTTWIDGET_H
