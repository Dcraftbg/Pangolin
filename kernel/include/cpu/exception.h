#pragma once
// Mostly taken from a project of mine (Dcraftbg) MinOS:
// https://github.com/Dcraftbg/MinOS/blob/master/kernel/src/exception.h
// Licensed under MIT
  
#include <stdint.h>
#include <stddef.h>
// Defined by assembly
void idt_exception_division();
void idt_exception_debug();
void idt_exception_breakpoint();
void idt_exception_overflow();
void idt_exception_bound_range_exceeded();
void idt_exception_invalid_opcode();
void idt_exception_dna(); 
void idt_exception_double_fault();
void idt_exception_cop_segment_overrun();
void idt_exception_invalid_tss();
void idt_exception_segment_not_present();
void idt_exception_ssf();
void idt_exception_gpf();
void idt_exception_page_fault();
void idt_exception_floating_point();
void idt_exception_alignment();
void idt_exception_machine_check();
void idt_exception_simd();
void idt_exception_virtualization();
void idt_exception_control_protection();
void idt_exception_hypervisor_injection();
void idt_exception_vmm_comm();
void idt_exception_security();
void idt_spurious_interrupt();
enum {
    EXCEPTION_DIV,
    EXCEPTION_DEBUG,
    EXCEPTION_BREAKPOINT,
    EXCEPTION_OVERFLOW,
    EXCEPTION_BOUND_RANGE_EXCEED,
    EXCEPTION_INVALID_OPCODE,
    EXCEPTION_DNA,
    EXCEPTION_DOUBLE_FAULT,
    EXCEPTION_COP_SEGMENT_OVERRUN,
    EXCEPTION_INVALID_TSS,
    EXECPTION_SEGMENT_NOT_PRESENT,
    EXCEPTION_SSF,
    EXCEPTION_GPF,
    EXCEPTION_PAGE_FAULT,
    EXCEPTION_FLOAT,
    EXCEPTION_ALIGNMENT,
    EXCEPTION_MACHINE_CHECK,
    EXCEPTION_SIMD,
    EXCEPTION_VIRTUALIZATION,
    EXCEPTION_CONTROL_PROT,
    EXCEPTION_HYPERVISOR_INJECT,
    EXCEPTION_VMM_COMM,
    EXCEPTION_SECURITY,
};
typedef struct {
    uint64_t cr2;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t type;
    uint64_t code;
    uint64_t rip;
    uint64_t cs;
    uint64_t flags;
    uint64_t rsp;
    uint64_t ss;
} IDTEFrame; // IDT Exception Frame
void exception_handler(IDTEFrame* frame);
void init_exceptions();
