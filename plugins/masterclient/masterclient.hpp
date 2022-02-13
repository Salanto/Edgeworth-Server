#include "masterclientinterface.hpp"
#include <QtNetwork/QTcpSocket>
#include <QTimer>

class MasterClientPlugin : public QObject, MasterClientInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MasterClientInterface_iid)
    Q_INTERFACES(MasterClientInterface)

public :
    MasterClientPlugin();

    void connectMasterserver(QString f_hostname, int f_port);

    void disconnectMasterserver();

public slots:

    void publishServer();

    void sendHeartbeat();

    void requestNews();

    void setAdvertiserConfiguration(const QString& f_server_name, const QString& f_server_description, int f_server_port);

    void updateAdvertiserConfiguration(const QString& f_server_name, const QString& f_server_description);

signals:
    void MasterserverConnected();

    void MasterserverDisconnected();

    void serverPublished();

    void heartbeatSuccess();

    void MasterserverNews(const QString& f_news);

    void errorReceived(const QString& f_error_message);

private slots:

    /**
     * @brief Reads socket data and forwards it to packet handling.
     */
    void onReadyRead();

private:

    /**
     * @brief Escapes # and % symbols before writing it to the network socket.
     * @param QStringList containing all arguments of the packet.
     * @return QByteArray with escaped symbols to prevent packet processing issue.
     */
    QByteArray escapePacket(const QStringList& f_packet);

    /**
     * @brief Unescapes <percent> and <num> before returning it to the server for reply.
     * @param QStringList containing all arguments of the packet.
     * @return QStringList with unescaped symbols to prevent display errors.
     */
    QStringList unescapePacket(const QByteArray& f_packet);

    /**
     * @brief Handles AIO 0.4 formatted MS packets.
     */
    void handlePacket(const QStringList &f_packet);

    /**
      * @brief Member socket of the masterclient. Handles reading and writing to the MS.
      */
     QTcpSocket* m_socket;

     /**
      * @brief m_server_name
      */
     QString m_server_name;

     /**
      * @brief m_server_description
      */
     QString m_server_description;

     /**
      * @brief m_server_port
      */
     int m_server_port;

     /**
      * @brief Represents all possible replies of the AIO masterserver.
      */
     enum MS_HEADER {
         MS_CONNECTED,
         MS_SUCCESS,
         MS_NEWS,
         MS_ERROR
     };

     /**
      * @brief Translation map for packet handler readability sake.
      */
     QMap<QString,MS_HEADER> MS_ENUM =
     {
         {"1",          MS_CONNECTED},
         {"SUCCESS",    MS_SUCCESS},
         {"NEWS",       MS_NEWS},
         {"OKNOBO",     MS_ERROR}
     };
};
