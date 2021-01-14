#pragma once

#include <cstring>
#include <argon2.h>

#include "core/class_db.h"
#include "core/ustring.h"
#include "core/print_string.h"
#include "core/resource.h"
#include "core/method_bind_ext.gen.inc"

#define DEFAULT_HASH_LEN 32
#define DEFAULT_ENCODED_LEN 108

namespace godot {

class Argon2Wrapper : public Resource {
    GDCLASS(Argon2Wrapper, Resource)

protected:
    static void _bind_methods();

public:
    Argon2Wrapper();
    ~Argon2Wrapper();

    String argon2_hash(String password, String salt, int t_cost, int m_cost, int parallelism, String type);
    bool argon2_verify(String hash, String password, String type);
};

}