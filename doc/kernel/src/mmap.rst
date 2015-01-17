Memory Map
==========

The Virtual Memory Space in Sepix is divided into a kernel region from 0 to 1GB and a userspace region from 1 to 4GB. The table given below shows a detailed description of areas in memory. Addresses are given in hexadecimal.

======================= ===========================
Address                 Description
======================= ===========================
``000b 8000-000b ffff`` VGA Video Memory
``0010 0000-0fff ffff`` Kernel .text, .data, .bss
``1000 0000-1fff ffff`` Kernel heap
``2000 0000-3fff ffff`` *reserved*
----------------------- ---------------------------
``4000 0000-4fff ffff`` User .text, .data, .bss
``5000 0000-5fff ffff`` User heap
``6000 0000-ffff efff`` *reserved*
----------------------- ---------------------------
``ffff f000-ffff ffff`` Page Tables, Page Directory
======================= ===========================
