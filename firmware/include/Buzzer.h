#ifndef BUZZER_H_
#define BUZZER_H_

#ifdef __cplusplus
extern "C" {
#endif

void buzzer_init(void);
void buzzer_beep(void* v);

#ifdef __cplusplus
}
#endif

#endif /* BUZZER_H_ */
