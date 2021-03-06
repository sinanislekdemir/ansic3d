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
#include <ansic3d/vector3d.h>

void CloneVector(Vector3D from, Vector3D *to)
{
	SetVector(from.x, from.y, from.z, from.w, to);
}

void AddVector(Vector3D p1, Vector3D p2, Vector3D *target)
{
	target->x = p1.x + p2.x;
	target->y = p1.y + p2.y;
	target->z = p1.z + p2.z;
}

void SubVector(Vector3D p1, Vector3D p2, Vector3D *target)
{
	target->x = p1.x - p2.x;
	target->y = p1.y - p2.y;
	target->z = p1.z - p2.z;
}

void ScaleVector(Vector3D *target, float factor)
{
	target->x *= factor;
	target->y *= factor;
	target->z *= factor;
	target->w *= factor;
}

void CrossProduct(Vector3D v1, Vector3D v2, Vector3D *target)
{
	target->x = v1.y * v2.z - v1.z * v2.y;
	target->y = v1.z * v2.x - v1.x * v2.z;
	target->z = v1.x * v2.y - v1.y * v2.x;
}

void NormalizeVector(Vector3D *target)
{
	float invlen;
	float vn;
	vn = VectorNorm(*target);
	if (vn != 0)
	{
		invlen = 1 / vn;
		target->x = target->x * invlen;
		target->y = target->y * invlen;
		target->z = target->z * invlen;
		target->w = 0;
	}
}

void DivideVector(Vector3D *vector, Vector3D divider)
{
	vector->x = vector->x / divider.x;
	vector->y = vector->y / divider.y;
	vector->z = vector->z / divider.z;
}

void PerpendicularVector(Vector3D v1, Vector3D v2, Vector3D *target)
{
	float dot = DotProduct(v1, v2);
	target->x = v1.x - dot * v2.x;
	target->y = v1.y - dot * v2.y;
	target->z = v1.z - dot * v2.z;
}

void RotateAroundX(Vector3D *target, float angle)
{
	Vector3D org;
	float s, c;
	s = sin(angle);
	c = cos(angle);
	org.x = target->x;
	org.y = target->y;
	org.z = target->z;
	target->y = c * org.y + s * org.z;
	target->z = c * org.z - s * org.y;
}

void RotateAroundY(Vector3D *target, float angle)
{
	Vector3D org;
	float s, c;
	s = sin(angle);
	c = cos(angle);
	org.x = target->x;
	org.y = target->y;
	org.z = target->z;
	target->x = c * org.x + s * org.z;
	target->z = c * org.z - s * org.x;
}

void RotateAroundZ(Vector3D *target, float angle)
{
	Vector3D org;
	float s, c;
	s = sin(angle);
	c = cos(angle);
	org.x = target->x;
	org.y = target->y;
	org.z = target->z;
	target->x = c * org.x + s * org.y;
	target->y = c * org.y - s * org.x;
}

void SetVector(float x, float y, float z, float w, Vector3D *target)
{
	target->x = x;
	target->y = y;
	target->z = z;
	target->w = w;
}

float VectorLength(Vector3D vector)
{
	return sqrtf((vector.x * vector.x) +
			(vector.y * vector.y) +
			(vector.z * vector.z));
}

float DotProduct(Vector3D v1, Vector3D v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float VectorNorm(Vector3D vector)
{
	return sqrtf((vector.x * vector.x) + 
			(vector.y * vector.y) +
			(vector.z * vector.z));
}

float VectorDistance(Vector3D v1, Vector3D v2)
{
	return sqrt(pow(v2.x - v1.x, 2) +
			pow(v2.y - v1.y, 2) +
			pow(v2.z - v1.z, 2));
}

float rsqrt(float n)
{
	return 1 / sqrt(n);
}

int VectorEquals(Vector3D v1, Vector3D v2)
{
	float x, y, z;
	x = fabsf(v1.x - v2.x);
	y = fabsf(v1.y - v2.y);
	z = fabsf(v1.z - v2.z);
	return (x < PRECISION && y < PRECISION && z < PRECISION);
}

void PrintVector(Vector3D v)
{
	printf("V: %20.10f i %20.10f j %20.10f k %20.10f l\n", v.x, v.y, v.z, v.w);
}

void PlaneNormal(Vector3D v1, Vector3D v2, Vector3D v3, Vector3D *result)
{
	Vector3D t1, t2;
	SubVector(v2, v1, &t1);
	SubVector(v3, v1, &t2);
	CrossProduct(t1, t2, result);
	NormalizeVector(result);
}
