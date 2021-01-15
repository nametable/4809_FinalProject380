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

uint8_t Queue::size() {
    return this->end - this->front;
}