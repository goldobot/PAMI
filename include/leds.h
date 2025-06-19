void init_leds();

void set_side_blue();
void set_side_yellow();
void show_start_pos(uint8_t pami_id, uint8_t side);
void leds_pull_wait();
void leds_start_wait();
void leds_start_match();
void TaskRainbow(void *pvParameters);
void rainbow(int wait);