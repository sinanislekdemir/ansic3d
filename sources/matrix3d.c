#include <ansic3d/vector3d.h>
#include <ansic3d/matrix3d.h>

/**
 * HomogeneousMatrix
 * Creates a 4x4 Homogenous matrix to work with OpenGL or other
 * libraries to define the cartesian coordinates and orientation of a point
 *     1 0 0 0 --> Left Vector
 *     0 1 0 0 --> Direction Vector
 *     0 0 1 0 --> Up Vector
 *     0 0 0 1 --> Position Vector
 */
void HomogeneousMatrix(Matrix3D * matrix)
{
    SetVector(1, 0, 0, 0, &matrix->X);
    SetVector(0, 1, 0, 0, &matrix->Y);
    SetVector(0, 0, 1, 0, &matrix->Z);
    SetVector(0, 0, 0, 1, &matrix->W);
}

/**
 * EmptyMatrix
 * Creates a 4x4 empty Matrix
 *     1 0 0 0 --> Left Vector
 *     0 1 0 0 --> Direction Vector
 *     0 0 1 0 --> Up Vector
 *     0 0 0 1 --> Position Vector
 */
void EmptyMatrix(Matrix3D * matrix)
{
    SetVector(0, 0, 0, 0, &matrix->X);
    SetVector(0, 0, 0, 0, &matrix->Y);
    SetVector(0, 0, 0, 0, &matrix->Z);
    SetVector(0, 0, 0, 0, &matrix->W);
}

/**
 * CreateScaleMatrix
 * Create a scale matrix to let environment know the scale factor
 * and apply the scaling on the property
 */
void CreateScaleMatrix(Vector3D v, Matrix3D * target)
{
    HomogeneousMatrix(target);
    target->X.x = v.x;
    target->Y.y = v.y;
    target->Z.z = v.z;
}

/**
 * CreateTranslationMatrix
 * Create a matrix to change the location of a property
 * This is basically a Homogeneous Matrix except a set position vector
 */
void CreateTranslationMatrix(Vector3D v, Matrix3D * target)
{
    HomogeneousMatrix(target);
    target->W.x = v.x;
    target->W.y = v.y;
    target->W.z = v.z;
}


void CreateScaleAndTranslationMatrix(Vector3D scale, Vector3D offset,
                                     Matrix3D * target)
{
    HomogeneousMatrix(target);
    target->X.x = scale.x;
    target->W.x = offset.x;
    target->Y.y = scale.y;
    target->W.y = offset.y;
    target->Z.z = scale.z;
    target->W.z = offset.z;
}


void CreateRotationMatrixXSinCos(double sin, double cos, Matrix3D * target)
{
    EmptyMatrix(target);
    target->X.x = 1;
    target->Y.y = cos;
    target->Y.z = sin;
    target->Z.y = -1 * sin;
    target->Z.z = cos;
    target->W.w = 1;
}


void CreateRotationMatrixX(double angle, Matrix3D * target)
{
    double c, s;
    c = cos(angle);
    s = sin(angle);
    CreateRotationMatrixXSinCos(s, c, target);
}


void CreateRotationMatrixYSinCos(double sin, double cos, Matrix3D * target)
{
    EmptyMatrix(target);
    target->X.x = cos;
    target->X.z = -1 * sin;
    target->Y.y = 1;
    target->Z.x = sin;
    target->Z.z = cos;
    target->W.w = 1;
}


void CreateRotationMatrixY(double angle, Matrix3D * target)
{
    double c, s;
    c = cos(angle);
    s = sin(angle);
    CreateRotationMatrixYSinCos(s, c, target);
}


void CreateRotationMatrixZSinCos(double sin, double cos, Matrix3D * target)
{
    EmptyMatrix(target);
    target->X.x = cos;
    target->X.y = sin;
    target->Y.x = -1 * sin;
    target->Y.y = cos;
    target->Z.z = 1;
    target->W.w = 1;
}


void CreateRotationMatrixZ(double angle, Matrix3D * target)
{
    double c, s;
    c = cos(angle);
    s = sin(angle);
    CreateRotationMatrixZSinCos(s, c, target);
}


void CreateRotationMatrix(Vector3D axis, double angle, Matrix3D * target)
{
    double cosine, sine, one_minus_cos;
    sine = sin(angle);
    cosine = cos(angle);
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


void MultiplyMatrix(Matrix3D m1, Matrix3D m2, Matrix3D * target)
{
  target->X.x = (m1.X.x * m2.X.x + m1.X.y * m2.Y.x +
                    m1.X.z * m2.Z.x + m1.X.w * m2.W.x);
  target->X.y = (m1.X.x * m2.X.y + m1.X.y * m2.Y.y +
                    m1.X.z * m2.Z.y + m1.X.w * m2.W.y);
  target->X.z = (m1.X.x * m2.X.z + m1.X.y * m2.Y.z +
                    m1.X.z * m2.Z.z + m1.X.w * m2.W.z);
  target->X.w = (m1.X.x * m2.X.w + m1.X.y * m2.Y.w +
                    m1.X.z * m2.Z.w + m1.X.w * m2.W.w);
  target->Y.x = (m1.Y.x * m2.X.x + m1.Y.y * m2.Y.x +
                   m1.Y.z * m2.Z.x + m1.Y.w * m2.W.x);
  target->Y.y = (m1.Y.x * m2.X.y + m1.Y.y * m2.Y.y +
                   m1.Y.z * m2.Z.y + m1.Y.w * m2.W.y);
  target->Y.z = (m1.Y.x * m2.X.z + m1.Y.y * m2.Y.z +
                   m1.Y.z * m2.Z.z + m1.Y.w * m2.W.z);
  target->Y.w = (m1.Y.x * m2.X.w + m1.Y.y * m2.Y.w +
                   m1.Y.z * m2.Z.w + m1.Y.w * m2.W.w);
  target->Z.x = (m1.Z.x * m2.X.x + m1.Z.y * m2.Y.x +
                  m1.Z.z * m2.Z.x + m1.Z.w * m2.W.x);
  target->Z.y = (m1.Z.x * m2.X.y + m1.Z.y * m2.Y.y +
                  m1.Z.z * m2.Z.y + m1.Z.w * m2.W.y);
  target->Z.z = (m1.Z.x * m2.X.z + m1.Z.y * m2.Y.z +
                  m1.Z.z * m2.Z.z + m1.Z.w * m2.W.z);
  target->Z.w = (m1.Z.x * m2.X.w + m1.Z.y * m2.Y.w +
                  m1.Z.z * m2.Z.w + m1.Z.w * m2.W.w);
  target->W.x = (m1.W.x * m2.X.x + m1.W.y * m2.Y.x +
                   m1.W.z * m2.Z.x + m1.W.w * m2.W.x);
  target->W.y = (m1.W.x * m2.X.y + m1.W.y * m2.Y.y +
                   m1.W.z * m2.Z.y + m1.W.w * m2.W.y);
  target->W.z = (m1.W.x * m2.X.z + m1.W.y * m2.Y.z +
                   m1.W.z * m2.Z.z + m1.W.w * m2.W.z);
  target->W.w = (m1.W.x * m2.X.w + m1.W.y * m2.Y.w +
                   m1.W.z * m2.Z.w +m1.W.w * m2.W.w);
}


void VectorTransform(Matrix3D matrix, Vector3D * target)
{
    Vector3D org;
    org.x = target->x;
    org.y = target->y;
    org.z = target->z;
    target->x = org.x * matrix.X.x + org.y * matrix.Y.x + org.z * matrix.Z.x + org.w * matrix.W.x;
    target->y = org.x * matrix.X.y + org.y * matrix.Y.y + org.z * matrix.Z.y + org.w * matrix.W.y;
    target->z = org.x * matrix.X.z + org.y * matrix.Y.z + org.z * matrix.Z.z + org.w * matrix.W.z;
    target->w = org.x * matrix.X.w + org.y * matrix.Y.w + org.z * matrix.Z.w + org.w * matrix.W.w;
}


double MatrixDeterminant(Matrix3D matrix)
{
    double a, b, c, d;
    a = matrix.X.x * MatrixDetInternal(matrix.Y.y, matrix.Z.y, matrix.W.y,
                                       matrix.Y.z, matrix.Z.z, matrix.W.z,
                                       matrix.Y.w, matrix.Z.w, matrix.W.w);
    b = matrix.X.y * MatrixDetInternal(matrix.Y.x, matrix.Z.x, matrix.W.x,
                                       matrix.Y.z, matrix.Z.z, matrix.W.z,
                                       matrix.Y.w, matrix.Z.w, matrix.W.w);
    c = matrix.X.z * MatrixDetInternal(matrix.Y.x, matrix.Z.x, matrix.W.x,
                                       matrix.Y.y, matrix.Z.y, matrix.W.y,
                                       matrix.Y.w, matrix.Z.w, matrix.W.w);
    d = matrix.X.w * MatrixDetInternal(matrix.Y.x, matrix.Z.x, matrix.W.x,
                                       matrix.Y.y, matrix.Z.y, matrix.W.y,
                                       matrix.Y.z, matrix.Z.z, matrix.W.z);
    return a - b + c - d;
}


double MatrixDetInternal(double a1, double a2, double a3, double b1,
                         double b2, double b3, double c1, double c2,
                         double c3)
{
    return a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 *
        (a2 * b3 - a3 * b2);
}


void AdjointMatrix(Matrix3D * matrix)
{
    double a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;
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


void ScaleMatrix(Matrix3D * target, double factor)
{
    ScaleVector(&target->X, factor);
    ScaleVector(&target->Y, factor);
    ScaleVector(&target->Z, factor);
    ScaleVector(&target->W, factor);
}


void PrintMatrix(Matrix3D matrix)
{
    printf("X: %20.4f i %20.4f j %20.4f k %20.4f l\n", matrix.X.x,
                                                       matrix.X.y,
                                                       matrix.X.z,
                                                       matrix.X.z);
    printf("Y: %20.4f i %20.4f j %20.4f k %20.4f l\n", matrix.Y.x,
                                                       matrix.Y.y,
                                                       matrix.Y.z,
                                                       matrix.Y.z);
    printf("Z: %20.4f i %20.4f j %20.4f k %20.4f l\n", matrix.Z.x,
                                                       matrix.Z.y,
                                                       matrix.Z.z,
                                                       matrix.Z.w);
    printf("W: %20.4f i %20.4f j %20.4f k %20.4f l\n", matrix.W.x,
                                                       matrix.W.y,
                                                       matrix.W.z,
                                                       matrix.W.w);
}


void InvertMatrix(Matrix3D * matrix)
{
    double det;
    det = MatrixDeterminant(*matrix);
    if(fabs(det) < EPSILON)
    {
        HomogeneousMatrix(matrix);
    }else{
        AdjointMatrix(matrix);
        ScaleMatrix(matrix, 1.0 / det);
    }
}


void TransposeMatrix(Matrix3D * matrix)
{
    double f;
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
    matrix->Z.w = matrix->W.z;
    matrix->W.z = f;
}


void LookAtMatrix(Vector3D eye,
                  Vector3D target,
                  Vector3D up, Matrix3D * matrix)
{
    Vector3D x_axis, y_axis, z_axis;
    SubVector(eye, target, &z_axis);
    NormalizeVector(&z_axis);
    CrossProduct(up, z_axis, &x_axis);
    NormalizeVector(&x_axis);
    CrossProduct(z_axis, x_axis, &y_axis);
    CloneVector(x_axis, &matrix->X);
    CloneVector(y_axis, &matrix->Y);
    CloneVector(z_axis, &matrix->Z);
    SetVector(eye.x, eye.y, eye.z, 1, &matrix->W);
}
