#include "server.h"
#include <locale>

int main() {
    // 设置C++全局locale为C locale
    std::locale::global(std::locale("C"));
    FlipCoinServer server;
    server.run();

    return 0;
}
