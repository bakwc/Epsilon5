#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "application.h"

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    TApplication app(argc, argv);

    if (!app.Init()) {
        qDebug() << "ERROR: Server already running or can't bind default server port";
        app.exit(0);
    }

    return app.exec();
}
