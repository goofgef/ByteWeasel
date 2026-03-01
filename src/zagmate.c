#include "zagmate.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int write_vm(VM *vm, Instruction* bytecode, size_t len) {
    if (!bytecode) return 1;
    if (!vm) return 1;

    vm->bytecode = bytecode;
    vm->program_size = len;
    return 0;
}

int run_vm(VM *vm) {
    if (!vm) return 1;
    if (!vm->bytecode) return 1;

    //Loop through each instruction in bytecode
    for (size_t i = 0; i < vm->program_size; i++) {
        Instruction current_instruction = vm->bytecode[i];
        Handler handler = vm->handlers[current_instruction.opcode];
        if (!handler){
            printf("Unkown opcode %u\n", current_instruction.opcode);
            return 1;
        }
        handler(vm, &current_instruction);
    }
}

int register_handler_vm(VM* vm, uint8_t opcode, Handler handler) {
    if (!handler) return 1;
    vm->handlers[opcode] = handler;
    return 0;
}

int clean_vm(VM *vm) {
    if (!vm) return 1;
    vm->program_size = 0;
    free(vm->bytecode);
}

int init_vm(VM *vm) {
    if (!vm) return 1;
    vm->program_size = 0;
    vm->bytecode = NULL;
    return 0;
}

Register* find_register(Register* regs, uint32_t addr, size_t count){
     for (size_t i = 0; i < count; i++){
        if (regs[i].address == addr) return &regs[i];
     }
     return NULL;
}
int main() {
    VM vm = {};
    init_vm(&vm);

    return 0;
}