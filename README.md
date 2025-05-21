# `siri::tools`
A collection of random C++ utilities that I found myself using often.

## Compilation
### Requirements
Compiling this project requires:
- A modern C++ compiler and `std` library. 
    (I use the latest stable `g++`, 
    which is what I officially support, but `clang++` and (possibly) MSVC `cl` should also work)
- Meson (and by extension, python3, ninja, etc.)

_**Note:** While this library doesn't currently depend on Boost, I am seriously considering requiring it._

Optionally, it is useful to also have:
- Doxygen (for generating documentation locally)
### Compiling
To compile the library, simply run:
```sh
meson setup ./buildDir && meson compile -C ./buildDir siricxx
```
Compile with `CFLAGS="-D_SIRI_DEBUG $CFLAGS"` or `#define _SIRI_DEBUG` 
to enable more expressive logging and some debug assertions.

## Library Contents

- `int sanity_check()`, a function that returns 0.
- `RecalculateLazy<T>`, a class that manages a lazily-reevaluated optional.

## Documentation
This repository does not contain any generated documentation, 
but you can easily generate it by running in the project root:
```sh
doxygen
```
To open interactive web docs, open `./docs/html/index.html`.
To generate a static PDF reference manual, use
```sh
make -C ./docs/latex
```
and then open `./docs/latex/refman.pdf`.

## Development Information
### Testing
All tests should pass
Tests are simple programs that return 0 on success.
```sh
meson setup ./buildDir && meson test -C ./buildDir
```
Furthermore, I will strictly disallow any warnings generated when built on Linux and g++ 14, 
including those brought on by (-Wpedantic, -Wextra).
### Writing Documentation
This project is documented with [Doxygen](https://doxygen.nl/), using QT-style
doc-comments.
Please try to keep documentation high-quality and tag your work with `\author` and `\since`.
#### Internal Documentation
I would strongly suggest building your own copy of the documentation with
```
INTERNAL_DOCS = yes
```
You can find exactly what line this setting is on with 
```sh
cat Doxyfile | grep INTERNAL
```
The internal docs contain implementation details and the like, 
that are not necessary for consumers of the library.
### Code Style
I haven't setup any autoformat or linting but I intend to in the near future. Watch this space.

## License
The program code in this library is protected under the copyright (2025) of the 
contributors who wrote it. Particularly, Kira "Siri" K.

This program is free software: you can redistribute it and/or modify it under 
the terms of the GNU Lesser General Public License as published by the Free Software Foundation, 
either version 3 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License along with this program. 
(Particularly, in `./COPYING` and `./COPYING.LESSER`)
If not, see <https://www.gnu.org/licenses/>. 
