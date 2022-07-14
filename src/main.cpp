#include "wgm_user.h"
#include <sqlite3.h>

int main() {
    wgm_user::user app_user;
    app_user.run_app();
    app_user.stop_app();
    return 0;
}