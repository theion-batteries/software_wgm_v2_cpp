#include "wgm_user.h"
#include "sinking_process.h"

int main() {

    wgm_processes::Isinking_process* p = new wgm_processes::sinking_process();
    wgm_processes::Ialigning_process* a = new wgm_processes::aligning_process();

    delete p;
    delete a;
    return 0;
}