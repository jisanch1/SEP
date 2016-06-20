#ifndef _LOGIC_H_
#define _LOGIC_H_

#define LOGIC_T_MAX	60
#define LOGIC_T_MIN -10
#define DELTA_MAX	20

typedef enum {
	OFF,
	HEAT,
	COOL
} stm_state;

void stm_init(int set, uint8_t delta);
stm_state stm_handler(int temp);
int get_set_temp(void);

#endif