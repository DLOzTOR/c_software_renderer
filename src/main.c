#include "math/math.h"
#include "io/tga_image.h"
#include "render/renderer.h"

int main() {
	render_target* t = create_render_target(500, 500);
	draw_line(&(vec2i){0,0}, &(vec2i){499,499}, t, 0x0020FF20);
	write_tga("out.tga", t->data, t->width, t->height);
}
