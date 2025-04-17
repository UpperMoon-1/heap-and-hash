/**
 * -------------------------------------
 * @file  expression_symbol.c
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
#include "common_queue_stack.h"
#include "expression_symbol.h"

QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
	QUEUE queue = { 0 };
	STACK stack = { 0 };
	char *p = infixstr;
	int sign = 1;
	int num = 0;
	char symbol[11] = { 0 };

	while (*p) {
		if (*p == '-' && (p == infixstr || *(p - 1) == '(')) {
			sign = -1;
		} else if (*p >= '0' && *p <= '9') {
			num = *p - '0';
			while ((*(p + 1) >= '0' && *(p + 1) <= '9')) {
				num = num * 10 + *(p + 1) - '0';
				p++;
			}
			enqueue(&queue, new_node(sign * num, 0));
			sign = 1;
		} else if (*p == '(') {
			push(&stack, new_node('(', 2));
		} else if (*p == ')') {
			while (stack.top) {
				if (stack.top->type == 2) {
					free(pop(&stack));
					break;
				}
				enqueue(&queue, pop(&stack));
			}
		} else if (*p == '/' || *p == '*' || *p == '%' || *p == '+'
				|| *p == '-') {
			while (stack.top && stack.top->type == 1
					&& priority(stack.top->data) >= priority(*p))
				enqueue(&queue, pop(&stack));
			push(&stack, new_node(*p, 1));
		} else if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			char *sp = symbol;
			*sp = *p;
			while ((*(p + 1) >= 'a' && *(p + 1) <= 'z')
					|| (*(p + 1) >= 'A' && *(p + 1) <= 'Z')
					|| (*(p + 1) >= '0' && *(p + 1) <= '9')) {
				p++;
				sp++;
				*sp = *p;
			}
			*(sp + 1) = '\0';

			// your code, get the value of the symobol from the hash table, then enqueue the value
			HNODE *h = hashtable_search(ht, symbol);
			enqueue(&queue, new_node(h->data.value, 0));
		}
		p++;
	}

	while (stack.top) {
		enqueue(&queue, pop(&stack));
	}

	return queue;
}

int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
	// your code
	QUEUE q = infix_to_postfix_symbol(ht, infixstr);
	int val = evaluate_postfix(q);

	return val;
}

int evaluate_postfix(QUEUE queue) {
	STACK stack = { 0 };
	int type = 0;
	NODE *p = queue.front;
	while (p) {
		type = p->type;

		if (type == 0) {    // operant
			push(&stack, new_node(p->data, 0));
		} else if (type == 1) {  // operator
			int operator = p->data;
			NODE *oprand2 = pop(&stack);

			if (operator == '+')
				stack.top->data = stack.top->data + oprand2->data;
			else if (operator == '-')
				stack.top->data = stack.top->data - oprand2->data;
			else if (operator == '*')
				stack.top->data = stack.top->data * oprand2->data;
			else if (operator == '/')
				stack.top->data = stack.top->data / oprand2->data;

			free(oprand2);
		}
		p = p->next;
	}
	int result = stack.top->data;
	clean_stack(&stack);
	return result;
}

DATA evaluate_statement(HASHTABLE *ht, char *statement) {
	DATA hd = { 0 };
	char line[80] = { 0 };
	strcpy(line, statement);
	char *p = line, *dp = line;
	while (*p) {
		if (*p != ' ') {
			*dp = *p;
			dp++;
		}
		p++;
	}
	*dp = '\0';
	char name[20] = { 0 };
	char *eqp = strstr(line, "=");
	if (eqp) {
		*eqp = '\0';
		strcpy(name, line);
		if ((name[0] >= 'a' && name[0] <= 'z')
				|| (name[0] >= 'A' && name[0] <= 'Z')) {
			int value = evaluate_infix_symbol(ht, eqp + 1);
			DATA data = { 0 };
			strcpy(data.name, name);
			data.value = value;
			hashtable_insert(ht, data);
			strcpy(hd.name, name);
			hd.value = value;
		}
	} else {
		strcpy(name, line);
		if ((name[0] >= 'a' && name[0] <= 'z')
				|| (name[0] >= 'A' && name[0] <= 'Z')) {
			HNODE *hnp = hashtable_search(ht, name);
			if (hnp) {
				strcpy(hd.name, name);
				hd.value = hnp->data.value;
			}
		}
	}
	return hd;
}
