#include "masterclient.hpp"

MasterClientPlugin::MasterClientPlugin()
{
    m_socket = new QTcpSocket();
    connect(m_socket, &QAbstractSocket::readyRead,
            this, &MasterClientPlugin::onReadyRead);
    m_heartbeat = new QTimer;
    connect(m_heartbeat, &QTimer::timeout,
            this, &MasterClientPlugin::sendHeartbeat);
}

void MasterClientPlugin::connectMasterserver(QString f_hostname, int f_port)
{

}

void MasterClientPlugin::disconnectMasterserver()
{
    m_socket->close();
    emit MasterserverDisconnected();
}

void MasterClientPlugin::publishServer()
{
    QStringList l_data;
    l_data << m_server_name << m_server_description << QString::number(m_server_port);
    m_socket->write(escapePacket(l_data));
}

void MasterClientPlugin::sendHeartbeat()
{
    QStringList l_data;
    l_data << "KEEPALIVE";
}

void MasterClientPlugin::requestNews()
{

}

void MasterClientPlugin::setAdvertiserConfiguration(const QString &f_server_name, const QString &f_server_description, int f_server_port)
{
    m_server_name = f_server_name;
    m_server_description = f_server_description;
    m_server_port = f_server_port;
}

void MasterClientPlugin::updateAdvertiserConfiguration(const QString &f_server_name, const QString &f_server_description)
{
    m_server_name = f_server_name;
    m_server_description = f_server_description;
}

void MasterClientPlugin::onReadyRead()
{
    QStringList l_remote_data = unescapePacket(m_socket->readAll());
    if (!l_remote_data.isEmpty()) {
        handlePacket(l_remote_data);
    }
    qCritical() << "Invalid packet received.";
}

QByteArray MasterClientPlugin::escapePacket(const QStringList &f_packet)
{
    QStringList l_packet = f_packet;
    l_packet.replaceInStrings("#","<num>");
    l_packet.replaceInStrings("%","<percent>");
    l_packet << "%";
    return l_packet.join("#").toUtf8();
}

QStringList MasterClientPlugin::unescapePacket(const QByteArray &f_packet)
{
    QString l_packet = f_packet;
    QStringList l_split_packet = l_packet.split("#");
    if (l_split_packet.last() != "%") {
        qCritical() << "A parsing error occured. Unable to process masterserver packet.";
        return QStringList();
    }
    l_split_packet.removeAt(l_split_packet.size() -1);

    //The AO microcosm, now in AIO!
    l_split_packet.replaceInStrings("<num>","#")
            .replaceInStrings("<percent>","%");
    return l_split_packet;
}

void MasterClientPlugin::handlePacket(const QStringList& f_packet)
{
    MS_HEADER l_header = MS_ENUM.value(f_packet.at(0));

    switch (l_header){
        case MS_CONNECTED :
            emit MasterserverConnected();
            break;

        case MS_NEWS :
            emit MasterserverNews(f_packet.at(1));
            break;

        case MS_SUCCESS :
            if (f_packet.at(1) == "13") {
                emit serverPublished();
                m_heartbeat->start(1000 * 25);
                break;
            }

            if (f_packet.at(1) == "KEEPALIVE")
                emit heartbeatSuccess();

        case MS_ERROR :
            if (f_packet.size() >= 3) {
                emit errorReceived(f_packet.at(2));
            }
    }
}
