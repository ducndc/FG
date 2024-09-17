# FG Project

This repository is first project use SFML library, which is developed by me.

## How to Use
1. Install Git and CMake. Use your system's package manager if available.
1. Follow [GitHub's instructions](https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template) for how to use their project template feature to create your own project.
1. Clone your new GitHub repo and open the repo in your text editor of choice.
1. Open [CMakeLists.txt](CMakeLists.txt). Rename the project and the executable to whatever name you want.
1. If you want to add or remove any .cpp files, change the source files listed in the `add_executable` call in CMakeLists.txt to match the source files your project requires. If you plan on keeping the default main.cpp file then no changes are required.
1. If your code uses the Audio or Network modules then add `sfml-audio` or `sfml-network` to the `target_link_libraries` call alongside the existing `sfml-graphics` library that is being linked.
1. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```
    Using CMake from the command line is straightforward as well.
    Be sure to run these commands in the root directory of the project you just created.

    ```
    cmake -B build
    cmake --build build
    ```
1. Enjoy!

## Upgrading SFML

SFML is found via CMake's [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) module.
FetchContent automatically downloads SFML from GitHub and builds it alongside your own code.
Beyond the convenience of not having to install SFML yourself, this ensures ABI compatability and simplifies things like specifying static versus shared libraries.

Modifying what version of SFML you want is as easy as changing the [`GIT_TAG`](CMakeLists.txt#L7) argument.
Currently it uses the latest in-development version of SFML 2 via the `2.6.x` tag.
If you're feeling adventurous and want to give SFML 3 a try, use the `master` tag.
Beware, this requires changing your code to suit the modified API!
The nice folks in the [SFML community](https://github.com/SFML/SFML#community) can help you with that transition and the bugs you may encounter along the way.

## But I want to...

Modify CMake options by adding them as configuration parameters (with a `-D` flag) or by modifying the contents of CMakeCache.txt and rebuilding.

### Change Compilers

See the variety of [`CMAKE_<LANG>_COMPILER`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER.html) options.
In particular you'll want to modify `CMAKE_CXX_COMPILER` to point to the C++ compiler you wish to use.

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
