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
#include <ansic3d/vector3d.h>
#define EPSILON 1E-40

typedef struct _Matrix3D
{
    Vector3D X, Y, Z, W;
} Matrix3D;

void HomogeneousMatrix(Matrix3D *matrix);
void EmptyMatrix(Matrix3D *matrix);
void CreateScaleMatrix(Vector3D v, Matrix3D *target);
void CreateTranslationMatrix(Vector3D v, Matrix3D *target);
void CreateScaleAndTranslationMatrix(Vector3D scale, Vector3D offset,
                                     Matrix3D *target);

void CreateRotationMatrixXSinCos(float sin, float cos, Matrix3D *target);
void CreateRotationMatrixX(float angle, Matrix3D *target);

void CreateRotationMatrixYSinCos(float sin, float cos, Matrix3D *target);
void CreateRotationMatrixY(float angle, Matrix3D *target);

void CreateRotationMatrixZSinCos(float sin, float cos, Matrix3D *target);
void CreateRotationMatrixZ(float angle, Matrix3D *target);

void CreateRotationMatrix(Vector3D axis, float angle, Matrix3D *target);

void MultiplyMatrix(Matrix3D m1, Matrix3D m2, Matrix3D *target);
void VectorTransform(Matrix3D matrix, Vector3D *target);

float MatrixDeterminant(Matrix3D matrix);
float MatrixDetInternal(float a1, float a2, float a3, float b1,
                         float b2, float b3, float c1, float c2,
                         float c3);
void AdjointMatrix(Matrix3D *matrix);
void ScaleMatrix(Matrix3D *target, float factor);
void PrintMatrix(Matrix3D matrix);
void InvertMatrix(Matrix3D *matrix);
void TransposeMatrix(Matrix3D *matrix);
void LookAtMatrix(Vector3D eye,
                  Vector3D target,
                  Vector3D up, Matrix3D *matrix);

#endif
