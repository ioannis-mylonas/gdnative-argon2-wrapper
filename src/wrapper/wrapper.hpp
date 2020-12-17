#pragma once

#include <cstring>
#include <Godot.hpp>
#include <Resource.hpp>
#include <argon2.h>

#define DEFAULT_HASH_LEN 32
#define DEFAULT_ENCODED_LEN 108

namespace godot {

class ArgonWrapper : public Resource {
    GODOT_CLASS(ArgonWrapper, Resource)

public:
    static void _register_methods();

    ArgonWrapper();
    ~ArgonWrapper();

    void _init();

    String argon_hash(String password, String salt, int t_cost, int m_cost, int parallelism, String type);
    bool argon_verify(String hash, String password, String type);
};

}