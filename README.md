# gdnative-argon2-wrapper
Very basic wrapper around Argon2 for hashing within the Godot Engine.

## Steps to compile
1. Follow the steps on [godot-cpp](https://github.com/godotengine/godot-cpp) to compile the library and generate the necessary headers;
2. Compile the [Argon2](https://github.com/P-H-C/phc-winner-argon2) library;
3. Adjust folder structure according to your preferences (using CMakeLists or similar, if needed);
4. Compile the dll;
5. Follow the godot-cpp instructions to create the .gdns and .gdnlib files;
6. Drop the resulting files into your project's folder and use it.

Note: Since at the time of writing, the MinGW compilation of GDNative libraries does not work with the included Scons file, the included CMake file adds the necessary flags in accordance to issue [#3463](https://github.com/godotengine/godot-docs/issues/3463) and [#3754](https://github.com/godotengine/godot-docs/issues/3754) (See this issue if you'd rather use Scons).

## Usage

This wrapper has two main methods.

The hashing method:
```C++
String Argon2Wrapper::argon2_hash(String password, String salt, int t_cost, int m_cost, int parallelism, String variant)
```

Which when used in GDScript will look something like this:
```GDScript
var hashed_pass = wrapper.argon2_hash("My Password", "A Valid Salt", 2, 64, 2, "id")
```

And the verify method:
```C++
bool Argon2Wrapper::argon2_verify(String password, String hash, String variant)
```

Which in GDScript looks a little like:
```GDScript
wrapper.argon2_verify("My Password", hashed_pass, "id")
```

The variants can be: "i", "d" or "id". The rest of the arguments should be self-explanatory but you can consult the wrapper.cpp file to see the implementation, or check the Argon2 GitHub page for more information.

## License

Note that the only code I can distribute under the MIT license is the wrapper's. Make sure to check both Argon2's license as well as Godot's.
