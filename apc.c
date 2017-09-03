#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <apc.h>

// Reverse string
void reverse_str(char *string)
{
	// calculate length
	int length = strlen(string), index = 0;

	char temp;

	// swapping
	while (index < length/2)
	{
		temp = string[index];

		string[index] = string[length - 1 - index];

		string[length - 1 - index] = temp;

		index++;
	}
}

// Slicing data
void slicing_data(char *string, dlist_t **head)
{
	int length = strlen(string);
	char buff[10];
	int index, value;

	// slicing the data by 9 digits
	while ((length - 1) >= 0)
	{
		// get 9 characters
		for (index = 0; index < 9 && (length - 1) >= 0; index++)
		
			buff[index] = string[--length];

		buff[index] = '\0';

		// reverse the string
		reverse_str(buff);

		// convert into value
		sscanf(buff, "%d", &value);

		// store into list
		dl_insert_first(head, value);
	}
}

// Swap list
void swap_list(dlist_t **ptr1, dlist_t **ptr2)
{
	dlist_t *temp = *ptr1;

	*ptr1 = *ptr2;

	*ptr2 = temp;
}

// Get carry
int get_carry(int *ptr_value)
{
	int carry;

	carry = *ptr_value / 1000000000;

	*ptr_value = *ptr_value % 1000000000;

	return carry;
}


/* APC Addition */
dlist_t *apc_addition(dlist_t *head1, dlist_t *head2)
{
	// head2 is null and head1 is not null then return head1
	if (head2 == NULL && head1 != NULL)

		return head1;

	// head1 is null and head2 is not null then return head2
	if (head1 == NULL && head2 != NULL)

		return head2;

	int carry = 0, value, count1 = 0, count2 = 0;

	dlist_t *ptr1 = head1, *ptr2 = head2, *head3 = NULL;

	// to reach last node of head1
	while (ptr1->next != NULL)
	{
		ptr1 = ptr1->next;

		count1++;
	}

	// to reach last node of head2
	while (ptr2->next != NULL)
	{
		ptr2 = ptr2->next;
	
		count2++;
	}

	// any list having value 0 then return another list
	if (count1 == 0 && head1->data == 0)

		return head2;

	else if (count2 == 0 && head2->data == 0)

		return head1;

	// take lowest no. of node list into ptr2
	if (count1 < count2)
	{
		swap_list(&ptr1, &ptr2);
	}

	// sum node by node upto one list reaches null
	while (ptr1 != NULL && ptr2 != NULL)
	{
		// add both node data and carry
		value = carry + ptr1->data + ptr2->data;

		// get carry
		carry = get_carry(&value);

		// insert value to ans list
		dl_insert_first(&head3, value);

		// move to prev nodes of list1 and list2
		ptr1 = ptr1->prev;
		ptr2 = ptr2->prev;
	}

	// copying remaining data upto null
	while (ptr1 != NULL)
	{
		// add carry and node data
		value = carry + ptr1->data;

		// get carry
		carry = get_carry(&value);

		// insert that value to ans list
		dl_insert_first(&head3, value);

		// move to prev node
		ptr1 = ptr1->prev;
	}

	// at last carry is present insert that carry to ans list
	if (carry)

		dl_insert_first(&head3, carry);

	// return ans list
	return head3;
}


/* APC Subtraction */
dlist_t *apc_subtraction(dlist_t *head1, dlist_t *head2)
{
	int borrow = 1000000000, value, count1 = 0, count2 = 0, flag = 0;

	dlist_t *ptr1 = head1, *ptr2 = head2, *head3 = NULL;

	// to reach last node of list1
	while (ptr1->next != NULL)
	{
		ptr1 = ptr1->next;

		count1++;
	}

	// to reach last node of list2
	while (ptr2->next != NULL)
	{
		ptr2 = ptr2->next;

		count2++;
	}

	// no. of nodes of list1 and 2 are equal 
	if(count1 == count2)
	{
		dlist_t *ptr3 = head1, *ptr4 = head2;

		// both list data are equal
		while (ptr3 != NULL && ptr3->data == ptr4->data)
		{
			ptr3 = ptr3->next;
			ptr4 = ptr4->next;			
		}		

		// the ptr reaches null then return ans as zero
		if (ptr3 == NULL)
		{
			dl_insert_first(&head3, 0);
			
			return head3;
		}

		// which list data is maximun take that into ptr1 and set the flag
		else if (ptr4->data > ptr3->data)
		{
			flag = 1;
			swap_list(&ptr1, &ptr2);
		}
	}

	// count2 having max no. of nodes then swap ptr1 and ptr2
	if (count1 < count2)
	{
		flag = 1;
		swap_list(&ptr1, &ptr2);
	}

	// do the subtraction upto any one ptr reaches null 
	while (ptr1 != NULL && ptr2 != NULL)
	{
		// ptr1 data is lessthan ptr2 data then borrow
		if (ptr1->data < ptr2->data)
		{
			// add the borrow to ptr1 data
			ptr1->data = ptr1->data + borrow;

			// subtract 1 from the prev data
			if (ptr1->prev != NULL)
			{
				ptr1->prev->data = ptr1->prev->data - 1;

				flag = 1;
			}
		}

		// subtracted result
		value = ptr1->data - ptr2->data;

		// insert result to res list
		dl_insert_first(&head3, value);

		// move ptr1 and ptr2 to prev nodes
		ptr1 = ptr1->prev;
		ptr2 = ptr2->prev;
	}

	// copying remaining data upto ptr1 prev reaches null
	while (ptr1 != NULL)
	{
		dl_insert_first(&head3, ptr1->data);

		ptr1 = ptr1->prev;
	}

	if (flag)

		head3->data = head3->data * -1;

	// return result list
	return head3;
}


// Add zeros
void add_zeros(dlist_t **head, int limit)
{
	dlist_t *n_head = NULL, *pans = NULL;
	int index;

	// multiply that many times
	for (index = 0; index < limit; index++)
	{
		n_head = apc_addition(*head, n_head);
	}

	// update the head
	*head = n_head;
}

// Calculate the limits
void calculate_limits(int value, int *limit_1, int *limit_2)
{
	// last 5 digits
	*limit_1 = value % 100000;

	// remaining digits
	*limit_2 = value / 100000;
}


/* APC Multiplication*/
dlist_t *multiplication(dlist_t *head1, dlist_t *head2)
{
	dlist_t *result_1 = NULL, *result_2 = NULL, *result_t = NULL, *final_res = NULL;

	dlist_t *ptr1 = head1, *ptr2 = head2, *pans = NULL;

	int count_1 = 0, count_2 = 0, count = 0, limit_1 = 0, limit_2 = 0, flag = 0, index, jdx;

	// to reach last nod of list1
	while (ptr1->next != NULL)
	{
		ptr1 = ptr1->next;
		count_1++;
	}

	// to reach last nod of list2
	while (ptr2->next != NULL)
	{
		ptr2 = ptr2->next;
		count_2++;
	}

	// count1 is lessthan the count2 then swap ptrs
	if (count_1 < count_2)
	{
		swap_list(&ptr1, &ptr2);

		ptr1 = head2;
	}

	// any one of the data is zero then return zero as result
	if (count_1 == 0 && head1->data == 0)
	{
		dl_insert_first(&final_res, 0);

		return final_res;
	}

	else if (count_2 == 0 && head2->data == 0)
	{
		dl_insert_first(&final_res, 0);

		return final_res;
	}

	// multiply upto ptr2 reaches null
	while (ptr2 != NULL)
	{
		result_1 = NULL, result_2 = NULL;

		// calculate limits
		calculate_limits(ptr2->data, &limit_1, &limit_2);	

		// multiply by limit1
		for (index = 0; index < limit_1; index++)
		{
			result_1 = apc_addition(ptr1, result_1);
		}

		// multiply by limit2
		for (index = 0; index < limit_2; index++)
		{
			result_2 = apc_addition(ptr1, result_2);	
		}

		// add zeros to ans2
		if (result_2 != NULL)

			add_zeros(&result_2, 100000);

		// add both ans found by limit1 and limit2
		result_t = apc_addition(result_1, result_2);

		// flag is 1
		if (flag)
		{
			count++;

			// insert 0 value upto count
			for (jdx = 0; jdx < count; jdx++)
				dl_insert_last(&result_t, 0);
		}

		else

			flag = 1;

		// add prev and new multiplication values
		final_res = apc_addition(result_t, final_res);

		// move ptr to prev node
		ptr2 = ptr2->prev;
	}

	// return multiplication res
	return final_res;
}


// Get quotient 
dlist_t *get_quotient(dlist_t **head_1, dlist_t *head_2)
{
	dlist_t *head_3 = NULL, *result = *head_1, *value = NULL; 
	dlist_t	*prv_1 = NULL, *prv_2 = NULL, *p_1 = NULL, *p_2 = NULL;
	int flag = 0, count_1 = 0, count_2 = 0;
	
	dl_insert_first(&head_3, 0);
	dl_insert_first(&value, 1);

	// subtract head_1 recursively by head_2
	while (1)
	{
		prv_1 = result;

		result = apc_subtraction(result, head_2);
		dl_del_list(&prv_1);
 
		p_1 = result, p_2 = head_2;
		
		count_1 = 0, count_2 = 0;
	
		// check the count_1 and count_2 values
		while (p_1->next != NULL)
		{
			count_1++;
			p_1 = p_1->next;
		}
		
		while (p_2->next != NULL)
		{
			count_2++;
			p_2 = p_2->next;
		}
		
		p_1 = result, p_2 = head_2;
	
		// check for valid data
		while (count_1 == count_2 && p_1 != NULL && p_2 != NULL && p_1->data == p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;
		}

		// break the loop
		if (count_1 == count_2 && p_1 != NULL && p_2 != NULL && p_1->data < p_2->data)
		
			flag = 1;
		
		else if (count_1 > count_2)

			flag = 0;

		// break the loop
		if (result != NULL && result->next == NULL && result->data == 0)
		{
			head_3 = apc_addition(head_3, value);
	
			break;
		}
		// the data is less then stop the loop
		else if (count_1 == count_2 && result != NULL && flag)

			break;

		else
		
			// count the successive subtraction
			head_3 = apc_addition(head_3, value);
	}

	*head_1 = result;

	// return count
	return head_3;
}

// APC Division
dlist_t *apc_division(dlist_t *head_1, dlist_t *head_2)
{
	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL;
	dlist_t	*q_head = NULL, *p_head = NULL, *t_head = NULL, *p_1 = NULL, *p_2 = NULL;

	int index, count_1 = 0, count_2 = 0, flag = 0;

	// count no.of nodes in list1
	while (ptr_1->next != NULL)
	{
		count_1++;

		ptr_1 = ptr_1->next;
	}

	// count no.of nodes in list2
	while (ptr_2->next != NULL)
	{
		count_2++;

		ptr_2 = ptr_2->next;
	}

	// Error print
	if (count_2 == 0 && head_2->data == 0)
	{
		printf("Error\n");

		return NULL;
	}

	// return 0 if list 1 data is lessthan the list2
	if (count_1 < count_2)
	{
		dl_insert_last(&p_head, 0);

		return p_head;
	} 

	// take the valid data
	else if (count_1 == count_2)
	{
		p_1 = head_1, p_2 = head_2;

		while (p_1 != NULL && p_1->data == p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;
		}

		// return 0 if list 1 data is lessthan the list2
		if (p_1 != NULL && p_1->data < p_2->data)
		{
			dl_insert_last(&p_head, 0);

			return p_head;
		}
	}

	ptr_1 = head_1;

	// when quotient becomes 0 break the loop
	while (1)
	{
		// get list 2 no.of nodes from list 1
		for (index = 0; index <= count_2 && ptr_1 != NULL; index++)
		{
			dl_insert_last(&head_3, ptr_1->data);

			ptr_1 = ptr_1->next;
		}

		p_1 = head_3, p_2 = head_2;

		// to check the data is valid for operation
		while (p_1 != NULL && p_1->data >= p_2->data)
		{
			p_1 = p_1->next;
			p_2 = p_2->next;
		}

		// data is not valid take the next node
		if (p_1 != NULL && p_1->data < p_2->data)
		
			flag = 1;

		else

			flag = 0;

		// list 1 head  data is less than take next node too
		if (flag && ptr_1 != NULL)
		{
			dl_insert_last(&head_3, ptr_1->data);

			ptr_1 = ptr_1->next;
		}

		// get quotient function call
		q_head = get_quotient(&head_3, head_2);

		ptr_2 = q_head;

		count_1 = 0;

		// count nodes in q_head
		while (ptr_2 != NULL && ptr_2->next != NULL)
		{
			count_1++;

			ptr_2 = ptr_2->next;
		}

		// add count_1 no of zero nodes to p_head
		for (index = 0; index < count_1; index++)

			dl_insert_last(&p_head, 0);

		// add p_head and q_head
		p_head = apc_addition(p_head, q_head);
	
		// ptr_1 reaches 0 stop
		if (ptr_1 == NULL)

			break;
	}

	// return ans
	return p_head;
}



/*function to get quotient*/
dlist_t *get_quotient_number(dlist_t *head4 ,dlist_t *head2)
{
	dlist_t *result = NULL;
	int count = 0;

	/*if head4 data > head2 data*/
	while((head4)->data >= (head2)->data)
	{

		/*subtract the list and get quotient*/
		result = apc_subtraction(result ,head2);
		
		count++;
	}

	printf("%d\n",count);

	/*insert that count into result*/
	dl_insert_last(&result ,count);

	dl_print_list(result);

	return result;
}


/*function to do apc division*/
void *division(dlist_t *head1, dlist_t *head2)
{
	int index, count1 = 0, count2 = 0;

	dlist_t *ptr1 = head1, *ptr2 = head2, *result = NULL, *head3 = NULL;
	dlist_t  *quotient = NULL;

	/*check ptr1 and count nodes*/
	while (ptr1 != NULL )
	{
		ptr1 = ptr1->next;

		count1++;
	}
	/*check ptr2 and count nodes*/
	while(ptr2 != NULL)
	{
		ptr2 = ptr2->next;

		count2++;
	}
	
	/*if head 1 data is zero insert 0 into result*/
	if(count1 == 0 && (head1)->data == 0)
	{
		dl_insert_first(&head3 , 0);

		return head3;
	}
	/*if head2 data is 0 print error message*/
	else if(count2 == 0 && (head2)->data == 0)
	{
		printf("Division is not possible\n");
	}
	
	/*if nodesfor head1 is less insert 0*/
	if(count1 < count2)
	{
		dl_insert_first(&head3 , 0);

		return head3;
	}
	/*if both counts are equal check for data*/
	else if(count1 == count2 )
	{
		dlist_t *ptr3 = head1 ,*ptr4 = head2;

		while(ptr3 != NULL && ptr3->data == ptr4->data)
		{
			ptr3 = ptr3->next;

			ptr4 = ptr4->next;
		}
		/*if data for both heads are similar insert 1*/
		if(ptr3 == NULL)
		{
			dl_insert_first(&head3 ,1);

			return head3;
		}
		/*if ptr3 less ptr4 insert 0*/
		else if(ptr3->data < ptr4->data)
		{
			dl_insert_first(&head3 ,0);

			return head3;
		}
	}
	/*run the loop up to NULL*/
	while(ptr1 != NULL && ptr2 != NULL)
	{
		dlist_t *head4 = NULL;

		dlist_t *ptr5  = head4;

		ptr1 = head1, ptr2 = head2;

		int idx ;

		/*if count2 is less insert ptr1 data  for division*/
		for(idx = 0; idx < count2 ; idx++)
		{
			dl_insert_last(&head4 ,ptr1->data);

			ptr1 = ptr1->next;
		}

		/*do the division up to diviser number should less than ptr2 data*/
		while(ptr5->data < ptr2->data)
		{
			dl_insert_last(&head4 ,ptr1->data);

			ptr1 = ptr1 ->next;

			/*get quotient and insert into final result head3*/
		     quotient = get_quotient_number(head4 , ptr2);

			dl_insert_last(&head3 , quotient->data);
	dl_print_list(head3);
		}
	}
	return head3;
}






			



/*


 
dlist_t *apc_fpart_subtraction(dlist_t *head_1, dlist_t *head_2)
{
	int borrow = 1000000000, value, count_1 = 0, count_2 = 0, flag = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL;

	// to reach last node of list1
	while (ptr_1->next != NULL)
	
		ptr_1 = ptr_1->next;
	
	// to reach last node of list2
	while (ptr_2->next != NULL)
	
		ptr_2 = ptr_2->next;

	dlist_t *p_1 = head_1, *p_2 = head_2;

	while (p_1->data == p_2->data)
	{
		p_1 = p_1->next;
		p_2 = p_2->next;
	}

	if (p_1 != NULL && p_1->data < p_2->data)

		flag = 1;

	// do the subtraction upto any one ptr reaches null 
	while (ptr_1 != NULL && ptr_2 != NULL)
	{
		// ptr1 data is lessthan ptr2 data then borrow
		if (ptr_1->data < ptr_2->data)
		{
			// add the borrow to ptr1 data
			ptr_1->data = ptr_1->data + borrow;

			// subtract 1 from the prev data
			if (ptr_1->prev != NULL)
			
				ptr_1->prev->data = ptr_1->prev->data - 1;
		}

		// subtracted result
		value = ptr_1->data - ptr_2->data;

		// insert result to res list
		dl_insert_first(&head_3, value);

		// move ptr1 and ptr2 to prev nodes
		ptr_1 = ptr_1->prev;
		ptr_2 = ptr_2->prev;
	}

	if (flag)

		head_3->data = head_3->data * -1; 	

	// return result list
	return head_3;
}


dlist_t *add_no_of_zeros(dlist_t *head, int limit)
{
	dlist_t *ptr = head;

	int num, index, idx = 0, mod, count = 0, ary_size;

	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	
		count++;
	}

	ary_size = (count + 1) * 9 + 1;
	char array[ary_size];

	while (ptr != NULL)
	{
		num = ptr->data;

		for (index = 0; index < 9; index++)
		{
			mod = num % 10;

			array[idx++] = mod + 48;

			num = num / 10;
		}

		ptr = ptr->prev;
	}

	array[idx] = '\0';

	reverse_str(array);

	idx = strlen(array);

	for (index = 0; index < limit; index++)

		array[idx + index] = 48;

	array[idx + index] = '\0';

	head = NULL;

	slicing_data(array, &head);

	return head;
}

dlist_t *new_multiplication(dlist_t *head_1, dlist_t *head_2)
{
	if (head_1 == NULL)
		return head_2;

	if (head_2 == NULL)
		return head_1;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *ptr = NULL, *head_3 = NULL, *i_head = NULL, *f_head = NULL;
	int count_1 = 0, count_2 = 0, count = 0, carry = 0, mul_value = 0, value, index;

	while (ptr_1->next != NULL)
	{
		ptr_1 = ptr_1->next;

		count_1++;
	}
	
	while (ptr_2->next != NULL)
	{
		ptr_2 = ptr_2->next;

		count_2++;
	}

	if (count_1 < count_2)
	{
		swap_list(&ptr_1, &ptr_2);
	}

	while (ptr_2 != NULL)
	{
		i_head = NULL;

		for (index = 0; index < 9; index++)
		{
			mul_value = ptr_2->data % 10;

			ptr = ptr_1;

			while (ptr != NULL)
			{
				value = ptr->data * mul_value + carry;

				dl_insert_first(&head_3, value);

				carry = get_carry(&head_3->data);

				ptr = ptr->prev;
			}

			if (carry)

				dl_insert_first(&head_3, carry);

			head_3 = add_no_of_zeros(head_3, index);

			i_head = apc_addition(i_head, head_3);

			
			head_3 = NULL;

			ptr_2->data = ptr_2->data / 10;
		}

		for (index = 0; index < count; index++)

			dl_insert_last(&i_head, 0);

		f_head = apc_addition(f_head, i_head);


		count++;

		ptr_2 = ptr_2->prev;
	}

	while (f_head != NULL && f_head->data == 0)
	{
		ptr = f_head;

		f_head = f_head->next;

		ptr->next = NULL;

		free(ptr);

		if (f_head != NULL)
		f_head->prev = NULL;
	}

	return f_head;
}


void apc_division(dlist_t *head_1, dlist_t *head_2)
{
	int index, count_1 = 0, count_2 = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *result = NULL, *head_3 = NULL;

	while (ptr_1 != NULL && ptr_1->next != NULL)
	{
		ptr_1 = ptr_1->next;

		count_1++;
	}

	dl_insert_last(&head_3, 1);

	for (index = 1; index < 111111111; index++)
	{
		head_3->data = index;

		//dl_print_list(head_3);
		//printf("before multiplication\n");
		result = new_multiplication(head_2, head_3);
		//printf("after multiplication\n");

		//dl_print_list(result);

		ptr_2 = result;

		while (ptr_2 != NULL && ptr_2->next != NULL)
		{
			ptr_2 = ptr_2->next;

			count_2++;
		}

		if (count_2 == count_1)
		{
			if (result != NULL && result->data > head_1->data)
				break;
			else
//				dl_delete_list(&result);

		}
//		else
//			dl_delete_list(&result);
	}

	dl_print_list(result);
	result = apc_subtraction(result, head_1);

	printf("%d---\n", index - 1);

	dl_print_list(result);
}
*/
