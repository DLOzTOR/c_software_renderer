#include <stdio.h>

#include "math/math.h"
#include "io/tga_image.h"
#include "assets/model.h"
#include "render/renderer.h"

void test_draw_line() {
	render_target* t = create_render_target(500, 500);
	vec2i s = {250,0};
	vec2i e = {0,499};
	vec2i s1 = {250, 499};
	vec2i e1 = {0, 0};
	vec2i s2 = {0,250};
	vec2i e2 = {499,0};
	vec2i s3 = {499, 250};
	vec2i e3 = {0, 0};
	int32_t c = 0x00FF00;
	for (int32_t x = 0; x <= 500; x+=50) {
		e.x = x;
		e1.x = x;
		e2.y = x;
		e3.y = x;
		if (e.x > 499)e.x = 499;
		draw_line(&s, &e, t, c);
		//draw_line(&s1, &e1, t, c);
		draw_line(&s2, &e2, t, c);
		draw_line(&s3, &e3, t, c);
	}
	write_tga("test.tga", t->data, t->width, t->height);
}

int super_main() {
	render_target* t = create_render_target(2500, 2500);

	model* monke = load_model_obj("assets/monkey.obj");
	printf("%p monke\n", monke);
	draw_wired_model(monke, t, 0xFFFFFF);
	free_model(monke);
	monke = (void*)0;
	write_tga("out.tga", t->data, t->width, t->height);
	return 0;
}

int main() {
	super_main();
}
