# software_wgm_v2_cpp
contains the wafer growing machine v2 [source code](src/) and [documentation](docs/wfg_system_modelling.pdf).
The App is currently built for Windows. the branch dev_win_api is the current working branch.


# architecture and module design
The High level design is demonstrated in the picture below.
The three levels (green, yellow and red) are internal application level.
The outer level (violet) is an external level (hardware).
Every process call is done in this order:
A process manager execute the processes sequentially.
process->system->subsystem->hardware. 
The integration of User interface will be done using the QT framework.

![arch](docs/tree_arch.jpg)
