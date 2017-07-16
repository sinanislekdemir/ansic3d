# Ansi C 3D Math Library


Some codes are derived from GLScene project (glscene.org)

I needed a basic ansi-c  3D library for another project of mine so I started
this project. I implemented my own needs within the library.

I tried to write comments as much as I can.


## Vector3D
Vector3D is a basic data structure which holds x, y, z and w information about
a point in space.

| Function | Parameters | Description |
| -------- | ---------- | ----------- |
| AddVector3D | p1, p2, target | Add p1 to p2 and write the results in target |
| SubVector3D | p1, p2, target | Substract p2 from p2 and write the results in target |
| ScaleVector | target, factor | Scale target vector by factor |
| CrossProduct | v1, v2, target | Calculate vector cross product and write the results in target |
| NormalizeVector3D | target | Normalize target vector (overwrites the target!) |
| DivideVector | vector, divider | Divide vector by divider vector (X1 = X1 / X2 ) |
| PerpendicularVector | v1, v2, target | Calculate perpendicular vector to v1 - v2 |
| RotateAroundX | target, angle | Rotate target vector around X axis by angle |
| RotateAroundY | target, angle | Rotate target vector around Y axis by angle |
| RotateAroundZ | target, angle | Rotate target vector around Z axis by angle |
| SetVector | x, y, z, w, target | Set vector variables |
| CloneVector | from, to | Clone vector variables from vector to vector |
| PrintVector | v | Simply printf vector variables for debugging |
| VectorLength | vector | Calculate vector length |
| DotProduct | v1, v2 | Calculate dot product of v1 x v2 |
| VectorNorm | vector | Calculate vector norm |
| VectorDistance | v1, v2 | Calculate distance from vector v1 to v2 |
| rsqrt | n | Private function that is used inside, 1 / sqrt (n) |
| VectorEquals | v1, v2 | Vector equality test, returns 1 if true else 0 |
| PlaneNormal | v1, v2, v3 | Plane normal for triangle v1, v2 , v3 |


## Matrix3D
Matrix3D is a simple 4x4 matrix structure which can be used in OpenGL operations
to identify an objects location and direction

| Function | Parameters | Description |
| -------- | ---------- | ----------- |
| HomogeneousMatrix | matrix | Reset matrix to a unit matrix |
| EmptyMatrix | matrix | Empty matrix and set all data to 0 |
| CreateScaleMatrix | v, target | Create scale matrix for vector v |
| CreateTranslationMatrix | v, target | Create translation matrix for vector v |
| CreateScaleAndTranslationMatrix | scale, offset, target | Create both scale and translation matrix|
| CreateRotationMatrixXSinCos | sin, cos, target | Create rotation matrix along X axis for sin - cos |
| CreateRotationMatrixX | angle, target | Create rotation matrix along X axis for angle |
| CreateRotationMatrixYSinCos | sin, cos, target | Create rotation matrix along Y axis for sin - cos |
| CreateRotationMatrixY | angle, target | Create rotation matrix along X axis for angle |
| CreateRotationMatrixZSinCos | sin, cos, target | Create rotation matrix along Z axis for sin - cos |
| CreateRotationMatrixZ | angle, target | Create rotation matrix along Z axis for angle |
| CreateRotationMatrix | axis, angle, target | Create rotation matrix along axis for given angle |
| MultiplyMatrix | m1, m2, target | Multiply matrix m1 with m2 and write to target |
| VectorTransform | matrix, target | Transform target vector by matrix |
| MatrixDeterminant | matrix | Calculate matrix determinant |
| AdjointMatrix | matrix | Adjoint given matrix |
| ScaleMatrix | target, factor | Scale matrix by factor |
| PrintMatrix | matrix | Simply printf matrix for debugging |
| InvertMatrix | matrix | Invert given matrix |
| LookAtMatrix | eye, target, up, matrix | Calculate look-at matrix for given eye position, to target with given up vector |


## VectorList
Vector list is a dynamic 3d vector array with simple functionalities

| Function | Parameters | Description |
| -------- | ---------- | ----------- |
| InitVectorList | list | Initialize the defined VectorList, must be called before using a VectorList |
| PushVector | v, list | Push vector to the end of array |
| PopVector | list, target | Pop the last item of the array into target vector and remove it from the VectorList |
| RemoveLastVector | list | Remove the last item of the array |
| RemoveVectorIndex | list, index | Remove the index given from the VectorList |
| FreeVectorList | list | Free VectorList memory, must be called to prevent possible leaks |

## Installing
You need bbee (https://github.com/sinanislekdemir/bbee) script in your PATH.

To compile the library:

    bbee

To install the library:

    bbee --install


To compile the tests

    bbee --i=test.json

Or just run to compule and install the library and run the tests.

    ./build.sh


## Creator

sinan islekdemir | sinan@islekdemir.com 


## Note
I only compiled the code under MacOs so let me know if it works for you too.
