/**
 * -------------------------------------
 * @file  common_queue_stack.c
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
#include "common_queue_stack.h"

NODE* new_node(int data, int type) {
	NODE *np = (NODE*) malloc(sizeof(NODE));
	np->data = data;
	np->type = type;
	np->next = NULL;
	return np;
}

void display(NODE *start) {
	while (start) {
		if (start->type == 0)
			printf("%d", start->data);
		else
			printf("%c", start->data);

		start = start->next;

		if (start)
			printf(" ");
	}
}

void clean(NODE **startp) {
	NODE *p = *startp;
	while (p) {
		NODE *tmp = p;
		p = p->next;
		free(tmp);
	}
	*startp = NULL;
}

void enqueue(QUEUE *qp, NODE *np) {
	if (qp == NULL || np == NULL)
		return;
	if (qp->front == NULL) {
		qp->front = np;
		qp->rear = np;
	} else {
		qp->rear->next = np;
		qp->rear = np;
	}
	qp->length++;
}

NODE* dequeue(QUEUE *qp) {
	if (qp == NULL || qp->front == NULL)
		return NULL;

	NODE *ptr = qp->front;
	if (qp->front == qp->rear) {
		qp->front = NULL;
		qp->rear = NULL;
	} else {
		qp->front = ptr->next;
	}
	qp->length--;

	return ptr;
}

void clean_queue(QUEUE *qp) {
	clean(&(qp->front));
	qp->front = NULL;
	qp->rear = NULL;
	qp->length = 0;
}

void push(STACK *sp, NODE *np) {
	if (sp == NULL || np == NULL)
		return;
	if (sp->top == NULL) {
		sp->top = np;
		sp->top->next = NULL;
	} else {
		np->next = sp->top;
		sp->top = np;
	}
	sp->height++;
}

NODE* pop(STACK *sp) {
	if (sp == NULL || sp->top == NULL)
		return NULL;
	NODE *tmp = sp->top;
	sp->top = tmp->next;
	sp->height--;
	tmp->next = NULL;
	return tmp;
}

void clean_stack(STACK *sp) {
	clean(&(sp->top));
	sp->top = NULL;
	sp->height = 0;
}

int mytype(char c) {
	int t = -1;
	if (c >= '0' && c <= '9')
		t = 0;
	else if (c == '+' || c == '-' || c == '*' || c == '/')
		t = 1;
	else if (c == '(')
		t = 2;
	else if (c == ')')
		t = 3;
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		t = 4;
	else if (c == ' ')
		t = 5;

	return t;
}

int priority(char op) {
	if (op == '/' || op == '*' || op == '%')
		return 1;
	else if (op == '+' || op == '-')
		return 0;
	else
		return -1;
}
