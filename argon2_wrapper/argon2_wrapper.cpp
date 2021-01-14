#include "argon2_wrapper.hpp"

using namespace godot;

Argon2Wrapper::Argon2Wrapper() {}

Argon2Wrapper::~Argon2Wrapper() {}

void Argon2Wrapper::_bind_methods() {
  ClassDB::bind_method(D_METHOD("argon2_hash", "password", "salt", "t_cost", "m_cost", "parallelism", "variant"), &Argon2Wrapper::argon2_hash);
  ClassDB::bind_method(D_METHOD("argon2_verify", "password", "hash", "variant"), &Argon2Wrapper::argon2_verify);
}

/**
 * Hashes a password with the selected variant, returning a godot::String with the encoded hash
 * @param password The password to be hashed
 * @param salt The salt to be used. A warning will be printed if the salt is too short
 * @param t_cost Number of iterations
 * @param m_cost Sets memory usage to m_cost kibibytes
 * @param parallelism Number of threads and compute lanes
 * @param variant Variant to be used. Can be i, d or id
 * @pre Returns an empty string on failure, or an encoded hash upon success
 */
String Argon2Wrapper::argon2_hash(String password, String salt, int t_cost, int m_cost, int parallelism, String variant) {
  CharString pass_data = password.utf8();
  CharString salt_data = salt.utf8();
  CharString variant_data = variant.utf8();

  char hash[DEFAULT_ENCODED_LEN];

  // Pointer to any of the Argon2 high-level API methods
  int (*target_fun)(
    uint32_t t_cost,
    uint32_t m_cost,
    uint32_t parallelism,
    const void *pwd,
    size_t pwdlen,
    const void *salt,
    size_t saltlen,
    size_t hashlen,
    char *encoded,
    size_t encodedlen
  );

  // Check which Argon2 variant is desired, return empty godot::String if invalid and prints an error
  if (strcmp(variant_data.get_data(), "i") == 0) {
    target_fun = &argon2i_hash_encoded;
  } else if (strcmp(variant_data.get_data(), "d") == 0) {
    target_fun = &argon2d_hash_encoded;
  } else if (strcmp(variant_data.get_data(), "id") == 0) {
    target_fun = &argon2id_hash_encoded;
  } else {
    print_error(String("Error: Please supply a valid hash type for argon_hash. They can be i, d or id."));
    return String("");
  }

  // Use function pointer to the correct high-level API variant
  int result = target_fun(
    t_cost,
    m_cost,
    parallelism,
    pass_data.get_data(),
    pass_data.length(),
    salt_data.get_data(),
    salt_data.length(),
    DEFAULT_HASH_LEN,
    hash,
    DEFAULT_ENCODED_LEN
  );

  // Return empty string if operation failed, prints said error
  if (result != ARGON2_OK) {
    String error = String(argon2_error_message(result));
    print_error(error);
    return String("");
  }

  // Return godot::String with encoded hash
  return String(hash);
}

/**
 * Verifies password against hash, based on the type selected
 * @param password Password that is to be verified
 * @param hash Hash to be checked against
 * @param variant Variant, can be i, d or id
 * @pre Returns false if the password does not check out, or no valid hash type has been passed
 * @pre Returns true if the password is successfuly verified against hash and type
 */
bool Argon2Wrapper::argon2_verify(String password, String hash, String variant) {
  CharString pass_data = password.utf8();
  CharString hash_data = hash.utf8();
  CharString variant_data = variant.utf8();

  // Pointer to any of the high-level API methods for verification
  int (*target_fun)(const char *encoded, const void *pwd, const size_t pwd_len);

  if (strcmp(variant_data.get_data(), "i") == 0) { target_fun = argon2i_verify; }
  else if (strcmp(variant_data.get_data(), "d") == 0) { target_fun = argon2d_verify; }
  else if (strcmp(variant_data.get_data(), "id") == 0) { target_fun = argon2id_verify; }
  else {
    print_error(String("Error: Please supply a valid hash type for argon_verify. They can be i, d or id."));
    return false;
  }
  return (target_fun(hash_data.get_data(), pass_data.get_data(), pass_data.length()) == ARGON2_OK);
}