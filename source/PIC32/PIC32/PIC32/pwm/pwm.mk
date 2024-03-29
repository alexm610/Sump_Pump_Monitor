# Since we are compiling in windows, select 'cmd' as the default shell.  This
# is important because make will search the path for a linux/unix like shell
# and if it finds it will use it instead.  This is the case when cygwin is
# installed.  That results in commands like 'del' and echo that don't work.
SHELL=cmd
# Specify the compiler to use
CC = xc32-gcc
# Specify the .elf to .hex converter
OBJCPY = xc32-bin2hex
# Specify the device we are using
ARCH = -mprocessor=32MX130F064B
# List the object files involved in this project
OBJ = pwm.o

# The default 'target' (output) is pwm.elf and 'depends' on
# the object files listed in the 'OBJS' assignment above.
# These object files are linked together to create pwm.elf.
# The linked file is converted to hex using program $(OBJCPY).
pwm.elf: $(OBJ)
	$(CC) $(ARCH) -o pwm.elf pwm.o -mips16 -DXPRJ_default=default \
		-legacy-libc -Wl,-Map=pwm.map
	$(OBJCPY) pwm.elf
	@echo Success!
	
# The object file pwm.o depends on pwm.c. pwm.c is compiled
# to create pwm.o. 
pwm.o: pwm.c
	$(CC) -g -x c -mips16 -Os -c $(ARCH) -MMD -o pwm.o pwm.c \
		-DXPRJ_default=default -legacy-libc

# Target 'clean' is used to remove all object files and executables
# associated wit this project
clean:
	@del *.o *.elf *.hex *.d *.map 2>NUL

# Target 'LoadFlash' is used to load the hex file to the microcontroller 
# using the flash loader.
LoadFlash:
	@Taskkill /IM putty.exe /F 2>NUL | wait 500
	pro32 -p -v pwm.hex

# Phony targets can be added to show useful files in the file list of
# CrossIDE or execute arbitrary programs:
dummy: pwm.hex pwm.map

explorer:
	explorer .
