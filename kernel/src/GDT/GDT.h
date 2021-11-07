#pragma once

#include <stdint.h>

struct GDTDescriptor {
    uint16_t Size;
    uint64_t Offset;
} __attribute__((packed));

struct TSS {
    uint32_t reserved0; 
    uint64_t rsp0;      
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1; 
    uint64_t ist1;
    uint64_t ist2;     
    uint64_t ist3;     
    uint64_t ist4;
    uint64_t ist5;      
    uint64_t ist6;      
    uint64_t ist7;
    uint64_t reserved2; 
    uint16_t reserved3; 
    uint16_t iopb_offset;
}__attribute__((packed));

struct GDTEntry {
    uint16_t Limit0;
    uint16_t Base0;
    uint8_t Base1;
    uint8_t AccessByte;
    uint8_t Limit1_Flags;
    uint8_t Base2;
}__attribute__((packed));

struct GDT {
    GDTEntry Null; //0x00
    GDTEntry KernelCode; //0x08
    GDTEntry KernelData; //0x10
    GDTEntry UserNull;
    GDTEntry UserData;
    GDTEntry UserCode;
    GDTEntry OVMFData;
    GDTEntry OVMFCode;
    GDTEntry TSSLow;
    GDTEntry TSSHigh;
} __attribute__((packed)) 
__attribute((aligned(0x1000)));

extern GDT DefaultGDT;
extern "C" void LoadGDT(GDTDescriptor* GDTDescriptor);
extern "C" void EnableSCE();
extern "C" void ToUserSpace(void* userFunction, void* userStack);