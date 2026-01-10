#include <stdio.h>
#include "math.h"
#define UTILS_IMPLEMENTATION
#include "utils.h"

int main() {
	vec2i* posA = &(vec2i){15, 15};
	vec2i* posB = &(vec2i){10, 10};
	swap_p(posA, posB);
    printf("Vector2Int:(%d; %d)\n", posA->X, posA->Y);
    printf("Vector2Int:(%d; %d)\n", posB->X, posB->Y);
    return 0;
}
