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
#include <ansic3d/vectorlist.h>

void InitVectorList(VectorList *list, int capacity)
{
	void *p = malloc(capacity * sizeof(Vector3D));
	list->vectors = p;
	if (p == NULL)
	{
		return;
	}
	list->count = 0;
	list->index = -1;
	list->capacity = capacity;
}

int PushVector(Vector3D v, VectorList *list)
{
	if (list->capacity > list->count)
	{
		list->index++;
		CloneVector(v, &list->vectors[list->index]);
		list->count++;
		return list->index;
	}

	list->capacity++;
	void *p = realloc(list->vectors,
			list->capacity * sizeof(Vector3D));
	if (p == NULL)
	{
		list->capacity--;
		return 0;
	}
	else
	{
		list->vectors = p;
	}
	list->index++;
	CloneVector(v, &list->vectors[list->index]);
	list->count++;
	return list->count;
}

void FreeVectorList(VectorList *list)
{
	free(list->vectors);
	list->vectors = NULL;
	list->count = 0;
	list->capacity = 0;
	list->index = -1;
}

int PopVector(VectorList *list, Vector3D *target)
{
	if (list->count == 0)
	{
		return 0;
	}

	CloneVector(list->vectors[list->index], target);
	// We don't actually re-allocate the memory. This can be too much memory
	// consuming due to memcpy operations inside realloc.
	// instead we take the memory cursor (index) one step back so if
	// a new vector gets added, it will over-write the memory area
	list->index--;
	list->count--;
	return list->count;
}

void RemoveLastVector(VectorList *list)
{
	Vector3D v;
	PopVector(list, &v);
}

int RemoveVectorIndex(VectorList *list, int index)
{
	int i, j;
	if ((int) list->count <= index)
	{
		return 0;
	}

	Vector3D *temp = malloc((list->capacity) * sizeof(Vector3D));
	if (temp == NULL)
	{
		return 0;
	}
	j = 0;
	for (i = 0; i < list->index; i++)
	{
		if (i != index)
		{
			CloneVector(list->vectors[i], &temp[j++]);
		}
	}
	free(list->vectors);
	list->vectors = temp;
	list->count--;
	list->index--;
	return list->count;
}

int TrimVectorList(VectorList *list)
{
	unsigned int i;
	Vector3D *temp = malloc((list->count) * sizeof(Vector3D));
	if (temp == NULL)
	{
		return 0;
	}
	list->capacity = list->count;
	list->index = list->count - 1;
	for (i = 0; i < list->count; i++)
	{
		CloneVector(list->vectors[i], &temp[i]);
	}
	free(list->vectors);
	list->vectors = temp;
	return list->count;
}
