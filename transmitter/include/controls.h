#ifndef CONTROLS_H
#define CONTROLS_H

void controls_begin(void);
void controls_loop(void* v);
bool select_pressed(void);
bool left_pressed(void);
bool right_pressed(void);
int read_left_x(void);
int read_left_y(void);
int read_right_x(void);
int read_right_y(void);

#endif /* CONTROLS_H */
