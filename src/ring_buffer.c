//
// Created by harshil on 03/09/21.
//

#include <assert.h>
#include <stdlib.h>
#include "embedded_utils/ring_buffer.h"

static void advance_pointer(RingBufferPtr_t RingBuffer);
static void retreat_pointer(RingBufferPtr_t RingBuffer);

bool RingBuffer_Init(RingBufferPtr_t RingBuffer, uint32_t* buffer, size_t size)
{
    assert(buffer && size);
    RingBuffer = malloc(sizeof(struct RingBufferStruct_t));
    assert(RingBuffer);
    RingBuffer->buffer = buffer;
    RingBuffer->max = size;
    return true;
}

bool RingBuffer_Full(RingBufferPtr_t RingBuffer)
{
    return RingBuffer->full;
}

bool RingBuffer_Empty(RingBufferPtr_t RingBuffer)
{
    return (!RingBuffer->full && (RingBuffer->head == RingBuffer->tail));
}

bool RingBuffer_Destroy(RingBufferPtr_t RingBuffer)
{
    assert(RingBuffer);
    free(RingBuffer);
    return true;
}

bool RingBuffer_Put(RingBufferPtr_t RingBuffer, uint32_t data)
{
    bool ErrorState = false;
    if (RingBuffer == 0 || RingBuffer->buffer == 0)
    {
        ErrorState = true;
    } else
    {
        RingBuffer->buffer[RingBuffer->head] = data;
        advance_pointer(RingBuffer);
    }
    return ErrorState;
}

bool RingBuffer_Put_NoOverwrite(RingBufferPtr_t RingBuffer, uint32_t data)
{
    bool ErrorState = false;
    if (RingBuffer == 0 || RingBuffer->buffer == 0)
    {
        ErrorState = true;
    } else
    {
        if (!RingBuffer_Full(RingBuffer))
        {
            RingBuffer->buffer[RingBuffer->head] = data;
            advance_pointer(RingBuffer);
            ErrorState = true;
        }
    }
    return ErrorState;
}

bool RingBuffer_Get(RingBufferPtr_t RingBuffer, uint32_t *data)
{
    bool ErrorState = false;
    if (RingBuffer == 0 || RingBuffer->buffer == 0)
    {
        ErrorState = true;
    } else
    {
        if (!RingBuffer_Empty(RingBuffer))
        {
            *data = RingBuffer->buffer[RingBuffer->tail];
            retreat_pointer(RingBuffer);
        }
    }
    return ErrorState;
}

static void advance_pointer(RingBufferPtr_t RingBuffer)
{
    if (RingBuffer->full)
    {
        // We use conditional logic to reduce total number of instructions
        if (++(RingBuffer->tail) == RingBuffer->max)
        {
            RingBuffer->tail = 0;
        }
    }
    if (++(RingBuffer->head) == RingBuffer->max)
    {
        RingBuffer->head = 0;
    }
    RingBuffer->full = (RingBuffer->head == RingBuffer->tail);
}

static void retreat_pointer(RingBufferPtr_t RingBuffer)
{
    RingBuffer->full = false;
    if (++(RingBuffer->tail) == RingBuffer->max)
    {
        RingBuffer->tail = 0;
    }
}
