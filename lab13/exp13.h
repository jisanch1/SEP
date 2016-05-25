
#ifndef _EXP13_H_
#define _EXP13_H_

// Led
void led_init(void);
void led_toggle(void);

// Button counter
void cnt_init(void);
void cnt_increase(void);
void cnt_stop(void);
void cnt_start(void);
void cnt_send_next(void);

// Debouncer
void deb_init(void);
void deb_shift_left(void);
void deb_shift_right(void);
void deb_press(void);
void deb_release(void);
void deb_countdown(void);

#endif // _EXP13_H_