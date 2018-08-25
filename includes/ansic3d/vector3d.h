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
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <stdio.h>

#define degtorad(def) (def * M_PI / 180.0)
#define radtodeg(rad) (rad * 180.0 / M_PI)

typedef struct _Vector3d
{
    double x, y, z, w;
} Vector3D;

void AddVector(Vector3D p1, Vector3D p2, Vector3D *target);
void SubVector(Vector3D p1, Vector3D p2, Vector3D *target);
void ScaleVector(Vector3D *target, double factor);
void CrossProduct(Vector3D v1, Vector3D v2, Vector3D *target);
void NormalizeVector(Vector3D *target);
void DivideVector(Vector3D *vector, Vector3D divider);
void PerpendicularVector(Vector3D v1, Vector3D v2, Vector3D *target);
void RotateAroundX(Vector3D *target, double angle);
void RotateAroundY(Vector3D *target, double angle);
void RotateAroundZ(Vector3D *target, double angle);
void SetVector(double x, double y, double z, double w, Vector3D *target);
void CloneVector(Vector3D from, Vector3D *to);
void PrintVector(Vector3D v);

double VectorLength(Vector3D vector);
double DotProduct(Vector3D v1, Vector3D v2);
double VectorNorm(Vector3D vector);
double VectorDistance(Vector3D v1, Vector3D v2);

double rsqrt(double n);
int VectorEquals(Vector3D v1, Vector3D v2);

void PlaneNormal(Vector3D v1, Vector3D v2, Vector3D v3, Vector3D *result);
#endif
