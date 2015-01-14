        /*
         *
         * File:    kernel/src/arch/x86/mm.c
         * Author:  Christoph Landgraf
         * Purpose: Assembly Routines for mm setup
         *
         */
        
        .global mm_load_pagedir
        .type mm_load_pagedir, @function
mm_load_pagedir:
        mov 4(%esp), %eax
        mov %eax, %cr3
        ret
        
        .global mm_enable_paging
        .type mm_enable_paging, @function
mm_enable_paging:
        mov %cr0, %eax
        or $0x80000000, %eax
        mov %eax, %cr0
        ret
