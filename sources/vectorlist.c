#include <ansic3d/vectorlist.h>


int PushVector(Vector3D v, VectorList * list)
{
    list->count += 1;
    void *p = realloc(list->vectors,
                      list->count * sizeof(Vector3D));
    if (p == NULL)
    {
#ifdef ANSIC3D_DEBUG
        printf("Cannot allocate memory!\n");
#endif
        list->count -= 1;
        return -1;
    }else{
        list->vectors = p;
    }
    CloneVector(v, &list->vectors[list->count - 1]);
    return list->count - 1;
}


void FreeVectorList(VectorList * list)
{
    free(list->vectors);
    list->vectors = NULL;
    list->count = 0;
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
#ifdef ANSIC3D_DEBUG
        printf("List is empty\n");
#endif
        return;
    }
    CloneVector(list->vectors[list->count-1], target);
    temp = realloc(list->vectors,
                   (list->count - 1) * sizeof(Vector3D));
    if (temp == NULL)
    {
#ifdef ANSIC3D_DEBUG
        printf("Cannot reallocate memory\n");
#endif
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


void RemoveVectorIndex(VectorList * list, int index)
{
    unsigned int i, j;
    if(list->count <= index)
    {
#ifdef ANSIC3D_DEBUG
        printf("List index out of bounds\n");
#endif
        return;
    }
    Vector3D * temp = malloc((list->count - 1) * sizeof(Vector3D));
    if(temp == NULL)
    {
#ifdef ANSIC3D_DEBUG
        printf("Cannot allocate memory\n");
#endif
        return;
    }
    j = 0;
    for(i = 0; i < list->count; i++)
    {
        if(i != index){
            CloneVector(list->vectors[i], &temp[j++]);
        }
    }
    free(list->vectors);
    list->vectors = temp;
    list->count -= 1;
}
