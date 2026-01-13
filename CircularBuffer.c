#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct CircularBuffer
{
    int *ptr;
    size_t capacity;
    int *Head;
    int *Tail;
    size_t size;

};

int cb_init(struct CircularBuffer *cb, size_t capacity)
{
    cb->capacity=capacity;
    cb->ptr = (int *)malloc(sizeof(int) * capacity);
    cb->Tail = cb->ptr;
    cb->Head = cb->ptr;
    cb->size = 0;
    return 0;
}


int cb_push(struct CircularBuffer *cb, int value)
{
    if(cb->size == cb->capacity)
    {
        printf("Buffer Full\n");
        return -1;
    }

    *cb->Head = value;
    cb->Head++;
    
    if( cb->Head == cb->ptr + cb->capacity)
    {
        cb->Head = cb->ptr;
    }

    cb->size ++;
    return 0;
}

int cb_pop(struct CircularBuffer *cb, int *value)
{
    if( cb->size == 0)
    {
        printf("Buffer Empty\n");
        return -1;
    }

    *value = *cb->Tail;
    cb->Tail ++;

    if ( cb->Tail == cb->ptr + cb->capacity)
    {
        cb->Tail = cb->ptr;
    }

    cb->size--;
    
    return 0;
}

void cb_free(struct CircularBuffer *cb)
{
    free(cb->ptr);
}

void cb_print(struct CircularBuffer *cb)
{
    int i=0;
    for(i=0;i<cb->capacity;i++)
    {
        printf("element %d is %d\n",i,cb->ptr[i]);
    }
}

int main()
{
    int element=0;
    struct CircularBuffer Cb;
    cb_init(&Cb,5);
    cb_print(&Cb);
    printf("----------------\n");
    cb_push(&Cb,10);
    cb_print(&Cb);
    printf("----------------\n");
    cb_push(&Cb,15);
    cb_push(&Cb,16);
    cb_push(&Cb,17);
    cb_push(&Cb,18);
    cb_push(&Cb,19);
    cb_print(&Cb);
    printf("----------------\n");
    cb_pop(&Cb,&element);
    printf("element is %d\n",element);
    cb_print(&Cb);
    printf("----------------\n");
    cb_pop(&Cb,&element);
    printf("element is %d\n",element);
    cb_push(&Cb,19);
    cb_print(&Cb);
    printf("----------------\n");
    cb_push(&Cb,18);
    cb_push(&Cb,19);
    cb_print(&Cb);
    cb_free(&Cb);

    return 0;
}