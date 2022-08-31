#include "Util.hpp"

#ifdef PG_WINDOWS
#include "WinInclude.hpp"
#endif

void Windows::setupWindows() {
    //Set codepage to 65001 (UTF-8)
    #ifdef PG_WINDOWS
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif
}