#include "wgm_user.h"

int main() {
    // test heating sys
    sulfur_heating_system::Iheater* h = new sulfur_heating_system::Heater();
    delete h;

    return 0;
}