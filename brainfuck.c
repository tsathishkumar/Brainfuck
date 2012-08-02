#include<stdio.h>
#include<stdlib.h>
/* Stack has three properties. capacity stands for the maximum number of elements stack can hold.
   Size stands for the current size of the stack and elements is the array of elements */
typedef struct Stack
{
        int capacity;
        int size;
        int *elements;
}Stack;
/* crateStack function takes argument the maximum number of elements the stack can hold, creates
   a stack according to it and returns a pointer to the stack. */
Stack * createStack(int maxElements)
{
        /* Create a Stack */
        Stack *S;
        S = (Stack *)malloc(sizeof(Stack));
        /* Initialise its properties */
        S->elements = (int *)malloc(sizeof(int)*maxElements);
        S->size = 0;
        S->capacity = maxElements;
        /* Return the pointer */
        return S;
}
void pop(Stack *S)
{
        /* If stack size is zero then it is empty. So we cannot pop */
        if(S->size==0)
        {
                printf("Stack is Empty\n");
                return;
        }
        /* Removing an element is equivalent to reducing its size by one */
        else
        {
                S->size--;
        }
        return;
}
int top(Stack *S)
{
        if(S->size==0)
        {
                printf("Stack is Empty\n");
                exit(0);
        }
        /* Return the topmost element */
        return S->elements[S->size-1];
}
void push(Stack *S,int element)
{
        /* If the stack is full, we cannot push an element into it as there is no space for it.*/
        if(S->size == S->capacity)
        {
                printf("Stack is Full\n"); //%d\n"+S->capacity);
        }
        else
        {
                /* Push an element on the top of it and increase its size by one*/ 
                S->elements[S->size++] = element;
        }
        return;
}

void execute(Stack* operationStack) {
	int array[3000] = {0};
	int* pointer = array;
	pointer = pointer + 1000;
	Stack* loopPointer = createStack(5000);
	while(operationStack->size > 0) {
		char ch = (char)top(operationStack);
		//printf("\n*%c*%d*",ch,operationStack->size);
		switch(ch) {
			case '>':
				++pointer;
				break;
			case '<':
				--pointer;
				break;
			case '+':
				++*pointer;
                      	  	break;
			case '-':
				--*pointer;
                	        break;
			case '.':
				putchar((char)*pointer);
                	        break;
			case ',':
				*pointer = getchar();
                	        break;
			case '[':
				if(*pointer > 0) {
					push(loopPointer, operationStack->size);
				} else {
					int count = 1;
        				while(count > 0) {
						pop(operationStack);
                				if(top(operationStack) == '[')
                        				count++;
                				if(top(operationStack) == ']')
                        				count--;
        				}
				}
                        	break;
			case ']':
				if(*pointer > 0) {
					operationStack->size = top(loopPointer);
				} else {
					pop(loopPointer);
				}
				break;
		}
		pop(operationStack);
	}
}


int main(int argc, char *argv[])
{
	FILE *fp ;
        Stack *operationStack = createStack(5000);
	//printf("%s\n",argv[1]);
	fp = fopen ( argv[1], "r" ) ;

	int ch;
	ch = fgetc(fp);
	while(ch != EOF) {
		//printf("%c",ch);
		if(ch == '.' || ch == ',' || ch == '>' || ch == '<' || ch == '+' || ch == '-' || ch == '[' || ch == ']')
			push(operationStack,ch);
		ch = fgetc(fp);
	}
	Stack *operationStackNew = createStack(5000);
	while(operationStack->size > 0) {
		//printf("%c",top(operationStack));
		push(operationStackNew, top(operationStack));
		pop(operationStack);
	}
	execute(operationStackNew);
}
