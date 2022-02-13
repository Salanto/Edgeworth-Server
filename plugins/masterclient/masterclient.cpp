#include "masterclient.hpp"

MasterClientPlugin::MasterClientPlugin()
{
    m_socket = new QTcpSocket();
    connect(m_socket, &QAbstractSocket::readyRead,
            this, &MasterClientPlugin::onReadyRead);
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

}

void MasterClientPlugin::updateAdvertiserConfiguration(const QString &f_server_name, const QString &f_server_description)
{

}

void MasterClientPlugin::onReadyRead()
{

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
}

void MasterClientPlugin::handlePacket(const QStringList& f_packet)
{

}
