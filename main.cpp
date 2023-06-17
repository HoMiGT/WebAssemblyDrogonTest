#include <drogon/drogon.h>
#include <string>

using namespace drogon;
using namespace std;


int main() {

    drogon::app().addListener("127.0.0.1", 8000);
    drogon::app().run();
    return 0;
}
