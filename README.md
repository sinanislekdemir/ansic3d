# Ansi C 3D Math Library

[![Build Status](https://travis-ci.org/sinanislekdemir/ansic3d.svg?branch=master)](https://travis-ci.org/sinanislekdemir/ansic3d)

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


## Tests

    $ bbee --i=test.json
    Building using gcc
    Collecting files
    Building ./tests/test.c
    Running build/test
    TestCloneVector [OK]
    TestAddVector [OK]
    TestSubVector [OK]
    TestScaleVector [OK]
    TestCrossProduct [OK]
    TestNormalizeVector [OK]
    TestDivideVector [OK]
    TestPerpendicularVector [OK]
    TestRotateAroundX [OK]
    TestRotateAroundY [OK]
    TestRotateAroundZ [OK]
    TestVectorLength [OK]
    TestDotProduct [OK]
    TestVectorNorm [OK]
    TestVectorDistance [OK]
    TestPlaceNormal [OK]
    TestInitVectorList [OK]
    TestPushVector [OK]
    TestFreeVectorList [OK]
    TestPopVector [OK]
    TestRemoveLastVector [OK]
    TestTrimVectorList [OK]
    TestHomogeneousMatrix [OK]
    TestCreateScaleMatrix [OK]
    TestCreateTranslationMatrix [OK]
    TestCreateScaleAndTranslationMatrix [OK]
    TestCreateRotationMatrixX [OK]
    TestCreateRotationMatrixY [OK]
    TestCreateRotationMatrixZ [OK]
    TestCreateRotationMatrix [OK]
    TestMultiplyMatrix [OK]
    TestVectorTransform [OK]
    TestMatrixDeterminant [OK]
    TestAdjointMatrix [OK]
    TestScaleMatrix [OK]
    TestInvertMatrix [OK]
    TestTransposeMatrix [OK]
    TestLookAtMatrix [OK]


## Creator

sinan islekdemir | sinan@islekdemir.com 


## Note
I only compiled the code under MacOs so let me know if it works for you too.
