#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "ringbuffer.h"


ringbuffer_t *rb_create(uint8_t lenght)
{
	ringbuffer_t *rb = malloc(sizeof(ringbuffer_t));
	rb->buffer = calloc(lenght, sizeof(char));
	rb->lenght = lenght;
	rb->tail = rb->head = rb->count = 0;
	return rb;
}

void rb_destroy(ringbuffer_t *rb)
{
	free(rb->buffer);
	free(rb);
}

uint8_t rb_put_char(ringbuffer_t *rb, char ch)
{
	uint8_t overwrite = 0;
	if (rb->count == rb->lenght)
	{
		overwrite = 1;
		rb->tail = (rb->tail + 1) % rb->lenght;
		rb->count--;
	}

	rb->buffer[rb->head] = ch;
	rb->head = (rb->head + 1) % rb->lenght;
	rb->count++;

	return overwrite;
}

uint8_t rb_put_string(ringbuffer_t *rb, char *str, uint8_t str_len)
{
	uint8_t overwritten_num = 0;
	while(str_len-- && *str)
	{
		overwritten_num += rb_put_char(rb, *str++);
	}
	return overwritten_num;
}

uint8_t rb_get_char(ringbuffer_t *rb, char *chp)
{
	if (rb->count > 0)
	{
		*chp = rb->buffer[rb->tail];
		rb->tail = (rb->tail + 1) % rb->lenght;
		rb->count--;
		return 0;
	}
	else
	{
		return 1;
	}
}

uint8_t rb_get_string(ringbuffer_t *rb, char *dest, uint8_t dest_len)
{
	uint8_t n;
	for(n = 0; --dest_len && !rb_get_char(rb, dest); n++, dest++)
	{
		if (*dest == '\r')
		{
			dest++;
			break;
		}
	}
	*dest = '\0';
	return n;
}

uint8_t rb_get_free_space(ringbuffer_t *rb)
{
	return rb->lenght - rb->count;
}

uint8_t rb_get_count(ringbuffer_t *rb)
{
	return rb->count;
}



