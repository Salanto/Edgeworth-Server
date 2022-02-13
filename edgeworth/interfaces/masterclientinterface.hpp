#include <QtPlugin>
#include <QObject>
#define MasterClientInterface_iid "de.salanto.AIO.Network.MasterClientInterface"

class MasterClientInterface
{
public:
    virtual ~MasterClientInterface() = default;

    virtual void connectMasterserver(QString f_hostname, int f_port) = 0;

    virtual void disconnectMasterserver() = 0;

public slots:

    virtual void publishServer() = 0;

    virtual void sendHeartbeat() = 0;

    virtual void requestNews() = 0;

    virtual void setAdvertiserConfiguration(const QString& f_server_name, const QString& f_server_description, int f_server_port) = 0;

    virtual void updateAdvertiserConfiguration(const QString& f_server_name, const QString& f_server_description) = 0;

signals:
    virtual void MasterserverConnected() = 0;

    virtual void MasterserverDisconnected() = 0;

    virtual void serverPublished() = 0;

    virtual void heartbeatSuccess() = 0;

    virtual void MasterserverNews(const QString& f_news) = 0;

    virtual void errorReceived(const QString& f_error_message) = 0;
};


Q_DECLARE_INTERFACE(MasterClientInterface, MasterClientInterface_iid)
