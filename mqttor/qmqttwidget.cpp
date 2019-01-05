#include "qmqttwidget.h"
#include "ui_qmqttwidget.h"
#include <QMessageBox>

static volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void */*context*/, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void */*context*/, char *topicName, int /*topicLen*/, MQTTClient_message *message)
{
    char* szMessage;

    // Message process
    szMessage = static_cast<char*>(message->payload);
    QString strMessage(szMessage);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    QMqttWidget::ms_instance->setSubscribe(strMessage);
    return 1;
}

void connlost(void */*context*/, char */*cause*/)
{
}

QMqttWidget *QMqttWidget::ms_instance = nullptr;
QMqttWidget::QMqttWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMqttWidget)
{
    ui->setupUi(this);
    ms_instance = this;
}

QMqttWidget::~QMqttWidget()
{
    delete ui;
}

void QMqttWidget::on_pushButton_connect_clicked()
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    //MQTTClient_message pubmsg = MQTTClient_message_initializer;
    //MQTTClient_deliveryToken token;
    int rc;

    QString strAddress = ui->lineEdit_host->text();
    //strAddress += ":";
    //strAddress += ui->lineEdit_port->text();
    QString strClientId = ui->lineEdit_clientId->text();
    MQTTClient_create(
                &client,
                strAddress.toLatin1().data(),
                strClientId.toLatin1().data(),
                MQTTCLIENT_PERSISTENCE_NONE,
                nullptr
                );
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = "deepblue";
    conn_opts.password = "deepblue";

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        QMessageBox::warning(this, "error", QString::number(rc));
        return;
    }
    ui->pushButton_connect->setEnabled(false);
    ui->pushButton_disconnect->setEnabled(true);
    return;
}

void QMqttWidget::on_pushButton_disconnect_clicked()
{
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
}

void QMqttWidget::on_pushButton_Subscribe_clicked()
{
    QString strTopic = ui->lineEdit_topicSubscribe->text();
    QByteArray baTopic = strTopic.toLatin1();
    const char *pszTopic = baTopic.data();
    int nQos = ui->comboBox_Subscribe->currentIndex();
    QMessageBox::information(this, "subscribe", QString("%1, %2").arg(pszTopic).arg(nQos));
    MQTTClient_subscribe(client, pszTopic, nQos);
}

void QMqttWidget::on_pushButton_Send_clicked()
{
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    QString strMsg = ui->textEdit->toPlainText();
    QByteArray baMsg = strMsg.toLocal8Bit();
    const char *pszMsg = baMsg.data();
    QString strTopic = ui->lineEdit_topicSend->text();
    QByteArray baTopic = strTopic.toLatin1();
    const char *pszTopic = baTopic.data();
    pubmsg.payload = (void*)(pszMsg);
    pubmsg.payloadlen = (int)strlen(pszMsg);
    pubmsg.qos = ui->comboBox_Send->currentIndex();
    pubmsg.retained = 0;
    QMessageBox::information(this, "subscribe", QString("%1, %2, %3").arg(pszTopic).arg(pszMsg).arg(pubmsg.qos));
    MQTTClient_publishMessage(client, pszTopic, &pubmsg, &token);
}

void QMqttWidget::setSubscribe(const QString &text)
{
    ui->textBrowser->setPlainText(text);
}
