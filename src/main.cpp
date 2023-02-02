#include "wgm_user.h"
#include "sinking_process.h"

int main() {

    wgm_processes::Isinking_process* p = new wgm_processes::sinking_process();

    delete p;
    return 0;
}