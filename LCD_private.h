/***************************************************************************/
/***************************************************************************/
/****************      Author:    Hamsa Ragheb       ***********************/
/****************      Layer:     HAL                ***********************/
/****************      SWC:       LCD                ***********************/
/****************      Date:      14/8/2023         ***********************/
/****************      Version:   1.00               ***********************/

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_
/*Replace Array to Linked List */
typedef struct node
{
	u8 data;
	struct node* next;
}node_t;

//node_t Head=NULL;

/*void InsertNode (u8 value)
{
	node_t* ptr = (node_t*)malloc(sizeof(node_t));
	ptr -> data = value;

	node_t* last = NULL;

	if (Head == NULL)
	{
		Head = ptr ;
		ptr -> next = NULL;
	}
	else
	{
		last = Head ;
		while(last -> next != NULL)
		{
			last = last -> next ;
		}

		last -> next = ptr;
		ptr -> next = NULL;
	}
}*/


#endif /* LCD_PRIVATE_H_ */
