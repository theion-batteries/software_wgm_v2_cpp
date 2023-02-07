#include "wgm_user.h"
#include "sinking_process.h"

int main() {
    wgm_processes::Iheating_process* h = new wgm_processes::heating_process();
    wgm_processes::Isinking_process* s = new wgm_processes::sinking_process();
    wgm_processes::Ialigning_process* a = new wgm_processes::aligning_process();
    wgm_processes::Icooling_process* c = new wgm_processes::cooling_process();
    //wgm_processes::Iextracting_process* e = new wgm_processes::extracting_process();

    delete h;
    delete s;
    delete a;
    delete c;
    //delete e;
    return 0;
}