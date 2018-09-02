#include <stdio.h>
#include <math.h>
#include <ansic3d/matrix3d.h>
#include <ansic3d/vector3d.h>
#include <ansic3d/vectorlist.h>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"

// Private function
void printOK(char *function_name)
{
    printf("%s %s[OK]%s\n", function_name, GREEN, NORMAL);
}

void printFAIL(char *function_name)
{
    printf("%s %s[FAIL]%s\n", function_name, RED, NORMAL);
}

int TestCloneVector()
{
    Vector3D v1, v2;
    SetVector(1, 2, 3, 1, &v1);
    CloneVector(v1, &v2);
    return VectorEquals(v1, v2);
}

int TestAddVector()
{
    Vector3D v1, v2, target, expect;
    SetVector(1, 1, 1, 1, &v1);
    SetVector(1, 2, 3, 1, &v2);
    SetVector(2, 3, 4, 1, &expect);
    AddVector(v1, v2, &target);
    return VectorEquals(target, expect);
}

int TestSubVector()
{
    Vector3D v1, v2, target, expect;
    SetVector(1, 1, 1, 1, &v1);
    SetVector(1, 2, 3, 1, &v2);
    SetVector(0, -1, -2, 1, &expect);
    SubVector(v1, v2, &target);
    return VectorEquals(target, expect);
}

int TestScaleVector()
{
    Vector3D vector, expect;
    SetVector(2, 2, 2, 1, &vector);
    SetVector(4, 4, 4, 2, &expect);
    ScaleVector(&vector, 2);
    return VectorEquals(vector, expect);
}

int TestCrossProduct()
{
    Vector3D v1, v2, target, expect;
    SetVector(1, 2, 1, 1, &v1);
    SetVector(3, 2, 4, 1, &v2);
    SetVector(6, -1, -4, 1, &expect);
    CrossProduct(v1, v2, &target);
    return VectorEquals(target, expect);
}

int TestNormalizeVector()
{
    Vector3D vector, expect;
    SetVector(3, 1, 5, 1, &vector);
    SetVector(0.5070925355, 0.1690308452, 0.8451542258, 1, &expect);
    NormalizeVector(&vector);
    return VectorEquals(expect, vector);
}

int TestDivideVector()
{
    Vector3D vector, divider, expect;
    SetVector(1, 1, 1, 1, &vector);
    SetVector(2, 2, 2, 1, &divider);
    SetVector(0.5, 0.5, 0.5, 1, &expect);
    DivideVector(&vector, divider);
    return VectorEquals(vector, expect);
}

int TestPerpendicularVector()
{
    Vector3D v1, v2, target, expect;
    SetVector(1, 0, 0, 1, &v1);
    SetVector(0, 1, 0, 1, &v2);
    SetVector(1, 0, 0, 1, &expect);
    PerpendicularVector(v1, v2, &target);
    return VectorEquals(target, expect);
}

int TestRotateAroundX()
{
    Vector3D vector, expect;
    SetVector(0, 1, 0, 1, &vector);
    SetVector(0, 0, -1, 1, &expect);
    RotateAroundX(&vector, degtorad(90));
    return VectorEquals(vector, expect);
}

int TestRotateAroundY()
{
    Vector3D vector, expect;
    SetVector(1, 0, 0, 1, &vector);
    SetVector(0, 0, -1, 1, &expect);
    RotateAroundY(&vector, degtorad(90));
    return VectorEquals(vector, expect);
}

int TestRotateAroundZ()
{
    Vector3D vector, expect;
    SetVector(1, 0, 0, 1, &vector);
    SetVector(0, -1, 0, 1, &expect);
    RotateAroundZ(&vector, degtorad(90));
    return VectorEquals(vector, expect);
}

int TestVectorLength()
{
    Vector3D vector;
    float length, expect;
    SetVector(3, 4, 5, 1, &vector);
    length = VectorLength(vector);
    expect = 7.0710678118654755;
    if (fabsf(expect - length) < PRECISION)
    {
        return 1;
    }
    return 0;
}

int TestDotProduct()
{
    Vector3D v1, v2;
    float product, expect;
    SetVector(1, 2, 3, 1, &v1);
    SetVector(1, 5, 7, 1, &v2);
    product = DotProduct(v1, v2);
    expect = 32;
    return fabsf(expect - product) < PRECISION;
}

int TestVectorNorm()
{
    Vector3D vector;
    float norm, expect;
    SetVector(2, 3, 5, 1, &vector);
    norm = VectorNorm(vector);
    expect = 6.164414002968976;
    return fabsf(expect - norm) < PRECISION;
}

int TestVectorDistance()
{
    Vector3D v1, v2;
    float distance, expect;
    SetVector(7, 4, 3, 1, &v1);
    SetVector(17, 6, 2, 1, &v2);
    distance = VectorDistance(v1, v2);
    expect = 10.246951;
    return fabsf(expect - distance) < PRECISION;
}

int TestPlaceNormal()
{
    Vector3D v1, v2, v3, target, expect;
    SetVector(0, 0, 0, 1, &v1);
    SetVector(1, 0, 0, 1, &v2);
    SetVector(1, 1, 0, 1, &v3);
    SetVector(0, 0, 1, 1, &expect);
    PlaneNormal(v1, v2, v3, &target);
    return VectorEquals(expect, target);
}

int TestInitVectorList()
{
    VectorList list;
    InitVectorList(&list, 10);
    if (list.capacity != 10)
    {
        return 0;
    }
    return 1;
}

int TestPushVector()
{
    VectorList list;
    Vector3D vector;
    unsigned int i;
    SetVector(1, 2, 3, 1, &vector);
    InitVectorList(&list, 10);
    PushVector(vector, &list);
    if (list.capacity != 10)
    {
        return 0;
    }
    if (list.index != 0)
    {
        return 0;
    }
    if (list.count != 1)
    {
        return 0;
    }
    // Exceed the capacity
    for (i = 0; i < 15; i++)
    {
        PushVector(vector, &list);
    }
    if (list.index != 15)
    {
        return 0;
    }
    if (list.capacity != 16)
    {
        return 0;
    }
    if (list.count != 16)
    {
        return 0;
    }
    return 1;
}

int TestFreeVectorList()
{
    VectorList list;
    Vector3D vector;
    SetVector(1, 2, 3, 1, &vector);
    InitVectorList(&list, 10);
    PushVector(vector, &list);
    FreeVectorList(&list);
    if (list.capacity != 0)
    {
        return 0;
    }
    if (list.count != 0)
    {
        return 0;
    }
    if (list.index != -1)
    {
        return 0;
    }
    return 1;
}

int TestPopVector()
{
    VectorList list;
    Vector3D vector;
    Vector3D target;
    SetVector(1, 2, 3, 1, &vector);
    InitVectorList(&list, 10);
    PushVector(vector, &list);
    PushVector(vector, &list);
    PopVector(&list, &target);
    if (VectorEquals(target, vector) == 0)
    {
        return 0;
    }
    if (list.count != 1)
    {
        return 0;
    }
    if (list.index != 0)
    {
        return 0;
    }
    return 1;
}

int TestRemoveLastVector()
{
    VectorList list;
    Vector3D vector;
    SetVector(1, 2, 3, 1, &vector);
    InitVectorList(&list, 10);
    PushVector(vector, &list);
    PushVector(vector, &list);
    RemoveLastVector(&list);
    if (list.count != 1)
    {
        return 0;
    }
    if (list.index != 0)
    {
        return 0;
    }
    if (list.capacity != 10)
    {
        return 0;
    }
    return 1;
}

int TestTrimVectorList()
{
    VectorList list;
    Vector3D vector;
    SetVector(1, 2, 3, 1, &vector);
    InitVectorList(&list, 10);
    PushVector(vector, &list);
    PushVector(vector, &list);
    TrimVectorList(&list);
    if (list.count != 2)
    {
        return 0;
    }
    if (list.index != 1)
    {
        return 0;
    }
    if (list.capacity != 2)
    {
        return 0;
    }
    return 1;
}

int TestHomogeneousMatrix()
{
    Matrix3D matrix, expect;
    SetVector(1, 0, 0, 0, &expect.X);
    SetVector(0, 1, 0, 0, &expect.Y);
    SetVector(0, 0, 1, 0, &expect.Z);
    SetVector(0, 0, 0, 1, &expect.W);
    HomogeneousMatrix(&matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestCreateScaleMatrix()
{
    Matrix3D matrix, expect;
    Vector3D scale;
    SetVector(2, 0, 0, 0, &expect.X);
    SetVector(0, 3, 0, 0, &expect.Y);
    SetVector(0, 0, 4, 0, &expect.Z);
    SetVector(0, 0, 0, 1, &expect.W);
    SetVector(2, 3, 4, 1, &scale);
    CreateScaleMatrix(scale, &matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestCreateTranslationMatrix()
{
    Matrix3D matrix, expect;
    Vector3D translation;
    SetVector(1, 0, 0, 0, &expect.X);
    SetVector(0, 1, 0, 0, &expect.Y);
    SetVector(0, 0, 1, 0, &expect.Z);
    SetVector(2, 3, 4, 1, &expect.W);
    SetVector(2, 3, 4, 1, &translation);
    CreateTranslationMatrix(translation, &matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestCreateScaleAndTranslationMatrix()
{
    Matrix3D matrix, expect;
    Vector3D scale, translation;
    SetVector(2, 0, 0, 0, &expect.X);
    SetVector(0, 3, 0, 0, &expect.Y);
    SetVector(0, 0, 4, 0, &expect.Z);
    SetVector(2, 3, 4, 1, &expect.W);
    SetVector(2, 3, 4, 1, &scale);
    SetVector(2, 3, 4, 1, &translation);
    CreateScaleAndTranslationMatrix(scale, translation, &matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestCreateRotationMatrixX()
{
    // This test also covers CreateRotationMatrixXSinCos
    Matrix3D target, expect;
    EmptyMatrix(&expect);
    SetVector(1, 0, 0, 0, &expect.X);
    SetVector(0, 0, -1, 0, &expect.Y);
    SetVector(0, 1, 0, 0, &expect.Z);
    SetVector(0, 0, 0, 1, &expect.W);
    CreateRotationMatrixX(degtorad(-90), &target);
    return MatrixEquals(&target, &expect);
}

int TestCreateRotationMatrixY()
{
    // This test also covers CreateRotationMatrixYSinCos
    Matrix3D target, expect;
    EmptyMatrix(&expect);
    SetVector(0, 0, 1, 0, &expect.X);
    SetVector(0, 1, 0, 0, &expect.Y);
    SetVector(-1, 0, 0, 0, &expect.Z);
    SetVector(0, 0, 0, 1, &expect.W);
    CreateRotationMatrixY(degtorad(-90), &target);
    return MatrixEquals(&target, &expect);
}

int TestCreateRotationMatrixZ()
{
    // This test also covers CreateRotationMatrixZSinCos
    Matrix3D target, expect;
    EmptyMatrix(&expect);
    SetVector(0, -1, 0, 0, &expect.X);
    SetVector(1, 0, 0, 0, &expect.Y);
    SetVector(0, 0, 1, 0, &expect.Z);
    SetVector(0, 0, 0, 1, &expect.W);
    CreateRotationMatrixZ(degtorad(-90), &target);
    return MatrixEquals(&target, &expect);
}

int TestCreateRotationMatrix()
{
    Matrix3D matrix, expect;
    Vector3D axis;
    EmptyMatrix(&expect);
    SetVector(0, 0, 1, 0, &axis);
    expect.X.y = -1;
    expect.Y.x = 1;
    expect.Z.z = 1;
    expect.W.w = 1;
    HomogeneousMatrix(&matrix);
    CreateRotationMatrix(axis, degtorad(90), &matrix);
    if (!MatrixEquals(&expect, &matrix))
    {
        return 0;
    }
    EmptyMatrix(&expect);
    SetVector(0, 1, 0, 0, &axis);
    HomogeneousMatrix(&matrix);
    expect.X.z = 1;
    expect.Y.y = 1;
    expect.Z.x = -1;
    expect.W.w = 1;
    CreateRotationMatrix(axis, degtorad(90), &matrix);
    if (!MatrixEquals(&expect, &matrix))
    {
        return 0;
    }
    EmptyMatrix(&expect);
    SetVector(1, 0, 0, 0, &axis);
    HomogeneousMatrix(&matrix);
    expect.X.x = 1;
    expect.Y.z = -1;
    expect.Z.y = 1;
    expect.W.w = 1;
    CreateRotationMatrix(axis, degtorad(90), &matrix);
    if (!MatrixEquals(&expect, &matrix))
    {
        return 0;
    }
    return 1;
}

int TestMultiplyMatrix()
{
    Matrix3D m1, m2, target, expect;
    HomogeneousMatrix(&m1);
    EmptyMatrix(&m2);
    SetVector(10, 5, 5, 1, &m1.W);
    SetVector(0, -1, 0, 0, &m2.X);
    SetVector(1, 0, 0, 0, &m2.Y);
    SetVector(0, 0, 1, 0, &m2.Z);
    SetVector(0, 0, 0, 1, &m2.W);
    SetVector(0, -1, 0, 0, &expect.X);
    SetVector(1, 0, 0, 0, &expect.Y);
    SetVector(0, 0, 1, 0, &expect.Z);
    SetVector(5, -10, 5, 1, &expect.W);
    MultiplyMatrix(&m1, &m2, &target);
    return MatrixEquals(&expect, &target);
}

int TestVectorTransform()
{
    Matrix3D matrix;
    Vector3D vector, expect;
    SetVector(10, 5, 5, 1, &vector);
    SetVector(5, -10, 5, 1, &expect);
    CreateRotationMatrixZ(degtorad(-90), &matrix);
    VectorTransform(&matrix, &vector);
    return VectorEquals(vector, expect);
}

int TestMatrixDeterminant()
{
    // This test also covers MatrixDetInternal
    Matrix3D matrix;
    float determinant, expect;
    HomogeneousMatrix(&matrix);
    SetVector(0, -1, 0, 0, &matrix.X);
    SetVector(1, 0, 0, 0, &matrix.Y);
    SetVector(0, 0, 1, 0, &matrix.Z);
    SetVector(5, 10, 10, 1, &matrix.W);
    determinant = MatrixDeterminant(&matrix);
    expect = 1;
    return fabsf(expect - determinant) < PRECISION;
}

int TestAdjointMatrix()
{
    Matrix3D matrix, expect;
    HomogeneousMatrix(&matrix);
    SetVector(0, -1, 0, 0, &matrix.X);
    SetVector(1, 0, 0, 0, &matrix.Y);
    SetVector(0, 0, 1, 0, &matrix.Z);
    SetVector(5, 10, 10, 1, &matrix.W);
    SetVector(0, 1, 0, 0, &expect.X);
    SetVector(-1, 0, 0, 0, &expect.Y);
    SetVector(0, 0, 1, 0, &expect.Z);
    SetVector(10, -5, -10, 1, &expect.W);
    AdjointMatrix(&matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestScaleMatrix()
{
    Matrix3D matrix, expect;
    SetVector(0, -1, 0, 0, &matrix.X);
    SetVector(1, 0, 0, 0, &matrix.Y);
    SetVector(0, 0, 1, 0, &matrix.Z);
    SetVector(5, 10, 10, 1, &matrix.W);

    SetVector(0, -1.0 / 3.0, 0, 0, &expect.X);
    SetVector(1.0 / 3.0, 0, 0, 0, &expect.Y);
    SetVector(0, 0, 1.0 / 3.0, 0, &expect.Z);
    SetVector(5.0 / 3.0, 10.0 / 3.0, 10.0 / 3.0, 1.0 / 3.0, &expect.W);
    ScaleMatrix(&matrix, 1.0 / 3.0);
    return MatrixEquals(&expect, &matrix);
}

int TestInvertMatrix()
{
    Matrix3D matrix, expect;
    SetVector(0, -1, 0, 0, &matrix.X);
    SetVector(1, 0, 0, 0, &matrix.Y);
    SetVector(0, 0, 1, 0, &matrix.Z);
    SetVector(5, 10, 10, 1, &matrix.W);

    SetVector(0, 1, 0, 0, &expect.X);
    SetVector(-1, 0, 0, 0, &expect.Y);
    SetVector(0, 0, 1, 0, &expect.Z);
    SetVector(10, -5, -10, 1, &expect.W);

    InvertMatrix(&matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestTransposeMatrix()
{
    Matrix3D matrix, expect;
    SetVector(0, -1, 0, 0, &matrix.X);
    SetVector(1, 0, 0, 0, &matrix.Y);
    SetVector(0, 0, 1, 0, &matrix.Z);
    SetVector(5, 10, 10, 1, &matrix.W);

    SetVector(0, 1, 0, 5, &expect.X);
    SetVector(-1, 0, 0, 10, &expect.Y);
    SetVector(0, 0, 1, 10, &expect.Z);
    SetVector(0, 0, 0, 1, &expect.W);

    TransposeMatrix(&matrix);
    return MatrixEquals(&matrix, &expect);
}

int TestLookAtMatrix()
{
    Vector3D eye, target, up;
    Matrix3D camera, expect;
    SetVector(10, 10, 10, 1, &eye);
    SetVector(0, 0, 0, 1, &target);
    SetVector(0, 0, 1, 0, &up);

    SetVector(-0.7071067691, 0.7071067691, 0, 0, &expect.X);
    SetVector(-0.4082482457, -0.4082482457, 0.8164964914, 0.8164964914, &expect.Y);
    SetVector(0.5773501992, 0.5773501992, 0.5773501992, 0, &expect.Z);
    SetVector(10, 10, 10, 1, &expect.W);

    LookAtMatrix(eye, target, up, &camera);
    return MatrixEquals(&camera, &expect);
}

int TestCastFloat()
{
    Matrix3D m;
    unsigned int i;
    float f[16] = {0};
    float expect[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    HomogeneousMatrix(&m);
    CastFloat(&m, f);
    for (i = 0; i < 16; i++)
    {
        if (fabsf(expect[i] - f[i]) > PRECISION)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    if (TestCloneVector())
    {
        printOK("TestCloneVector");
    }
    else
    {
        printFAIL("TestCloneVector");
    }
    if (TestAddVector())
    {
        printOK("TestAddVector");
    }
    else
    {
        printFAIL("TestAddVector");
    }
    if (TestSubVector())
    {
        printOK("TestSubVector");
    }
    else
    {
        printFAIL("TestSubVector");
    }
    if (TestScaleVector())
    {
        printOK("TestScaleVector");
    }
    else
    {
        printFAIL("TestScaleVector");
    }
    if (TestCrossProduct())
    {
        printOK("TestCrossProduct");
    }
    else
    {
        printFAIL("TestCrossProduct");
    }
    if (TestNormalizeVector())
    {
        printOK("TestNormalizeVector");
    }
    else
    {
        printFAIL("TestNormalizeVector");
    }
    if (TestDivideVector())
    {
        printOK("TestDivideVector");
    }
    else
    {
        printFAIL("TestDivideVector");
    }
    if (TestPerpendicularVector())
    {
        printOK("TestPerpendicularVector");
    }
    else
    {
        printFAIL("TestPerpendicularVector");
    }
    if (TestRotateAroundX())
    {
        printOK("TestRotateAroundX");
    }
    else
    {
        printFAIL("TestRotateAroundX");
    }
    if (TestRotateAroundY())
    {
        printOK("TestRotateAroundY");
    }
    else
    {
        printFAIL("TestRotateAroundY");
    }
    if (TestRotateAroundZ())
    {
        printOK("TestRotateAroundZ");
    }
    else
    {
        printFAIL("TestRotateAroundZ");
    }
    if (TestVectorLength())
    {
        printOK("TestVectorLength");
    }
    else
    {
        printFAIL("TestVectorLength");
    }
    if (TestDotProduct())
    {
        printOK("TestDotProduct");
    }
    else
    {
        printFAIL("TestDotProduct");
    }
    if (TestVectorNorm())
    {
        printOK("TestVectorNorm");
    }
    else
    {
        printFAIL("TestVectorNorm");
    }
    if (TestVectorDistance())
    {
        printOK("TestVectorDistance");
    }
    else
    {
        printFAIL("TestVectorDistance");
    }
    if (TestPlaceNormal())
    {
        printOK("TestPlaceNormal");
    }
    else
    {
        printFAIL("TestPlaceNormal");
    }

    // Vector List Tests
    if (TestInitVectorList())
    {
        printOK("TestInitVectorList");
    }
    else
    {
        printFAIL("TestInitVectorList");
    }
    if (TestPushVector())
    {
        printOK("TestPushVector");
    }
    else
    {
        printFAIL("TestPushVector");
    }
    if (TestFreeVectorList())
    {
        printOK("TestFreeVectorList");
    }
    else
    {
        printFAIL("TestFreeVectorList");
    }
    if (TestPopVector())
    {
        printOK("TestPopVector");
    }
    else
    {
        printFAIL("TestPopVector");
    }
    if (TestRemoveLastVector())
    {
        printOK("TestRemoveLastVector");
    }
    else
    {
        printFAIL("TestRemoveLastVector");
    }
    if (TestTrimVectorList())
    {
        printOK("TestTrimVectorList");
    }
    else
    {
        printFAIL("TestTrimVectorList");
    }

    // Matrix Tests
    if (TestHomogeneousMatrix())
    {
        printOK("TestHomogeneousMatrix");
    }
    else
    {
        printFAIL("TestHomogeneousMatrix");
    }
    if (TestCreateScaleMatrix())
    {
        printOK("TestCreateScaleMatrix");
    }
    else
    {
        printFAIL("TestCreateScaleMatrix");
    }
    if (TestCreateTranslationMatrix())
    {
        printOK("TestCreateTranslationMatrix");
    }
    else
    {
        printFAIL("TestCreateTranslationMatrix");
    }
    if (TestCreateScaleAndTranslationMatrix())
    {
        printOK("TestCreateScaleAndTranslationMatrix");
    }
    else
    {
        printFAIL("TestCreateScaleAndTranslationMatrix");
    }
    if (TestCreateRotationMatrixX())
    {
        printOK("TestCreateRotationMatrixX");
    }
    else
    {
        printFAIL("TestCreateRotationMatrixX");
    }
    if (TestCreateRotationMatrixY())
    {
        printOK("TestCreateRotationMatrixY");
    }
    else
    {
        printFAIL("TestCreateRotationMatrixY");
    }
    if (TestCreateRotationMatrixZ())
    {
        printOK("TestCreateRotationMatrixZ");
    }
    else
    {
        printFAIL("TestCreateRotationMatrixZ");
    }
    if (TestCreateRotationMatrix())
    {
        printOK("TestCreateRotationMatrix");
    }
    else
    {
        printFAIL("TestCreateRotationMatrix");
    }
    if (TestMultiplyMatrix())
    {
        printOK("TestMultiplyMatrix");
    }
    else
    {
        printFAIL("TestMultiplyMatrix");
    }
    if (TestVectorTransform())
    {
        printOK("TestVectorTransform");
    }
    else
    {
        printFAIL("TestVectorTransform");
    }
    if (TestMatrixDeterminant())
    {
        printOK("TestMatrixDeterminant");
    }
    else
    {
        printFAIL("TestMatrixDeterminant");
    }
    if (TestAdjointMatrix())
    {
        printOK("TestAdjointMatrix");
    }
    else
    {
        printFAIL("TestAdjointMatrix");
    }
    if (TestScaleMatrix())
    {
        printOK("TestScaleMatrix");
    }
    else
    {
        printFAIL("TestScaleMatrix");
    }
    if (TestInvertMatrix())
    {
        printOK("TestInvertMatrix");
    }
    else
    {
        printFAIL("TestInvertMatrix");
    }
    if (TestTransposeMatrix())
    {
        printOK("TestTransposeMatrix");
    }
    else
    {
        printFAIL("TestTransposeMatrix");
    }
    if (TestLookAtMatrix())
    {
        printOK("TestLookAtMatrix");
    }
    else
    {
        printFAIL("TestLookAtMatrix");
    }
    if (TestCastFloat())
    {
        printOK("TestCastFloat");
    }
    else
    {
        printFAIL("TestCastFloat");
    }
    return 0;
}
