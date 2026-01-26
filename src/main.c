#include "math/math.h"
#include "io/tga_image.h"
#include "assets/model.h"
#include "render/renderer.h"

int main() {
	render_target* t = create_render_target(500, 500);

	model* monke = load_model_obj("assets/monkey.obj");
	draw_wired_model(monke, t, 0xFFFFFF);
	write_tga("out.tga", t->data, t->width, t->height);
}
