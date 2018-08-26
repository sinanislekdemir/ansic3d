# Ansi C 3D Math Library


Some codes are derived from GLScene project (glscene.org)

I needed a basic ansi-c  3D library for another project of mine so I started
this project. I implemented my own needs within the library.

Documenting the library in README is a heavy job so instead, best documentation
is the code itself. So you may find the needed information in header files.

And for the use cases, you can refer to `tests/test.c`

## Installing
BBee Build tool is already inside the repo (https://github.com/sinanislekdemir/bbee)

To compile the library (to build/libansic3d.a):

    python bbee

To install the library:

    python bbee --install


To compile and run the tests

    python bbee --i=test.json

Or just run to compule and install the library and run the tests.

    ./build.sh


## Creator

sinan islekdemir | sinan@islekdemir.com 


## Note
I only compiled the code under MacOs so let me know if it works for you too.
