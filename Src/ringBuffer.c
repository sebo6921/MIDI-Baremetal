/*
 * ringBuffer.c
 *
 *  Created on: Jun 8, 2026
 *      Author: libak
 */
#include "ringBuffer.h"

struct ringBuffer_t{
	uint8_t *array;
	size_t tail;
	size_t head;
	size_t size;
	size_t counter;
};

ringBuffer_t* ringBuffer_create(void *static_memory_pool, size_t capacity)
{
	ringBuffer_t *rb = (ringBuffer_t*)static_memory_pool;
	// cast the static memory pool to a unsigned integer and then cast it to fit the array uint8t we need to do this before convert a void* pointer to an integer
    rb->array = (uint8_t*)((uintptr_t)static_memory_pool + sizeof(*rb));

	rb->tail = 0;
	rb->head = 0;
	rb->size = capacity;
	rb->counter = 0;

	return rb;
}


void ringBuffer_destroy(ringBuffer_t* rb)
{
	if(rb == NULL){
		return;
	}
	rb->tail = 0;
	rb->head = 0;
	rb->counter = 0;
}

// function to check if the ring buffer is full
bool ringBuffer_full(const ringBuffer_t* rb)// const here is used to ensure these functions do not modify the value
{
	if (rb == NULL)
	{
		return NULL ;
	}
	return (rb->counter == rb->size);
}

bool ringBuffer_empty(const ringBuffer_t* rb)
{
	if (rb == NULL)
	{
		return true;
	}
	return 	rb->counter == 0;
}

/*
 rb = ring buffer object
 outdate = out_data like a delivery address if success then we return the value into there so we can then read it
 */

bool ringBuffer_pop(ringBuffer_t* rb, uint8_t *outdata)
{
	// disabling interrupts to make sure that counter logic is atomic as interrupots could corrupt it
	__disable_irq();

	if (rb == NULL) {__enable_irq(); return false;}

	if (rb->counter == 0){__enable_irq(); return false;} // empty nothing to read

	*outdata = rb->array[rb->tail]; // store the data into the outdate var so we can read it

	rb->tail = (rb->tail + 1)% rb->size;

	rb->counter --;

	__enable_irq();

	return true;
}


void ringBuffer_push(uint8_t obj, ringBuffer_t* rb)
{
	// disabling interrupts to make sure that counter logic is atomic as interrupots could corrupt it
	__disable_irq();
	if (rb == NULL) {__enable_irq(); return;}
	bool isFull = ringBuffer_full(rb);
	if (isFull){__enable_irq(); return;}
	rb->array[rb->head] = obj;
	rb->head = (rb->head + 1)% rb->size;
	rb->counter ++;
	__enable_irq();
	return;
}


