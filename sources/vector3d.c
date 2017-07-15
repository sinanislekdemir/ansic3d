#include <ansic3d/vector3d.h>


void CloneVector(Vector3D from, Vector3D * to)
{
    SetVector(from.x, from.y, from.z, from.w, to);
}

void AddVector3D(Vector3D p1, Vector3D p2, Vector3D * target)
{
    target->x = p1.x + p2.x;
    target->y = p1.y + p2.y;
    target->z = p1.z + p2.z;
}


void SubVector3D(Vector3D p1, Vector3D p2, Vector3D * target)
{
    target->x = p1.x - p2.x;
    target->y = p1.y - p2.y;
    target->z = p1.z - p2.z;
}


void ScaleVector(Vector3D * target, double factor)
{
    target->x *= factor;
    target->y *= factor;
    target->z *= factor;
    target->w *= factor;
}


void CrossProduct(Vector3D v1, Vector3D v2, Vector3D * target)
{
    target->x = v1.y * v2.z - v1.z * v2.y;
    target->y = v1.z * v2.x - v1.x * v2.z;
    target->z = v1.x * v2.y - v1.y * v2.x;
}


void NormalizeVector3D(Vector3D * target)
{
    double invlen;
    double vn;
    vn = VectorNorm(*target);
    if (vn != 0)
    {
        invlen = rsqrt(vn);
        target->x = target->x * invlen;
        target->y = target->y * invlen;
        target->z = target->z * invlen;
        target->w = 0;
    }
}


void DivideVector(Vector3D * vector, Vector3D divider)
{
    vector->x = vector->x / divider.x;
    vector->y = vector->y / divider.y;
    vector->z = vector->z / divider.z;
}


void PerpendicularVector(Vector3D v1, Vector3D v2, Vector3D * target)
{
    double dot = DotProduct(v1, v2);
    target->x = v1.x - dot * v2.x;
    target->y = v1.y - dot * v2.y;
    target->z = v1.z - dot * v2.z;
}


void RotateAroundX(Vector3D * target, double angle)
{
    Vector3D org;
    double s, c;
    s = sin(angle);
    c = cos(angle);
    org.x = target->x;
    org.y = target->y;
    org.z = target->z;
    target->y = c * org.y + s * org.z;
    target->z = c * org.z - s * org.y;
}


void RotateAroundY(Vector3D * target, double angle)
{
    Vector3D org;
    double s, c;
    s = sin(angle);
    c = cos(angle);
    org.x = target->x;
    org.y = target->y;
    org.z = target->z;
    target->x = c * org.x + s * org.z;
    target->z = c * org.z - s * org.x;
}


void RotateAroundZ(Vector3D * target, double angle)
{
    Vector3D org;
    double s, c;
    s = sin(angle);
    c = cos(angle);
    org.x = target->x;
    org.y = target->y;
    org.z = target->z;
    target->x = c * org.x + s * org.y;
    target->y = c * org.y - s * org.x;
}


void SetVector(double x, double y, double z, double w, Vector3D * target)
{
    target->x = x;
    target->y = y;
    target->z = z;
    target->w = w;
}


double VectorLength(Vector3D vector)
{
    return sqrt((vector.x * vector.x) +
                (vector.y * vector.y) +
                (vector.z * vector.z));
}


double DotProduct(Vector3D v1, Vector3D v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z + v2.z);
}


double VectorNorm(Vector3D vector)
{
    return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}


double VectorDistance(Vector3D v1, Vector3D v2)
{
    return sqrt(pow(v2.x - v1.x, 2) +
                pow(v2.y - v1.y, 2) +
                pow(v2.z - v1.z, 2));
}


double rsqrt(double n)
{
    return 1 / sqrt(n);
}


int VectorEquals(Vector3D v1, Vector3D v2)
{
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}


void PrintVector(Vector3D v)
{
    printf("V: %20.4f i %20.4f j %20.4f k %20.4f l\n", v.x, v.y, v.z, v.w);
}


void PlaneNormal(Vector3D v1, Vector3D v2, Vector3D v3, Vector3D * result)
{
    Vector3D t1, t2;
    SubVector3D(v2, v1, &t1);
    SubVector3D(v3, v1, &t2);
    CrossProduct(t1, t2, result);
    NormalizeVector3D(result);
}
