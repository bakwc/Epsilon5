#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "application.h"

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    TApplication app(argc, argv);

    if (!app.Init()) {
        return 1;
    }

    return app.exec();
}
