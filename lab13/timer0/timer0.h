#ifndef _TIMER0_H_
#define _TIMER0_H_

typedef enum {NORMAL, CTC, FAST_PWM, PHC_PWM, CTC_FAST_PWM, CTC_PHC_PWM} waveform_mode_te;
typedef enum {TIMER0_OK, TIMER0_BAD_CLOCK_SET} timer0_error_handler_te;

void timer0_set_waveform(waveform_mode_te wf);

/* Clock and prescaler */
uint8_t timer0_enable_clock(uint16_t prescaler);
void timer0_disable_clock(void);

/* Configure compare registers */
void timer0_set_compare_register_A(uint8_t value);
void timer0_set_compare_register_B(uint8_t value);

/* Interrupts */
void timer0_enable_compare_A_interrupt(void);
void timer0_disable_compare_A_interrupt(void);
void timer0_enable_compare_B_interrupt(void);
void timer0_disable_compare_B_interrupt(void);
void timer0_enable_overflow_interrupt(void);
void timer0_disable_overflow_interrupt(void);

#endif // _TIMER0_H_