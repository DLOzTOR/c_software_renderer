#include <stdio.h>

#include "io/tga_image.h"
#include "assets/model.h"
#include "render/renderer.h"

int main() {
	render_target* t = create_render_target(2500, 2500);

	model* monke = load_model_obj("assets/monkey.obj");
	printf("%p monke\n", monke);
	draw_wired_model(monke, t, 0xFFFFFF);
	free_model(monke);
	monke = (void*)0;
	write_tga("out.tga", t->data, t->width, t->height);
	return 0;
}
