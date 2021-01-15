#include <stdint.h>

class Queue
{
    private:
        uint8_t buffer[256];
        uint8_t front;
        uint8_t end;
    
    public:
        Queue();
        uint8_t dequeue();
        void queue(uint8_t value);
        void queue(uint8_t *buffer);
        uint8_t size();
};