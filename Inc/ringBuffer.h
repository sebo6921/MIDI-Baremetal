/*
 * ringBuffer.h
 *
 *  Created on: Jun 7, 2026
 *      Author: libak
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// this is a stic pool use this to avoid malloc and free
// Size = size of the hidden struct pointer + your custom byte slots
#define RING_BUFFER_MEMORY_SIZE(capacity) (sizeof(size_t)*5 + (capacity))


typedef struct ringBuffer_t ringBuffer_t;

ringBuffer_t* ringBuffer_create(void *static_memory_pool, size_t capacity);

void ringBuffer_destroy(ringBuffer_t* rb);

// const here is used to ensure these functions do not modify the value
bool ringBuffer_full(const ringBuffer_t* rb);

bool ringBuffer_empty(const ringBuffer_t* rb);

bool ringBuffer_pop(ringBuffer_t* rb, uint8_t *outdata);

void ringBuffer_push(uint8_t obj, ringBuffer_t* rb);

static inline void __disable_irq(void) {
    __asm volatile ("cpsid i" : : : "memory");
}

static inline void __enable_irq(void) {
    __asm volatile ("cpsie i" : : : "memory");
}
#endif /* RINGBUFFER_H_ */
