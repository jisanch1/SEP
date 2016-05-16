
#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

typedef struct {
	char *buffer;
	uint8_t lenght;
	uint8_t head;
	uint8_t tail;
	uint8_t count;
} ringbuffer_t;

ringbuffer_t * rb_create(uint8_t lenght);
void rb_destroy(ringbuffer_t *rb);

uint8_t rb_put_char(ringbuffer_t *rb, char ch);
uint8_t rb_put_string(ringbuffer_t *rb, char *str, uint8_t str_len);
uint8_t rb_get_char(ringbuffer_t *rb, char *chp);
uint8_t rb_get_string(ringbuffer_t *rb, char *dest, uint8_t dest_len);
uint8_t rb_get_free_space(ringbuffer_t *rb);
uint8_t rb_get_count(ringbuffer_t *rb);





#endif // _RINGBUFFER_H_ 