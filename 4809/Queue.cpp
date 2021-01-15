#include "Queue.h"

Queue::Queue() {
    this->front = 0;
    this->end = 0;
}

uint8_t Queue::dequeue() {
    return buffer[this->front++];
}

void Queue::queue(uint8_t value) {
    this->buffer[this->end] = value;
    this->end++;
}

void Queue::queue(uint8_t *buffer) {
    while(*buffer != 0) {
        this->buffer[this->end] = *buffer;
        this->end++;
        buffer++;
    }
}

uint8_t Queue::size() {
    return this->end - this->front;
}