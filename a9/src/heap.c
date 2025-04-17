/**
 * -------------------------------------
 * @file  heap.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-17
 *
 * -------------------------------------
 */
/*
 * MIN HEAP HAS LOWEST VAL FIRST
 * EX.
 * [1,2,3,4,5...]
 * hda[0] < hda[heap->size]!!!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
	int r = 0;
	if (a < b)
		r = -1;
	else if (a > b)
		r = 1;
	return r;
}

HEAP* new_heap(int capacity) {
	HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
	if (hp == NULL)
		return NULL;
	hp->hda = (HEAPDATA*) malloc(sizeof(HEAPDATA) * capacity);
	if (hp->hda == NULL) {
		free(hp);
		return NULL;
	};
	hp->capacity = capacity;
	hp->size = 0;
	return hp;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index) { //return the new index of the item heapified//this work
	// your code
	HEAPDATA temp;
	int j;
	while (index > 0) {	//when the index is greater than 1 we need to check if it is greater than parent
		j = (index - 1) / 2;
		if (cmp(hda[index].key, hda[j].key) < 0) {//if j is greater than i swap!!!
			temp = hda[index];
			hda[index] = hda[j];
			hda[j] = temp;
			index = j;
		} else {
			break;
		}
	}

	return index;
}

// you may add this function to be used other functions.
//n is size of heap
//index is the index of the item you want to move!!!
int heapify_down(HEAPDATA *hda, int n, int index) {	//return new index of the item heapified
	// your code
	int i = index;
	int left;
	int right;
	int small;
	HEAPDATA temp;
	while (1) {
		left = 2 * i + 1;
		right = 2 * i + 2;
		small = i;	//cmp(hda[index].key, hda[j].key) < 0
		if (left < n && cmp(hda[left].key, hda[small].key) < 0) {
			small = left;	//hda[left] < hda[small]
		}
		if (right < n && cmp(hda[right].key, hda[small].key) < 0) {
			small = right;
		}
		if (small != i) {
			temp = hda[i];
			hda[i] = hda[small];
			hda[small] = temp;
			i = small;
		} else {
			break;
		}
	}
	return i;
}

void heap_insert(HEAP *heap, HEAPDATA new_node) {	//this is correct
	// your code
	if (heap->size == heap->capacity) {
		heap->capacity *= 2;
		HEAPDATA *temp = realloc(heap->hda, sizeof(HEAPDATA) * heap->capacity);
		if (temp) {
			heap->hda = temp;
		} else {
			temp = malloc(sizeof(HEAP) * heap->capacity);
			if (temp) {
				memcpy(temp, heap->hda, sizeof(HEAPDATA) * heap->size);
				free(heap->hda);
				heap->hda = temp;
			} else {
				printf("array resize failed\n");
			}
		}

	}
	heap->hda[heap->size] = new_node;
	heap->size++;
	heapify_up(heap->hda, heap->size - 1);

	return;
}

HEAPDATA heap_find_min(HEAP *heap) {
	// your code
	if (heap->size == 0) {
		HEAPDATA node = { 0 };
		return node;
	}

	return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap) { //delete min
	// your code
	if (heap->size == 0) {
		HEAPDATA node = { 0 };
		return node;
	}
	HEAPDATA node = heap->hda[0];	//return the front
	if (heap->size <= (heap->capacity) / 4 && heap->capacity > 4) {
		heap->capacity /= 2;
	}
	heap->hda[0] = heap->hda[heap->size - 1];
	heap->size--;
	heapify_down(heap->hda, heap->size, 0);

	return node;

}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
	// your code
	if (index >= heap->size) {
		return -1;	//element doesnt exist
	}
	int i;
	KEYTYPE oldKey = heap->hda[index].key;
	//1 if oldKey is greater than
	//if old key is greater than you have to heapify down
	//else up
	heap->hda[index].key = new_key;
	if (cmp(oldKey, new_key) < 0) {
		i = heapify_down(heap->hda, heap->size, index);
	} else {
		i = heapify_up(heap->hda, index);
	}
	return i;
}

int heap_search_value(HEAP *heap, VALUETYPE data) {	//this work fine
	// your code
	int j;
	for (j = 0; j < heap->size; j++) {
		if (heap->hda[j].value == data) {
			return j;
		}
	}

	return -1;
}
/*
 *
 }
 */
void heap_sort(HEAPDATA *arr, int n) {
	// your code
	int i;
	HEAPDATA temp;

	for (i = n / 2 - 1; i >= 0; i--) {
		heapify_down(arr, n, i);
	}
	for (i = n - 1; i > 0; i--) {
		HEAPDATA temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify_down(arr, i, 0);

	}
	return;
}

void heap_clean(HEAP **heapp) {
	if (heapp) {
		HEAP *heap = *heapp;
		if (heap->capacity > 0) {
			heap->capacity = 0;
			heap->size = 0;
			free(heap->hda);
			free(heap);
		}
		*heapp = NULL;
	}
}
