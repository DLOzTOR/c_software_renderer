#include "entity.h"

entity create_entity(model* m) {
    return (entity){
        m,
        transform_identity()
    };
}