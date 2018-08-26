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
#ifndef _vectorlist_h
#define _vectorlist_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ansic3d/vector3d.h>
#include <ansic3d/config.h>

typedef struct _VectorList
{
    Vector3D *vectors;
    unsigned int count;
    unsigned int capacity;
    int index;
} VectorList;

/**
 * Init the vectorlist.
 * Vector still can get over this capacity but in each PushVector
 * it will create a copy and swap the memory. SetCapacity 
 * pre-allocates a memory upto given vector count.
 */
void InitVectorList(VectorList *list, int capacity);

/**
 * Add a vector to the end of the list
 * Return count of items in list, 0 if fails
 */
int PushVector(Vector3D v, VectorList *list);

/**
 * Pop out the latest item in the list
 * Return count of items in list, 0 if fails
 */
int PopVector(VectorList *list, Vector3D *target);

/**
 * Remove the vector at given index
 * Please note that, this is a memory-heavy operation.
 * Return count of items in list, 0 if fails
 */
int RemoveVectorIndex(VectorList *list, int index);

/**
 * Remove the last element in the vector list
 */
void RemoveLastVector(VectorList *list);

/**
 * Free the vector list
 */
void FreeVectorList(VectorList *list);

/**
 * Trim the leading empty vectors from the list.
 * Can/should be used before pushing the vector list to video memory
 * Return count of items in list, 0 if fails
 */
int TrimVectorList(VectorList *list);

#endif
