#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "../utils/uexception.h"
#include "application.h"

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    TApplication app(argc, argv);
    try {
        app.Init();
        qDebug() << "Server started";
    } catch (const UException& e) {
        qDebug() << "ERROR: " << e.what();
        app.exit(42);
    }
    return app.exec();
}
