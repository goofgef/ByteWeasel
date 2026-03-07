#include "byteweasel_builtin.h"
#include "byteweasel.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc >= 3) {
        fprintf(stderr, "Usage: byteweasel -w/--what\n");
        return 1;
    }

    if (argc > 1 && (strcmp(argv[1], "--what") == 0 || strcmp(argv[1], "-w") == 0)) {
        printf("ByteWeasel is a register-based VM made in C.\n");
        printf("ByteWeasel is meant to be a framework that others can build on.\n");
        return 0;
    }else{
        VM vm = {0};
        init_vm(&vm, 2);

        vm.vtable->register_handler(&vm, 0, &add);
        vm.vtable->register_handler(&vm, 1, &sub);

        Instruction* bytecode = malloc(2 * sizeof(Instruction));

        int64_t ops0[] = {0, 1, 2};
        int64_t ops1[] = {1, 1, 2};

        bytecode[0] = vm.vtable->make(0, 3, ops0);
        bytecode[1] = vm.vtable->make(1, 3, ops1);

        vm.regs[1].data.value = 11;
        vm.regs[2].data.value = 7;

        vm.vtable->write(&vm, bytecode, 2);
        vm.vtable->run(&vm);

        printf("Result in r0: %" PRId64 "\n", vm.regs[0].data.value); //18
        printf("Result in r1: %" PRId64 "\n", vm.regs[1].data.value); //4

        vm.vtable->clean(&vm);
        return 0;
    }
    return 0;
}