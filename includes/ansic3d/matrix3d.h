/*
    AnsiC3D - 3D Math Library
    Copyright (C) 2018  Sinan ISLEKDEMIR - sinan@islekdemir.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <stdio.h>
#include <stdlib.h>
#include <ansic3d/vector3d.h>
#define EPSILON 1E-40

typedef struct _Matrix3D
{
    Vector3D X, Y, Z, W;
} Matrix3D;

/**
 * HomogeneousMatrix
 * Creates a 4x4 Homogenous matrix to work with OpenGL or other
 * libraries to define the cartesian coordinates and orientation of a point
 *     1 0 0 0 --> Left Vector
 *     0 1 0 0 --> Direction Vector
 *     0 0 1 0 --> Up Vector
 *     0 0 0 1 --> Position Vector
 */
void HomogeneousMatrix(Matrix3D *matrix);

/**
 * Creates a 4x4 empty Matrix
 *     1 0 0 0 --> Left Vector
 *     0 1 0 0 --> Direction Vector
 *     0 0 1 0 --> Up Vector
 *     0 0 0 1 --> Position Vector
 */
void EmptyMatrix(Matrix3D *matrix);

/**
 * Create a scale matrix to let environment know the scale factor
 * and apply the scaling on the property
 */
void CreateScaleMatrix(Vector3D v, Matrix3D *target);

/**
 * Create a matrix to change the location of a property
 * This is basically a Homogeneous Matrix except a set position vector
 */
void CreateTranslationMatrix(Vector3D v, Matrix3D *target);

/**
 * A combination of functions - CreateScaleMatrix & CreateTranslationMatrix
 * Creates a Homogeneous Matrix and modifies Scale and Position vectors
 */
void CreateScaleAndTranslationMatrix(Vector3D scale, Vector3D offset,
                                     Matrix3D *target);

/**
 * Create a Rotation Matrix to rotate a vector around X Axis by Sin and Cos
 */
void CreateRotationMatrixXSinCos(float sin, float cos, Matrix3D *target);

/**
 * Create a Rotation Matrix to rotate a vector around X Axis
 */
void CreateRotationMatrixX(float angle, Matrix3D *target);

/**
 * Create a Rotation Matrix to rotate a vector around Y Axis by Sin and Cos
 */
void CreateRotationMatrixYSinCos(float sin, float cos, Matrix3D *target);

/**
 * Create a Rotation Matrix to rotate a vector around Y Axis
 */
void CreateRotationMatrixY(float angle, Matrix3D *target);

/**
 * Create a Rotation Matrix to rotate a vector around Z Axis by Sin and Cos
 */
void CreateRotationMatrixZSinCos(float sin, float cos, Matrix3D *target);

/**
 * Create a Rotation Matrix to rotate a vector around Z Axis
 */
void CreateRotationMatrixZ(float angle, Matrix3D *target);

/**
 * Create Rotation Matrix around a given axis Vector by a given angle
 */
void CreateRotationMatrix(Vector3D axis, float angle, Matrix3D *target);

/**
 * Multiply two 4x4 matrices.
 */
void MultiplyMatrix(Matrix3D *m1, Matrix3D *m2, Matrix3D *target);

/**
 * Vector Transform for given matrix
 */
void VectorTransform(Matrix3D *matrix, Vector3D *target);

/**
 * Calculate the scaling factor of the linear transformation described by the 
 * matrix. (https://en.wikipedia.org/wiki/Determinant)
 */
float MatrixDeterminant(Matrix3D *matrix);

/**
 * Calculate partial Determinant for MatrixDeterminant function
 */
float MatrixDetInternal(float a1, float a2, float a3, float b1,
                        float b2, float b3, float c1, float c2,
                        float c3);

/**
 * The adjoint of a matrix A is the transpose of the cofactor matrix of A. 
 * It is denoted by adj A .
 * https://www.varsitytutors.com/hotmath/hotmath_help/topics/adjoint-of-a-matrix
 */
void AdjointMatrix(Matrix3D *matrix);

/**
 * Scale a matrix by given factor.
 */
void ScaleMatrix(Matrix3D *target, float factor);

/**
 * A simple printf wrapper for debugging
 */
void PrintMatrix(Matrix3D *matrix);

/**
 * Invert the given matrix
 */
void InvertMatrix(Matrix3D *matrix);

/**
 * The transpose of a matrix is an operator which flips a matrix over its
 * diagonal. (https://en.wikipedia.org/wiki/Transpose)
 */
void TransposeMatrix(Matrix3D *matrix);

/**
 * Create a look at matrix to position a camera
 */
void LookAtMatrix(Vector3D eye,
                  Vector3D target,
                  Vector3D up, Matrix3D *matrix);
/**
 * Check if two matrixes are equal
 */
int MatrixEquals(Matrix3D *m1, Matrix3D *m2);

/**
 * Convert matrix to Float array [4][4]
 * Compilers are "allowed" to add padding on structs therefore
 * casting Matrix3D struct to Float* might result to undefined behaviour.
 * Important!!
 * Target float MUST BE initialized with 16 size before this stage.
 */
void CastFloat(Matrix3D *m, float *f);

#endif
