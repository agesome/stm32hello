__boot_flash = 0x8000000;
__boot_flash_size = 1k;
__flash = __boot_flash + __boot_flash_size;
__flash_size = 128K - __boot_flash_size;
__ram = 0x20000000;
__ram_size = 32K;
__stack_size = 2k;
__heap_size_min = 28K;

INCLUDE picolibc.ld
