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
#include <ansic3d/matrix3d.h>

void HomogeneousMatrix(Matrix3D *matrix)
{
	SetVector(1, 0, 0, 0, &matrix->X);
	SetVector(0, 1, 0, 0, &matrix->Y);
	SetVector(0, 0, 1, 0, &matrix->Z);
	SetVector(0, 0, 0, 1, &matrix->W);
}

void EmptyMatrix(Matrix3D *matrix)
{
	SetVector(0, 0, 0, 0, &matrix->X);
	SetVector(0, 0, 0, 0, &matrix->Y);
	SetVector(0, 0, 0, 0, &matrix->Z);
	SetVector(0, 0, 0, 0, &matrix->W);
}

void CreateScaleMatrix(Vector3D v, Matrix3D *target)
{
	HomogeneousMatrix(target);
	target->X.x = v.x;
	target->Y.y = v.y;
	target->Z.z = v.z;
}

void CreateTranslationMatrix(Vector3D v, Matrix3D *target)
{
	HomogeneousMatrix(target);
	target->W.x = v.x;
	target->W.y = v.y;
	target->W.z = v.z;
}

void CreateScaleAndTranslationMatrix(Vector3D scale, Vector3D offset,
		Matrix3D *target)
{
	HomogeneousMatrix(target);
	target->X.x = scale.x;
	target->Y.y = scale.y;
	target->Z.z = scale.z;
	target->W.x = offset.x;
	target->W.y = offset.y;
	target->W.z = offset.z;
}

void CreateRotationMatrixXSinCos(float sin, float cos, Matrix3D *target)
{
	EmptyMatrix(target);
	target->X.x = 1;
	target->Y.y = cos;
	target->Y.z = sin;
	target->Z.y = -1 * sin;
	target->Z.z = cos;
	target->W.w = 1;
}

void CreateRotationMatrixX(float angle, Matrix3D *target)
{
	float c, s;
	c = cosf(angle);
	s = sinf(angle);
	CreateRotationMatrixXSinCos(s, c, target);
}

void CreateRotationMatrixYSinCos(float sin, float cos, Matrix3D *target)
{
	EmptyMatrix(target);
	target->X.x = cos;
	target->X.z = -1 * sin;
	target->Y.y = 1;
	target->Z.x = sin;
	target->Z.z = cos;
	target->W.w = 1;
}

void CreateRotationMatrixY(float angle, Matrix3D *target)
{
	float c, s;
	c = cosf(angle);
	s = sinf(angle);
	CreateRotationMatrixYSinCos(s, c, target);
}

void CreateRotationMatrixZSinCos(float sin, float cos, Matrix3D *target)
{
	EmptyMatrix(target);
	target->X.x = cos;
	target->X.y = sin;
	target->Y.x = -1 * sin;
	target->Y.y = cos;
	target->Z.z = 1;
	target->W.w = 1;
}

void CreateRotationMatrixZ(float angle, Matrix3D *target)
{
	float c, s;
	c = cosf(angle);
	s = sinf(angle);
	CreateRotationMatrixZSinCos(s, c, target);
}

void CreateRotationMatrix(Vector3D axis, float angle, Matrix3D *target)
{
	float cosine, sine, one_minus_cos;
	sine = sinf(angle);
	cosine = cosf(angle);
	NormalizeVector(&axis);
	one_minus_cos = 1 - cosine;

	target->X.x = (one_minus_cos * axis.x * axis.x) + cosine;
	target->X.y = (one_minus_cos * axis.x * axis.y) - (axis.z * sine);
	target->X.z = (one_minus_cos * axis.z * axis.x) + (axis.y * sine);
	target->X.w = 0;

	target->Y.x = (one_minus_cos * axis.x * axis.y) + (axis.z * sine);
	target->Y.y = (one_minus_cos * axis.y * axis.y) + cosine;
	target->Y.z = (one_minus_cos * axis.y * axis.z) - (axis.x * sine);
	target->Y.w = 0;

	target->Z.x = (one_minus_cos * axis.z * axis.x) - (axis.y * sine);
	target->Z.y = (one_minus_cos * axis.y * axis.z) + (axis.x * sine);
	target->Z.z = (one_minus_cos * axis.z * axis.z) + cosine;
	target->Z.w = 0;

	target->W.x = 0;
	target->W.y = 0;
	target->W.z = 0;
	target->W.w = 1;
}

void MultiplyMatrix(Matrix3D *m1, Matrix3D *m2, Matrix3D *target)
{
	target->X.x = (m1->X.x * m2->X.x + m1->X.y * m2->Y.x +
			m1->X.z * m2->Z.x + m1->X.w * m2->W.x);
	target->X.y = (m1->X.x * m2->X.y + m1->X.y * m2->Y.y +
			m1->X.z * m2->Z.y + m1->X.w * m2->W.y);
	target->X.z = (m1->X.x * m2->X.z + m1->X.y * m2->Y.z +
			m1->X.z * m2->Z.z + m1->X.w * m2->W.z);
	target->X.w = (m1->X.x * m2->X.w + m1->X.y * m2->Y.w +
			m1->X.z * m2->Z.w + m1->X.w * m2->W.w);
	target->Y.x = (m1->Y.x * m2->X.x + m1->Y.y * m2->Y.x +
			m1->Y.z * m2->Z.x + m1->Y.w * m2->W.x);
	target->Y.y = (m1->Y.x * m2->X.y + m1->Y.y * m2->Y.y +
			m1->Y.z * m2->Z.y + m1->Y.w * m2->W.y);
	target->Y.z = (m1->Y.x * m2->X.z + m1->Y.y * m2->Y.z +
			m1->Y.z * m2->Z.z + m1->Y.w * m2->W.z);
	target->Y.w = (m1->Y.x * m2->X.w + m1->Y.y * m2->Y.w +
			m1->Y.z * m2->Z.w + m1->Y.w * m2->W.w);
	target->Z.x = (m1->Z.x * m2->X.x + m1->Z.y * m2->Y.x +
			m1->Z.z * m2->Z.x + m1->Z.w * m2->W.x);
	target->Z.y = (m1->Z.x * m2->X.y + m1->Z.y * m2->Y.y +
			m1->Z.z * m2->Z.y + m1->Z.w * m2->W.y);
	target->Z.z = (m1->Z.x * m2->X.z + m1->Z.y * m2->Y.z +
			m1->Z.z * m2->Z.z + m1->Z.w * m2->W.z);
	target->Z.w = (m1->Z.x * m2->X.w + m1->Z.y * m2->Y.w +
			m1->Z.z * m2->Z.w + m1->Z.w * m2->W.w);
	target->W.x = (m1->W.x * m2->X.x + m1->W.y * m2->Y.x +
			m1->W.z * m2->Z.x + m1->W.w * m2->W.x);
	target->W.y = (m1->W.x * m2->X.y + m1->W.y * m2->Y.y +
			m1->W.z * m2->Z.y + m1->W.w * m2->W.y);
	target->W.z = (m1->W.x * m2->X.z + m1->W.y * m2->Y.z +
			m1->W.z * m2->Z.z + m1->W.w * m2->W.z);
	target->W.w = (m1->W.x * m2->X.w + m1->W.y * m2->Y.w +
			m1->W.z * m2->Z.w + m1->W.w * m2->W.w);
}

void VectorTransform(Matrix3D *matrix, Vector3D *target)
{
	Vector3D org;
	org.x = target->x;
	org.y = target->y;
	org.z = target->z;
	org.w = target->w;
	target->x = org.x * matrix->X.x + org.y * matrix->Y.x + org.z * matrix->Z.x + org.w * matrix->W.x;
	target->y = org.x * matrix->X.y + org.y * matrix->Y.y + org.z * matrix->Z.y + org.w * matrix->W.y;
	target->z = org.x * matrix->X.z + org.y * matrix->Y.z + org.z * matrix->Z.z + org.w * matrix->W.z;
	target->w = org.x * matrix->X.w + org.y * matrix->Y.w + org.z * matrix->Z.w + org.w * matrix->W.w;
}

float MatrixDeterminant(Matrix3D *matrix)
{
	float a, b, c, d;
	a = matrix->X.x * MatrixDetInternal(matrix->Y.y, matrix->Z.y, matrix->W.y,
			matrix->Y.z, matrix->Z.z, matrix->W.z,
			matrix->Y.w, matrix->Z.w, matrix->W.w);
	b = matrix->X.y * MatrixDetInternal(matrix->Y.x, matrix->Z.x, matrix->W.x,
			matrix->Y.z, matrix->Z.z, matrix->W.z,
			matrix->Y.w, matrix->Z.w, matrix->W.w);
	c = matrix->X.z * MatrixDetInternal(matrix->Y.x, matrix->Z.x, matrix->W.x,
			matrix->Y.y, matrix->Z.y, matrix->W.y,
			matrix->Y.w, matrix->Z.w, matrix->W.w);
	d = matrix->X.w * MatrixDetInternal(matrix->Y.x, matrix->Z.x, matrix->W.x,
			matrix->Y.y, matrix->Z.y, matrix->W.y,
			matrix->Y.z, matrix->Z.z, matrix->W.z);
	return a - b + c - d;
}

float MatrixDetInternal(float a1, float a2, float a3, float b1,
		float b2, float b3, float c1, float c2,
		float c3)
{
	return (a1 * ((b2 * c3) - (b3 * c2))) - (b1 * ((a2 * c3) - (a3 * c2))) + (c1 * ((a2 * b3) - (a3 * b2)));
}

void AdjointMatrix(Matrix3D *matrix)
{
	float a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
	a1 = matrix->X.x;
	b1 = matrix->X.y;
	c1 = matrix->X.z;
	d1 = matrix->X.w;

	a2 = matrix->Y.x;
	b2 = matrix->Y.y;
	c2 = matrix->Y.z;
	d2 = matrix->Y.w;

	a3 = matrix->Z.x;
	b3 = matrix->Z.y;
	c3 = matrix->Z.z;
	d3 = matrix->Z.w;

	a4 = matrix->W.x;
	b4 = matrix->W.y;
	c4 = matrix->W.z;
	d4 = matrix->W.w;

	matrix->X.x = MatrixDetInternal(b2, b3, b4, c2, c3, c4, d2, d3, d4);
	matrix->Y.x = -MatrixDetInternal(a2, a3, a4, c2, c3, c4, d2, d3, d4);
	matrix->Z.x = MatrixDetInternal(a2, a3, a4, b2, b3, b4, d2, d3, d4);
	matrix->W.x = -MatrixDetInternal(a2, a3, a4, b2, b3, b4, c2, c3, c4);

	matrix->X.y = -MatrixDetInternal(b1, b3, b4, c1, c3, c4, d1, d3, d4);
	matrix->Y.y = MatrixDetInternal(a1, a3, a4, c1, c3, c4, d1, d3, d4);
	matrix->Z.y = -MatrixDetInternal(a1, a3, a4, b1, b3, b4, d1, d3, d4);
	matrix->W.y = MatrixDetInternal(a1, a3, a4, b1, b3, b4, c1, c3, c4);

	matrix->X.z = MatrixDetInternal(b1, b2, b4, c1, c2, c4, d1, d2, d4);
	matrix->Y.z = -MatrixDetInternal(a1, a2, a4, c1, c2, c4, d1, d2, d4);
	matrix->Z.z = MatrixDetInternal(a1, a2, a4, b1, b2, b4, d1, d2, d4);
	matrix->W.z = -MatrixDetInternal(a1, a2, a4, b1, b2, b4, c1, c2, c4);

	matrix->X.w = -MatrixDetInternal(b1, b2, b3, c1, c2, c3, d1, d2, d3);
	matrix->Y.w = MatrixDetInternal(a1, a2, a3, c1, c2, c3, d1, d2, d3);
	matrix->Z.w = -MatrixDetInternal(a1, a2, a3, b1, b2, b3, d1, d2, d3);
	matrix->W.w = MatrixDetInternal(a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

void ScaleMatrix(Matrix3D *target, float factor)
{
	ScaleVector(&target->X, factor);
	ScaleVector(&target->Y, factor);
	ScaleVector(&target->Z, factor);
	ScaleVector(&target->W, factor);
}

void PrintMatrix(Matrix3D *matrix)
{
	printf("X: %20.10f i %20.10f j %20.10f k %20.10f l\n", matrix->X.x,
			matrix->X.y,
			matrix->X.z,
			matrix->X.z);
	printf("Y: %20.10f i %20.10f j %20.10f k %20.10f l\n", matrix->Y.x,
			matrix->Y.y,
			matrix->Y.z,
			matrix->Y.z);
	printf("Z: %20.10f i %20.10f j %20.10f k %20.10f l\n", matrix->Z.x,
			matrix->Z.y,
			matrix->Z.z,
			matrix->Z.w);
	printf("W: %20.10f i %20.10f j %20.10f k %20.10f l\n", matrix->W.x,
			matrix->W.y,
			matrix->W.z,
			matrix->W.w);
}

void InvertMatrix(Matrix3D *matrix)
{
	float det;
	det = MatrixDeterminant(matrix);
	if (fabs(det) < EPSILON)
	{
		HomogeneousMatrix(matrix);
	}
	else
	{
		AdjointMatrix(matrix);
		ScaleMatrix(matrix, 1.0 / det);
	}
}

void TransposeMatrix(Matrix3D *matrix)
{
	float f;
	f = matrix->X.y;
	matrix->X.y = matrix->Y.x;
	matrix->Y.x = f;

	f = matrix->X.z;
	matrix->X.z = matrix->Z.x;
	matrix->Z.x = f;

	f = matrix->X.w;
	matrix->X.w = matrix->W.x;
	matrix->W.x = f;

	f = matrix->Y.z;
	matrix->Y.z = matrix->Z.y;
	matrix->Z.y = f;

	f = matrix->Y.w;
	matrix->Y.w = matrix->W.y;
	matrix->W.y = f;

	f = matrix->Z.w;
	matrix->Z.w = matrix->W.z;
	matrix->W.z = f;
}

void LookAtMatrix(Vector3D eye,
		Vector3D target,
		Vector3D up, Matrix3D *matrix)
{
	Vector3D x_axis, y_axis, z_axis, neg_eye;
	SubVector(target, eye, &z_axis);
	NormalizeVector(&z_axis);

	CrossProduct(z_axis, up, &x_axis);
	NormalizeVector(&x_axis);

	CrossProduct(x_axis, z_axis, &y_axis);

	CloneVector(x_axis, &matrix->X);
	CloneVector(y_axis, &matrix->Y);
	CloneVector(z_axis, &matrix->Z);

	matrix->Z.x = -matrix->Z.x;
	matrix->Z.y = -matrix->Z.y;
	matrix->Z.z = -matrix->Z.z;

	SetVector(0, 0, 0, 1, &matrix->W);

	TransposeMatrix(matrix);
	SetVector(-eye.x, -eye.y, -eye.z, 1, &neg_eye);

	VectorTransform(matrix, &neg_eye);
	CloneVector(neg_eye, &matrix->W);
}

int MatrixEquals(Matrix3D *m1, Matrix3D *m2)
{
	return VectorEquals(m1->X, m2->X) && VectorEquals(m1->Y, m2->Y) &&
		VectorEquals(m1->Z, m2->Z) && VectorEquals(m1->W, m2->W);
}

void CastFloat(Matrix3D *m, float *f)
{
	f[0] = m->X.x;
	f[1] = m->X.y;
	f[2] = m->X.z;
	f[3] = m->X.w;
	f[4] = m->Y.x;
	f[5] = m->Y.y;
	f[6] = m->Y.z;
	f[7] = m->Y.w;
	f[8] = m->Z.x;
	f[9] = m->Z.y;
	f[10] = m->Z.z;
	f[11] = m->Z.w;
	f[12] = m->W.x;
	f[13] = m->W.y;
	f[14] = m->W.z;
	f[15] = m->W.w;
}
