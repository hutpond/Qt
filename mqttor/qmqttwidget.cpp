#include "qmqttwidget.h"
#include "ui_qmqttwidget.h"

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
    int rc;

    QString strAddress = ui->lineEdit_host->text() + ":" + ui->lineEdit_port->text();
    MQTTClient_create(&client, strAddress.toLocal8Bit(),
                      ui->lineEdit_clientId->text().toLocal8Bit(),
                      MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, nullptr, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) == MQTTCLIENT_SUCCESS)
    {
        ui->pushButton_connect->setEnabled(false);
        ui->pushButton_disconnect->setEnabled(true);
    }
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
    MQTTClient_subscribe(client, ui->lineEdit_topicSubscribe->text().toLocal8Bit(),
                         ui->comboBox_Subscribe->currentIndex());
}

void QMqttWidget::on_pushButton_Send_clicked()
{

}

void QMqttWidget::setSubscribe(const QString &text)
{
    ui->textBrowser->setPlainText(text);
}
