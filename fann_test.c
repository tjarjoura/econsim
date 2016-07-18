#include <stdlib.h>
#include <time.h>

#include <fann.h>

int main() {
    fann_type *outputs;
    fann_type inputs[10] = {4.5, -2.3, 0.001, -0.0004, 40.5, 100, 33, 12.3, 9.9, -111.2};
    srand(time(NULL));

    struct fann *ann = fann_create_standard(3, 10, 2, 20);

    for (int j = 0; j < 4000; j++) {
        outputs = fann_run(ann, inputs);

        for (int i = 0; i < 20; i++)
            printf("%f, ", outputs[i]);

        fann_randomize_weights(ann, -0.5, 0.5);

        putchar('\n');
    }
}
