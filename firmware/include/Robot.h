#ifndef ROBOT_H_
#define ROBOT_H_

#ifdef __cplusplus
extern "C" {
#endif

bool robot_init(void);
void robot_connect(void);
void robot_save_configuration(int configuration, int speed, float drift);
void robot_flip(void);
int robot_serialize_for_request(char* buffer);

#ifdef __cplusplus
}
#endif

#endif /* ROBOT_H_ */
