#ifndef _TIMER_H_
#define _TIMER_H_

typedef void (*suscriber)(void);

void timer_init(void);
void timer_suscribe(suscriber sus);
#endif