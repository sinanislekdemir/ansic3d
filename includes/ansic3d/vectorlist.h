#ifndef _vectorlist_h
#define _vectorlist_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ansic3d/vector3d.h>

typedef struct _VectorList
{
    Vector3D * vectors;
    unsigned int count;
} VectorList;

/**
 * This must be called in order to allocate the initial variables
 * and memory address;
 */
void InitVectorList(VectorList * list);
/**
 * Push vector to the vector list;
 * returns the index of last vector 
 * or (-1) if fails to allocate memory
 */
int PushVector(Vector3D v, VectorList * list);
/**
 * Pop last vector from list
 */
void PopVector(VectorList * list, Vector3D * target);
/**
 * Simply pops the last item but does not return back
 */
void RemoveLastVector(VectorList * list);
/**
 * Free the memory allocated for the vector list
 */
void FreeVector(VectorList * v);

#endif
