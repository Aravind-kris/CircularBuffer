#include <stdio.h>
#include <stddef.h>

struct CircularBuffer
{
    int *ptr;
    size_t capacity;
    int *Head;
    int *Tail;
    int size;

};

int cb_init(struct CircularBuffer *cb, size_t capacity)
{
    cb->capacity=capacity;
    cb->ptr = (int *)malloc(sizeof(int) * capacity);
    cb->Tail = cb->ptr;
    for(int i=0;i<capacity;i++)
    {
       cb->ptr[i]=0;
    }
    cb->Head = cb->ptr;
    cb->size = 0;
}


int cb_push(struct CircularBuffer *cb, int value)
{
    if(cb->size<cb->capacity)
    {
        *cb->Head = value;
        cb->Head++;
        cb->size++;
    }
    else
    {
        printf("Circular Buffer Full... Cannot push element\n");
    }
}

int cb_pop(struct CircularBuffer *cb, int *value)
{
    if(cb->size != 0)
    {
        value = *cb->Tail;
        *cb->Tail=0;
        cb->Tail++;
        cb->size--;
    }
    else
    {
        printf("Circular Buffer empty.... Cannot remove element\n");
    }
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
    cb_push(&Cb,10);
    cb_print(&Cb);
    cb_push(&Cb,15);
    cb_push(&Cb,16);
    cb_push(&Cb,17);
    cb_push(&Cb,18);
    cb_push(&Cb,19);
    cb_print(&Cb);
    cb_pop(&Cb,element);
    cb_print(&Cb);
    cb_pop(&Cb,element);
    cb_print(&Cb);
    cb_free(&Cb);

    return 0;
}