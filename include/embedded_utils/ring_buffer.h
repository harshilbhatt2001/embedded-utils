//
// Created by harshil on 03/09/21.
//

#ifndef EMBEDDED_UTILS_RING_BUFFER_H
#define EMBEDDED_UTILS_RING_BUFFER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct RingBufferStruct_t *RingBufferPtr_t;

struct RingBufferStruct_t {
    uint32_t *buffer;
    size_t head;
    size_t tail;
    size_t max;
    bool full;
};

bool RingBuffer_Init(RingBufferPtr_t RingBuffer, uint32_t *buffer, size_t size);
bool RingBuffer_Destroy(RingBufferPtr_t RingBuffer);
bool RingBuffer_Full(RingBufferPtr_t RingBuffer);
bool RingBuffer_Empty(RingBufferPtr_t RingBuffer);
bool RingBuffer_Put(RingBufferPtr_t RingBuffer, uint32_t data);
bool RingBuffer_Put_NoOverwrite(RingBufferPtr_t RingBuffer, uint32_t data);
bool RingBuffer_Get(RingBufferPtr_t RingBuffer, uint32_t *data);

#endif //EMBEDDED_UTILS_RING_BUFFER_H
