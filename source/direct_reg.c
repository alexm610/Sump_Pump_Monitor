#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2708_PERI_BASE		0x7E200000
#define GPIO_BASE				(BCM2708_PERI_BASE + 0x200000) // GPIO controller
#define PAGE_SIZE				(4 * 1024)
#define BLOCK_SIZE				(4 * 1024)

int mem_fd;
void *gpio_map;
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

void setup_io();
void set_LED(int); 

void set_LED(int g) {
	if (GET_GPIO(g)) {
		printf("button_pressed\n");
	} else {
		printf("button released\n");
	}
}

void setup() {
	/* open /dev/mem */
	if ((mem_fd == open("/dev/mem", O_RDWR|O_SYNC)) < 0) {
		printf("Can't open /dev/mem \n");
		exit(-1);
	}

	gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
	close(mem_fd);

	if (gpio_map == MAP_FAILED) {
		printf("mmap failure: error %d\n", (int)gpio_map);
		exit(-1);
	}

	/* Always use volatile pointer! */
	gpio = (volatile unsigned *)gpio_map;
}

int main(int argc, char **argv) {
	int g, rep;

	setup_io();




	return 0;
}