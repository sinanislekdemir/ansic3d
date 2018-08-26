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

/**
 * PRECISION is used for fixing equality checks.
 * All variables within this library is Float as most video graphic cards
 * are optimized for floats. But downside of floats is the precision, which
 * makes them too hard to check for equality condition.
 * Precision constant is the limit where two floats in VectorEquals function
 * can get near. If the diff of two floats is smaller than the precision,
 * they are considered to be equal.
 */
#define PRECISION 0.000001

typedef struct _Vector3d
{
    float x, y, z, w;
} Vector3D;

/**
 * target = p1 + p2
 */
void AddVector(Vector3D p1, Vector3D p2, Vector3D *target);

/**
 * target = p1 - p2
 */
void SubVector(Vector3D p1, Vector3D p2, Vector3D *target);

/**
 * target.x|y|z = target.x|y|z / factor
 */
void ScaleVector(Vector3D *target, float factor);

/**
 * the cross product CrossProduct(v1, v2), is a vector that is perpendicular 
 * to both v1 and v2  and thus normal to the plane containing them.
 * (https://en.wikipedia.org/wiki/Cross_product)
 */
void CrossProduct(Vector3D v1, Vector3D v2, Vector3D *target);

/**
 * Normalized Vector is the vector V1 still in the same direction but 1 as
 * vector length
 */
void NormalizeVector(Vector3D *target);

/**
 * vector.x|y|z = vector.x|y|z / divider.x|y|z relatively
 */
void DivideVector(Vector3D *vector, Vector3D divider);

/**
 * |\
 * | \
 * L__\   for two given vectors, perpendicular vector is the one
 *        perpendicular to two
 */
void PerpendicularVector(Vector3D v1, Vector3D v2, Vector3D *target);

/**
 * Rotate given vector around axis vector (1i, 0j, 0k)
 */
void RotateAroundX(Vector3D *target, float angle);

/**
 * Rotate given vector around axis vector (0i, 1j, 0k)
 */
void RotateAroundY(Vector3D *target, float angle);

/**
 * Rotate given vector around axis vector (0i, 0j, 1k)
 */
void RotateAroundZ(Vector3D *target, float angle);

/**
 * Set Vector
 */
void SetVector(float x, float y, float z, float w, Vector3D *target);

/**
 * Copy the vector properties to target
 */
void CloneVector(Vector3D from, Vector3D *to);

/**
 * Print vector to stdio
 */
void PrintVector(Vector3D v);

/**
 * Calculate the length of given vector
 */
float VectorLength(Vector3D vector);

/**
 * Dot product of two vectors
 * In modern geometry, Euclidean spaces are often defined by using vector 
 * spaces. In this case, the dot product is used for defining lengths 
 * (the length of a vector is the square root of the dot product of the 
 * vector by itself) and angles (the cosine of the angle of two vectors is 
 * the quotient of their dot product by the product of their lengths).
 * (https://en.wikipedia.org/wiki/Dot_product)
 */
float DotProduct(Vector3D v1, Vector3D v2);

/**
 * a norm is a function that assigns a strictly positive length or size to
 * each vector in a vector space—save for the zero vector, which is assigned
 * a length of zero. 
 * (https://en.wikipedia.org/wiki/Norm_(mathematics))
 */
float VectorNorm(Vector3D vector);

/**
 * Distance from Vector V1 to V2
 */
float VectorDistance(Vector3D v1, Vector3D v2);

float rsqrt(float n);

/**
 * v1 == v2
 * returns 1 if True, 0 if False
 */
int VectorEquals(Vector3D v1, Vector3D v2);

/**
 * Calculate the normal vector for the plane defined by V1, V2, V3
 */
void PlaneNormal(Vector3D v1, Vector3D v2, Vector3D v3, Vector3D *result);
#endif
