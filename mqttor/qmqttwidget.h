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

protected:
    virtual void timerEvent(QTimerEvent *) override;

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_Subscribe_clicked();
    void on_pushButton_Send_clicked();

    void on_pushButton_connect_3_clicked();

    void on_pushButton_connect_2_clicked();

private:
    Ui::QMqttWidget *ui;

    QStringList m_strlistHost;
    QStringList m_strlistPort;
    int m_nHostIndex;
    int m_nPortIndex;

    MQTTClient subscribe;
    MQTTClient publisher;
    QString m_strMessage;
    int m_nTimerId;
};

#endif // QMQTTWIDGET_H
