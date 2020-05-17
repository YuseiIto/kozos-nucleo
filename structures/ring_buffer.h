#include <stdint.h>

#define BUFFER_LENGTH 256
typedef enum
{
 OK = 0,
 buffer_empty = 1,
 buffer_overflow = 2
} ringBuffer_result_t;

typedef enum
{
 empty = 0,
 queued = 1,
 full = 2
} ringBuffer_state_t;

typedef struct
{
 uint16_t length;
 uint8_t data[BUFFER_LENGTH];
 uint16_t read_index;
 uint16_t write_index;
 ringBuffer_state_t state;
} ringBuffer_t;

void get_buffer_state(ringBuffer_t *buf)
{
 if (buf->read_index == buf->write_index - 1 || (buf->read_index == buf->length - 1 && buf->write_index == 0))
 {
  buf->state = empty;
 }
 else if (buf->read_index == buf->write_index + 1 || (buf->write_index == buf->length - 1 && buf->read_index == 0))
 {
  buf->state = full;
 }
 else
 {
  buf->state = queued;
 }
}

void ringBuffer_init(ringBuffer_t *buf)
{
 buf->length = BUFFER_LENGTH;
 buf->read_index = 0;
 buf->write_index = 1;

 get_buffer_state(buf);
}

ringBuffer_result_t push(ringBuffer_t *buf, uint8_t data)
{
 get_buffer_state(buf);
 if (buf->state < full)
 {
  buf->data[buf->write_index] = data;
  buf->write_index++;
  buf->write_index %= buf->length;

  get_buffer_state(buf);

  return OK;
 }
 else
 {
  // Full
  return buffer_overflow;
 }
}

ringBuffer_result_t pop(ringBuffer_t *buf, uint8_t *res)
{
 get_buffer_state(buf);
 if (buf->state > empty)
 {
  buf->read_index++;
  buf->read_index %= buf->length;
  *res = buf->data[buf->read_index];
  buf->data[buf->read_index] = 0x00;
  get_buffer_state(buf);
  return OK;
 }

 return buffer_empty;
}
