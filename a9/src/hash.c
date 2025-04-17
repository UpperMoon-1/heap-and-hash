/**
 * -------------------------------------
 * @file  hash.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-17
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

HNODE* hashtable_search(HASHTABLE *ht, char *name) {
	// your code
	int key = hash(name, ht->size);

	HNODE *current = *(ht->hna + key);
	while (current != NULL) {
		if (strcmp(current->data.name, name) == 0) { //found
			return current;
		}
		current = current->next;
	}

	return NULL;
}

int hashtable_insert(HASHTABLE *ht, DATA data) {
	// your code
	int key = hash(data.name, ht->size);
	HNODE *current = *(ht->hna + key);
	HNODE *previous = NULL;

	while (current != NULL) {
		if (strcmp(current->data.name, data.name) == 0) {
			current->data.value = data.value;
			return 0;
		}
		previous = current;
		current = current->next;
	}

	HNODE *node = (HNODE*) malloc(sizeof(HNODE));
	node->data = data;

	if (previous == NULL) {
		node->next = *(ht->hna + key);
		*(ht->hna + key) = node;
	} else {
		node->next = previous->next;
		previous->next = node;
	}
	ht->count++;

	return 1;
}

int hashtable_delete(HASHTABLE *ht, char *name) {
	// your code
	int key = hash(name, ht->size);
	HNODE *current = *(ht->hna + key);
	HNODE *prev = NULL;

	while (current != NULL) {
		if (strcmp(current->data.name, name) == 0) { //found
			if (prev == NULL) {
				*(ht->hna + key) = current->next;
			} else {
				prev->next = current->next;
			}
			free(current);
			ht->count--;
			return 1;
		}
		prev = current;
		current = current->next;
	}

	return 0;
}

int hash(char *key, int size) {
	unsigned int hash = 0;
	while (*key) {
		hash += *key++;
	}
	return hash % size;
}

HASHTABLE* new_hashtable(int size) {
	HASHTABLE *ht = (HASHTABLE*) malloc(sizeof(HASHTABLE));
	ht->hna = (HNODE**) malloc(sizeof(HNODE**) * size);
	int i;
	for (i = 0; i < size; i++)
		*(ht->hna + i) = NULL;

	ht->size = size;
	ht->count = 0;
	return ht;
}

void hashtable_clean(HASHTABLE **htp) {
	if (*htp == NULL)
		return;
	HASHTABLE *ht = *htp;
	HNODE *p, *temp;
	int i;
	for (i = 0; i < ht->size; i++) {
		p = ht->hna[i];
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		ht->hna[i] = NULL;
	}
	free(ht->hna);
	ht->hna = NULL;
	*htp = NULL;
}
