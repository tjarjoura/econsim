#include "include/econsim.h"

void run() {
    while(1) {
        //set_agent_inputs();
        //calculate_agent_outputs();
        //update_world();
        handle_events();
        render();
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    init_world();
    init_graphics();
    run();

    return 0;
}
