cmd_/home/ubuntu/work/Device_Driver_Final/src/monitor_proc.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /home/ubuntu/work/Device_Driver_Final/src/monitor_proc.ko /home/ubuntu/work/Device_Driver_Final/src/monitor_proc.o /home/ubuntu/work/Device_Driver_Final/src/monitor_proc.mod.o;  true