/*

Alyssa Pinnock
2/8/24

Instructions: An alternate method of storing a string is to store each letter of the string in a single node of a linked list,
with the first node of the list storing the first letter of the string. Using this method of storage, no null
character is needed since the next field of the node storing the last letter of the string would simply be a
null pointer.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head){
	int count = 0;
	for (int i=0; head != NULL; i++){
		count++;
		head = head->next;
	}

	return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	int nLen = length(head);
    char* str = (char*)malloc((nLen + 1) * sizeof(char));

    if (str == NULL) {
        printf("Error: memory allocation failed.\n");
        return 1;
    }
    
    for (int i = 0; head != NULL; i++) {
        str[i] = head->letter;
        head = head->next;
    }
    str[nLen] = '\0';
    return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{   
	node* tmp = (node*)malloc(sizeof(node));
	tmp->letter = c;
    tmp->next = NULL;

    if (!tmp) {
        printf("Error: memory allocation failed.\n");
        return 1;
    }

    if (*pHead == NULL) {
        *pHead = tmp;
    } else {
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = tmp;
    }
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	while (*pHead != NULL) {
        node* tmp = *pHead;
        *pHead = (*pHead)->next;
        free(tmp);
    }
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}