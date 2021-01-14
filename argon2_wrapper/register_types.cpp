#include "register_types.h"

#include "core/class_db.h"
#include "argon2_wrapper.hpp"

void register_argon2_wrapper_types() {
    ClassDB::register_class<godot::Argon2Wrapper>();
}

void unregister_argon2_wrapper_types() {}