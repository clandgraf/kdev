/*
 *
 * File:    kernel/src/arch/i386/arch.c
 * Author:  Christoph Landgraf
 * Purpose: Architecture initialization implementation 
 *          for the i386 architecture.
 *
 */

extern void gdt_init(void);

void arch_init(void)
{
    gdt_init();
}
