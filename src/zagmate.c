#include "zagmate.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>

ReturnStatus write_vm(VM *vm, Instruction* bytecode, size_t len) {
    if (!vm){
        printf("VM not initialized!\n");
        return NULL_VM;
    }
    if (!bytecode){
        printf("Bytecode is empty!\n");
        return NULL_BYTECODE;
    }

    vm->bytecode = bytecode;
    vm->program_size = len;

    return OK;
}

ReturnStatus append_vm(VM *vm, Instruction instruction) {
    if (!vm){
        printf("VM not initialized!\n");
        return NULL_VM;
    }

    if (!vm->bytecode){
        printf("Cannot append to bytecode, bytecode is NULL!\n");
        return NULL_BYTECODE;
    }
    if (vm->program_size >= vm->capacity){
        printf("Cannot append to bytecode, bytecode is full!\n");
        return FULL_BYTECODE;
    }
    vm->bytecode[vm->program_size] = instruction;

    vm->program_size++;

    return 0;
}

ReturnStatus run_vm_cycle(VM *vm) {
    if (!vm){
        printf("VM not initialized!\n");
        return NULL_VM;
    }
    if (!vm->bytecode){
        printf("Bytecode is empty!\n");
        return NULL_BYTECODE;
    }

    Instruction current_instruction = vm->bytecode[vm->pc];
    Handler handler = vm->handlers[current_instruction.opcode];
    if (!handler){
        printf("Unknown opcode %u\n", current_instruction.opcode);
        return GENERAL_NULL;
    }

    vm->pc++;
    handler(vm, &current_instruction);
    return 0;
}

ReturnStatus run_vm(VM *vm) {
    if (!vm){
        printf("VM not initialized!\n");
        return NULL_VM;
    }
    while (vm->pc < vm->program_size && !vm->halted) {
        run_vm_cycle(vm);
    }
    return OK;
}

Instruction make_vm(uint8_t opcode, uint8_t operand_count, int64_t operands[]){
    Instruction instruction;
    instruction.opcode = opcode;
    instruction.operand_count = operand_count;
    instruction.operands = malloc(operand_count * sizeof(int64_t));

    if (!instruction.operands){
        printf("Memory allocation error!\n");
        return instruction;
    }

    for (size_t i = 0; i < operand_count; i++){
        instruction.operands[i] = operands[i];
    }

    return instruction;
}

ReturnStatus register_handler_vm(VM* vm, uint8_t opcode, Handler handler) {
    if (!handler){
        printf("Handler not found!\n");
        return GENERAL_NULL;
    }
    if (!vm){
        printf("VM not initialized!\n");
        return NULL_VM;
    }
    vm->handlers[opcode] = handler;
    return 0;
}

ReturnStatus clean_vm(VM *vm) {
    if (!vm){
        printf("VM not initialized!\n");
        return NULL_VM;
    }

    for (size_t i = 0; i < vm->program_size; i++) {
        free(vm->bytecode[i].operands);
    }

    vm->program_size = 0;

    free(vm->bytecode);
    free(vm->vtable);

    vm->vtable = NULL;
    vm->bytecode = NULL;

    vm->program_size = 0;
    return OK;
}

ReturnStatus init_vtable(vtable* vtable) {
    vtable->write = write_vm;
    vtable->run = run_vm;
    vtable->clean = clean_vm;
    vtable->register_handler = register_handler_vm;
    vtable->make = make_vm;
    return OK;
}

ReturnStatus init_vm(VM *vm) {
    vm->program_size = 0;
    vm->bytecode = NULL;
    vm->vtable = malloc(sizeof(vtable));
    init_vtable(vm->vtable);
    vm->capacity = 0;

    vm->pc = 0;

    vm->halted = 0;
    for (size_t i = 0; i < 32; i++){
        vm->regs[i].address = i;
        vm->regs[i].data.value = 0;
    }
    return OK;
}

Register* find_register(Register* regs, uint32_t addr, size_t count){
    if (!regs){
        printf("Registers not found!\n");
        return NULL_REGISTER;
    }
    if (addr < 0 || addr >= count){
        printf("Address out of bounds!\n");
        return NULL_REGISTER;
    }
    return &regs[addr];
}