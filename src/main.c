#include <stdio.h>
#include "math/math.h"
#define UTILS_IMPLEMENTATION
#include "utility/utils.h"
#include "render/color.h"

int main() {
	int color = create_color(0xAB, 0xCD, 0xEF);
	printf("%X\n", get_red(color));
	printf("%X\n", get_green(color));
	printf("%X\n", get_blue(color));
	printf("%X\n", color); 
}
