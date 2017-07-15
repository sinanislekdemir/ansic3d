#include <ansic3d/vectorlist.h>


int PushVector(Vector3D v, VectorList * list)
{
    list->count += 1;
    void *p = realloc(list->vectors,
                      list->count * sizeof(Vector3D));
    if (p == NULL)
    {
        list->count -= 1;
        return -1;
    }else{
        list->vectors = p;
    }
    CloneVector(v, &list->vectors[list->count - 1]);
    return list->count - 1;
}


void FreeVector(VectorList * v)
{
    free(v->vectors);
    v->vectors = NULL;
    v->count = 0;
}


void InitVectorList(VectorList * list)
{
    list->vectors = NULL;
    list->count = 0;
}


void PopVector(VectorList * list, Vector3D * target)
{
    Vector3D * temp;
    if(list->count == 0)
    {
        return;
    }
    CloneVector(list->vectors[list->count-1], target);
    temp = realloc(list->vectors,
                   (list->count - 1) * sizeof(Vector3D));
    if (temp == NULL)
    {
        return;
    }
    list->vectors = temp;
    list->count -= 1;
}


void RemoveLastVector(VectorList * list)
{
    Vector3D v;
    PopVector(list, &v);
}
