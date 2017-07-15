#include <ansic3d/matrix3d.h>
#include <ansic3d/vector3d.h>
#include <ansic3d/vectorlist.h>
#include <stdio.h>


void MatrixInversionTest()
{
    Matrix3D m;
    printf("Homogeneous Matrix\n");
    HomogeneousMatrix(&m);
    PrintMatrix(m);
    printf("Scale Matrix by 2\n");
    ScaleMatrix(&m, 2);
    PrintMatrix(m);
    printf("Invert matrix\n");
    InvertMatrix(&m);
    PrintMatrix(m);
}


void CameraPositionTest()
{
    Matrix3D cam_matrix;
    Vector3D eye, target, up;
    SetVector(10, 10, 10, 1, &eye);
    SetVector(0, 0, 0, 1, &target);
    SetVector(0, 0, 1, 1, &up);
    LookAtMatrix(eye, target, up, &cam_matrix);
    PrintMatrix(cam_matrix);
}


void PlaneNormalTest()
{
    Vector3D p1, p2, p3, result;
    SetVector(0, 0, 0, 1, &p1);
    SetVector(10, 0, 0, 1, &p2);
    SetVector(5, 5, 0, 1, &p3);
    PlaneNormal(p1, p2, p3, &result);
    PrintVector(result);
}


void VectorListTest()
{
    unsigned int i;
    VectorList mylist;
    Vector3D v1, v2, v3, v4;

    InitVectorList(&mylist);

    SetVector(0, 1, 2, 1, &v1);
    SetVector(3, 4, 5, 1, &v2);
    SetVector(2, 5, 6, 1, &v3);
    SetVector(9, 2, 3, 1, &v4);

    PushVector(v1, &mylist);
    PushVector(v2, &mylist);
    PushVector(v3, &mylist);
    PushVector(v4, &mylist);

    printf("Total %d items in list\n", mylist.count);
    for(i=0; i < mylist.count; i++)
    {
        PrintVector(mylist.vectors[i]);
    }

    printf("Remove last item from list\n");
    RemoveLastVector(&mylist);
    for(i=0; i < mylist.count; i++)
    {
        PrintVector(mylist.vectors[i]);
    }


    FreeVector(&mylist);
}


int main()
{
    printf("Matrix Inversion Test\n");
    MatrixInversionTest();
    printf("Camera Position Test\n");
    CameraPositionTest();
    printf("Plane Normal Test\n");
    PlaneNormalTest();
    printf("Vector List Test\n");
    VectorListTest();
}
