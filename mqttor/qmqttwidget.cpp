#include "qmqttwidget.h"
#include "ui_qmqttwidget.h"
#include <QMessageBox>

static volatile MQTTClient_deliveryToken deliveredtoken;
static QString s_strMessage;

void delivered(void */*context*/, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void */*context*/, char *topicName, int /*topicLen*/, MQTTClient_message *message)
{
    char* szMessage;
    //printf("topic: %s\n", topicName);

    // Message process
    szMessage = static_cast<char*>(message->payload);
    printf("message: %s\n", szMessage);
    s_strMessage = szMessage;
    s_strMessage = s_strMessage.mid(0, message->payloadlen);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}

void connlost(void */*context*/, char */*cause*/)
{
}

QMqttWidget::QMqttWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMqttWidget),
    m_nTimerId(0)
{
    ui->setupUi(this);

    m_strlistHost << "dc.quixmart.com" << "61.155.196.60";
    m_strlistPort << "1893" << "8093" << "";
    m_nHostIndex = 0;
    m_nPortIndex = 0;
    ui->lineEdit_host->setText(m_strlistHost.at(m_nHostIndex));
    ui->lineEdit_port->setText(m_strlistPort.at(m_nPortIndex));
}

QMqttWidget::~QMqttWidget()
{
    if (m_nTimerId != 0)
    {
        killTimer(0);
        m_nTimerId = 0;
    }
    delete ui;
}

void QMqttWidget::on_pushButton_connect_clicked()
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    QString strAddress = ui->lineEdit_host->text();
    QString strPort = ui->lineEdit_port->text();
    if (!strPort.isEmpty())
    {
        strAddress.append(':');
        strAddress.append(strPort);
    }
    QByteArray baAddress = strAddress.toLatin1();
    const char *pszAddress = baAddress.data();
    QString strClientId = ui->lineEdit_clientId->text();
    QByteArray baClientId = strClientId.toLatin1();
    const char *pszClientId = baClientId.data();
    //QMessageBox::information(this, "connect", QString("%1, %2").arg(pszAddress).arg(pszClientId));
    MQTTClient_create(&subscribe, pszAddress, pszClientId, MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = "deepblue";
    conn_opts.password = "deepblue";
    MQTTClient_setCallbacks(subscribe, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(subscribe, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        QMessageBox::warning(this, "subscribe connect failed", QString::number(rc));
        return;
    }

    strClientId += "publisher";
    baClientId = strClientId.toLatin1();
    pszClientId = baClientId.data();
    MQTTClient_connectOptions conn_opts2 = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&publisher, pszAddress, pszClientId, MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    conn_opts2.keepAliveInterval = 20;
    conn_opts2.cleansession = 1;
    conn_opts2.username = "deepblue";
    conn_opts2.password = "deepblue";
    //QMessageBox::information(this, "connect", QString("%1, %2").arg(pszAddress).arg(pszClientId));
    if ((rc = MQTTClient_connect(publisher, &conn_opts2)) != MQTTCLIENT_SUCCESS)
    {
        QMessageBox::warning(this, "publisher connect failed", QString::number(rc));
        return;
    }

    ui->pushButton_connect->setEnabled(false);
    ui->pushButton_disconnect->setEnabled(true);
    m_nTimerId = startTimer(300);
    return;
}

void QMqttWidget::on_pushButton_disconnect_clicked()
{
    MQTTClient_disconnect(subscribe, 10000);
    MQTTClient_destroy(&subscribe);
    MQTTClient_disconnect(publisher, 10000);
    MQTTClient_destroy(&publisher);
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    killTimer(m_nTimerId);
    m_nTimerId = 0;
}

void QMqttWidget::on_pushButton_Subscribe_clicked()
{
    QString strTopic = ui->lineEdit_topicSubscribe->text();
    QByteArray baTopic = strTopic.toLatin1();
    const char *pszTopic = baTopic.data();
    int nQos = ui->comboBox_Subscribe->currentIndex();
    //QMessageBox::information(this, "subscribe", QString("%1, %2").arg(pszTopic).arg(nQos));
    MQTTClient_subscribe(subscribe, pszTopic, nQos);
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
    MQTTClient_publishMessage(publisher, pszTopic, &pubmsg, &token);
    //QMessageBox::information(this, "subscribe", QString("%1, %2, %3").arg(pszTopic).arg((char*)pubmsg.payload).arg(pubmsg.payloadlen));
}

void QMqttWidget::timerEvent(QTimerEvent *)
{
    if (m_strMessage != s_strMessage)
    {
        m_strMessage = s_strMessage;
        ui->textBrowser->setText(m_strMessage);
    }
}

void QMqttWidget::on_pushButton_connect_3_clicked()
{
    ++m_nHostIndex %= m_strlistHost.size();
    ui->lineEdit_host->setText(m_strlistHost.at(m_nHostIndex));

}

void QMqttWidget::on_pushButton_connect_2_clicked()
{
    ++m_nPortIndex %= m_strlistPort.size();
    ui->lineEdit_port->setText(m_strlistPort.at(m_nPortIndex));

}
