//
// Created by harshil on 04/09/21.
//

#ifndef INCLUDE_EMBEDDED_UTILS_QUEUE_H
#define INCLUDE_EMBEDDED_UTILS_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "embedded_utils/utils.h"

typedef struct QueueStruct_t *QueuePtr_t;

/// QueueStruct_t
struct QueueStruct_t {
#ifdef BUFFER_SIZE
    uint32_t buffer[BUFFER_SIZE];
#elif
    uint32_t *buffer;
#endif
    uint32_t head, tail, num_entries;
    size_t size;
};

bool Queue_Init(QueuePtr_t Queue, size_t size);
bool Queue_Enqueue(QueuePtr_t Queue, uint32_t data);
bool Queue_Dequeque(QueuePtr_t Queue, uint32_t *data);
bool Queue_Full(QueuePtr_t Queue);
bool Queue_Empty(QueuePtr_t Queue);
bool Queue_Destroy(QueuePtr_t Queue);

#endif //INCLUDE_EMBEDDED_UTILS_QUEUE_H
