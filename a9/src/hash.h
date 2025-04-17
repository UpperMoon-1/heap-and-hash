/**
 * -------------------------------------
 * @file  hash.h
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-17
 *
 * -------------------------------------
 */
#ifndef HASH_H
#define HASH_H

typedef struct {
	char name[20];
	int value;
} DATA;

typedef struct hnode {
	DATA data;
	struct hnode *next;
} HNODE;

typedef struct hashtable {
	int size;
	int count;
	HNODE **hna;
} HASHTABLE;

int hash(char *key, int size);

HASHTABLE* new_hashtable(int size);

int hashtable_insert(HASHTABLE *ht, DATA data);

HNODE* hashtable_search(HASHTABLE *ht, char *name);

int hashtable_delete(HASHTABLE *ht, char *name);

void hashtable_clean(HASHTABLE **ht);

#endif
