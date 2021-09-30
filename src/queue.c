//
// Created by harshil on 04/09/21.
//

#include "embedded_utils/queue.h"
#include <stdlib.h>
#include <assert.h>

/// Queue_Init
bool Queue_Init(QueuePtr_t Queue, size_t size)
{
    Queue = malloc(sizeof(struct QueueStruct_t));
    assert(Queue);
    Queue->size = size;
#ifndef BUFFER_SIZE
    Queue->buffer = malloc(sizeof(uint32_t) * Queue->size);
#endif
    Queue->num_entries = 0;
    Queue->head = 0;
    Queue->tail = 0;
    return true;
}

// Queue_Enqueue
bool Queue_Enqueue(QueuePtr_t Queue, uint32_t data)
{
    assert(Queue);
    if (Queue_Full(Queue))
    {
        // TODO:Log queue full
        return false;
    }
    Queue->buffer[Queue->tail] = data;
    Queue->num_entries++;
    Queue->tail = (Queue->tail + 1) % Queue->size;
    return true;
}

/// Queue_Dequeque
bool Queue_Dequeque(QueuePtr_t Queue, uint32_t *data)
{
    assert(Queue);
    if (Queue_Empty(Queue))
    {
        // log queue empty
        return false;
    }
    *data = Queue->buffer[Queue->head];
    Queue->head = (Queue->head + 1) % Queue->size;
    Queue->num_entries--;
    return true;
}

/// Queue_Full
bool Queue_Full(QueuePtr_t Queue)
{
    assert(Queue);
    return Queue->num_entries == Queue->size;
}

/// Queue_Empty
bool Queue_Empty(QueuePtr_t Queue)
{
    assert(Queue);
    return Queue->num_entries == 0;
}

/// Queue_Destroy
bool Queue_Destroy(QueuePtr_t Queue)
{
    assert(Queue);
    free(Queue->buffer);
    free(Queue);
    return true;
}