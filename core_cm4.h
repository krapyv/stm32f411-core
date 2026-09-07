#ifndef CORE_CM4_H
#define CORE_CM4_H

#include <stdint.h>

// offsets:
// ISER: 0x000 - 0x01C
// Reserved: 0x80-0x20 = 0x60 = 96 bytes = 24 words
// ICER: 0x080 - 0x9C
// Reserved: 0x100-0x0A0 = 0x60 = 96 bytes = 24 words
// ISPR: 0x100 - 0x11C
// Reserved: 0x180-0x120 = 0x60 = 96 bytes = 24 words
// ICPR: 0x180 - 0x19C
// Reserved: 0x200-0x1A0 = 0x60 = 96 bytes = 24 words
// IABR: 0x200 - 0x21C
// Reserved: 0x300-0x220 = 0xE0 = 224 bytes = 56 words
// IPR: 0x300 - 0x3EF
// Reserved: 0xE00-0x3F0 = 0xA10 = 2576 bytes = 644 words
// SVIR: 0xE00
typedef struct
{
    // Interrupt Set-enable Registers
    volatile uint32_t ISER[8]; // 0xE000E100-0xE000E11C
    uint32_t RESERVED0[24];
    // Interrupt Clear-enable Registers
    volatile uint32_t ICER[8]; // 0XE000E180-0xE000E19C
    uint32_t RESERVED1[24];
    // Interrupt Set-pending Registers
    volatile uint32_t ISPR[8]; // 0XE000E200-0xE000E21C
    uint32_t RESERVED2[24];
    // Interrupt Clear-pending Registers
    volatile uint32_t ICPR[8]; // 0XE000E280-0xE000E29C
    uint32_t RESERVED3[24];
    // Interrupt Active Bit Registers
    volatile uint32_t IABR[8]; // 0xE000E300-0xE000E31C
    // Interrupt Priority Registers
    uint32_t RESERVED4[56];
    volatile uint8_t IPR[240]; // 0xE000E400-0xE000E4EF
    uint32_t RESERVED5[644];
    // Software Trigger Interrupt Register
    volatile uint32_t STIR; // 0xE000EF00
} NVIC_RegDef_t;

typedef struct
{
    volatile uint32_t CSR;   // 0x00
    volatile uint32_t RVR;   // 0x04
    volatile uint32_t CVR;   // 0x08
    volatile uint32_t CALIB; // 0x0C
} SYST_RegDef_t;

typedef struct
{
    volatile uint32_t ACTLR; // 0xE000E008 - 0xE000E00B - Auxilary Control Register
    // CPUID: 0xE000ED00
    // the first byte after ACTLR: 0xE000E00C
    // 0xE000ED00 - 0xE000E00C = 0xCF4 = 3316 bytes => 3316 / 4 = 829 uint32_t
    uint32_t RESERVED0[829];
    volatile uint32_t CPUID; // 0xE000ED00 - 0xE000ED03 - CPUID Base Register
    volatile uint32_t ICSR;  // 0xE000ED04 - 0xE000ED07 - Interrupt Control and State Register
    volatile uint32_t VTOR;  // 0xE000ED08 - 0xE000ED0B - Vector Table Offset Register
    volatile uint32_t AIRCR; // 0xE000ED0C - 0xE000ED0F - Application Interrupt and Reset Control Register
    volatile uint32_t SCR;   // 0xE000ED10 - 0xE000ED13 - System Control Register
    volatile uint32_t CCR;   // 0xE000ED14 - 0xE000ED17 - Configuration and Control Register
    volatile uint32_t SHPR1; // 0xE000ED18 - 0xE000ED1B - System Handler Priority Register 1
    volatile uint32_t SHPR2; // 0xE000ED1C - 0xE000ED1F - System Handler Priority Register 2
    volatile uint32_t SHPR3; // 0xE000ED20 - 0xE000ED23 - System Handler Priority Register 3
    volatile uint32_t SHCRS; // 0xE000ED24 - 0xE000ED27 - System Handler Control and State Register
    volatile uint32_t CFSR;  // 0xE000ED28 - 0xE000ED2B - Configurable Fault Status Register
    // CFSR subregisters:
    // uint8_t MMSR // 0xE000ED28 - MemManage Fault Status Register
    // uint8_t BFSR // 0xE000ED29 - BusFault Status Register
    // uint16_t UFSR // 0xE000ED2A - 0xE000ED2B - UsageFault Status Register
    volatile uint32_t HFSR;  // 0xE000ED2C - 0xE000ED2F - HardFault Status Register
    uint32_t RESERVED1;      // 0xE000ED30 - 0xE000ED33
    volatile uint32_t MMFAR; // 0xE000ED34 - 0xE000ED37 - MemManage Fault Address Register
    volatile uint32_t BFAR;  // 0xE000ED38 - 0xE000ED3B - BusFault Address Register
    volatile uint32_t AFSR;  // 0xE000ED3C - 0xE000ED3F - Auxilary Fault Status Register
} SCB_RegDef_t;

#define NVIC_BASE (0xE000E100UL)
#define SYST_BASE (0xE000E010UL)
#define SCB_BASE (0xE000E008Ul)

#define NVIC ((NVIC_RegDef_t *)NVIC_BASE)
#define SYST ((SYST_RegDef_t *)SYST_BASE)
#define SCB ((SCB_RegDef_t *)SCB_BASE)

#define SYST_CVR_MAX_RELOAD 0x00FFFFFFUL

__attribute__((always_inline)) static inline void __DMB(void)
{
    __asm volatile("dmb" ::: "memory");
}

__attribute__((always_inline)) static inline void __NOP(void)
{
    __asm volatile("nop");
}

/**
 * @brief Executes the Wait For Interrupt (WFI) assembly instruction.
 *        Puts the CPU core into low-power sleep state until an interrupt fires.
 */
static inline void __attribute__((always_inline)) __WFI(void)
{
    __asm__ volatile("wfi");
}

static inline void __disable_irq(void)
{
    __asm__ volatile("cpsid i" : : : "memory");
}

static inline void __enable_irq(void)
{
    __asm__ volatile("cpsie i" : : : "memory");
}
#endif