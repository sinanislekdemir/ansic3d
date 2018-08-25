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
} VectorList;

void InitVectorList(VectorList *list);
int PushVector(Vector3D v, VectorList *list);
void PopVector(VectorList *list, Vector3D *target);
void RemoveVectorIndex(VectorList *list, int index);
void RemoveLastVector(VectorList *list);
void FreeVectorList(VectorList *list);

#endif
