#include "wgm_user.h"

int main() {

    wgm_processes::Iprocess_manager* p = new wgm_processes::process_manager();
    p->start_all();
    delete p;

    return 0;
}