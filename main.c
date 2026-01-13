#include <stdio.h>
#include "math.h"
#define UTILS_IMPLEMENTATION
#include "utils.h"
#include "color.h"

int main() {
	int color = create_color(0xAB, 0xCD, 0xEF);
	printf("%X\n", get_red(color));
	printf("%X\n", get_green(color));
	printf("%X\n", get_blue(color));
	printf("%X\n", color); 
}
