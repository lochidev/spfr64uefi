#include "KernelUtil.h"
#include "Memory/Heap.h"
#include "Scheduling/PIT/PIT.h"

uint64_t user_stack[1024];

void user_function() {
    //TODO: interrupts disabled, figure that out
    GlobalRenderer->Print("In userspace!");
    GlobalRenderer->Next();
    while(true){
        GlobalRenderer->Print("Usermode is okay!");
        GlobalRenderer->Next();       
    }
}

extern "C" void KernelStart(BootInfo* BootInfo){

    KernelInfo KernelInfo = InitializeKernel(BootInfo);
    EnableSCE();
    ToUserSpace((void*)user_function, (void*)&user_stack[1023]);
    while(true){
        asm ("hlt");
    }
}