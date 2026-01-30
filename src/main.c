#include "io/tga_image.h"
#include "assets/model.h"
#include "render/renderer.h"
#include "core/entity.h"

int main() {
	render_target* t = create_render_target(4000, 4000);

	entity monke = create_entity(load_model_obj("assets/monkey.obj"));
	monke._transform.scale = (vec3f){0.1f, 0.1f, 0.1f};
	for (float x = -.66f ; x < .67f; x+=0.33f) {
		monke._transform.translate.x = x;
		for (float y = -.66f ; y < .67f; y+=0.33f) {
			monke._transform.translate.y = y;
			draw_entity(&monke, t, 0xFFFFFF);
		}
	}
	free_model(monke._model);
	monke._model = (void*)0;
	write_tga("out.tga", t->data, t->width, t->height);
	return 0;
}
