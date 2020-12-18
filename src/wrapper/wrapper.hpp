#pragma once

#include <cstring>
#include <Godot.hpp>
#include <Resource.hpp>
#include <argon2.h>

#define DEFAULT_HASH_LEN 32
#define DEFAULT_ENCODED_LEN 108

namespace godot {

class Argon2Wrapper : public Resource {
    GODOT_CLASS(Argon2Wrapper, Resource)

public:
    static void _register_methods();

    Argon2Wrapper();
    ~Argon2Wrapper();

    void _init();

    String argon2_hash(String password, String salt, int t_cost, int m_cost, int parallelism, String type);
    bool argon2_verify(String hash, String password, String type);
};

}