#ifndef APC_H
#define APC_H
#include <dlist.h>




void reverse_str(char *string);

void slicing_data(char *string, dlist_t **head);

void swap_list(dlist_t **ptr1, dlist_t **ptr2);

int get_carry(int *ptr_value);

dlist_t *apc_addition(dlist_t *head1, dlist_t *head2);

dlist_t *apc_subtraction(dlist_t *head1, dlist_t *head2);


void calculate_limits(int value, int *limit_1, int *limit_2);

void add_zeros(dlist_t **head, int limit);

dlist_t *multiplication(dlist_t *head1, dlist_t *head2);

dlist_t *add_no_of_zeros(dlist_t *head, int limit);

dlist_t *new_multiplication(dlist_t *head_1, dlist_t *head_2);

dlist_t *get_quotient_number(dlist_t *head4 ,dlist_t *head2);

void *division(dlist_t *head1, dlist_t *head2);


dlist_t *apc_division(dlist_t *head_1, dlist_t *head_2);
dlist_t *get_quotient(dlist_t **head_1, dlist_t *head_2);


char *read_apc_inputs(void);
int find_fpoint(char *string, char **wpart, char **fpart);
void f_slicing_data(char *string, dlist_t **head);
void equal_no_of_nodes_fpart(dlist_t **fhead_1, dlist_t **fhead_2);
void add_carry_towpart(dlist_t **wresult, dlist_t **fresult, dlist_t *head);
#endif
