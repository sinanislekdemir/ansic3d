#ifndef _vectorlist_h
#define _vectorlist_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ansic3d/vector3d.h>
#include <ansic3d/config.h>

typedef struct _VectorList
{
    Vector3D * vectors;
    unsigned int count;
} VectorList;

void InitVectorList(VectorList * list);
int PushVector(Vector3D v, VectorList * list);
void PopVector(VectorList * list, Vector3D * target);
void RemoveVectorIndex(VectorList * list, int index);
void RemoveLastVector(VectorList * list);
void FreeVectorList(VectorList * list);

#endif
