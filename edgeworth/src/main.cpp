#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication Edgeworth(argc, argv);
    QCoreApplication::setApplicationName("Edgeworth-Server");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::addLibraryPath("./plugins");
    return Edgeworth.exec();
}
