#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<apc.h>


int main()
{
	int option;
	char num1[100] ,num2[100];
	dlist_t	*ptr = NULL;
	dlist_t *head1 = NULL ,*head2 = NULL;
	char ch;


	printf("Choose the option: \n\t 1.Addition\n\t 2.Subtraction\n\t 3.Multiplication\n\t 4.Division\n");

	printf("Enter the option :");
	scanf("%d",&option);

	printf("Enter the number1 :");
	scanf("%s",num1);

	slicing_data(num1 ,&head1);
	printf("\n");

	printf("Enter the number2 :");
	scanf("%s",num1);

	slicing_data(num1 ,&head2);
	printf("\n");

	switch(option)
	{
		case 1:

			ptr = apc_addition(head1 ,head2);

			printf("Adition :");
			dl_print_list(ptr);
			printf("\n");
			break;

		case 2:

			ptr = apc_subtraction(head1 ,head2);
			dl_print_list(ptr);
			printf("\n");

			break;


		case 3:
			ptr = multiplication(head1, head2);
			dl_print_list(ptr);
			printf("\n");

			break;

		case 4:
			ptr = apc_division(head1 ,head2);
			dl_print_list(ptr);
			printf("\n");

			break;

		default:
			printf("Check for option\n");
			break;

	}

	return 0;
}



