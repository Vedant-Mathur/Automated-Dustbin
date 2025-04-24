//Final Working Code

#include <LPC17xx.h>

#define TRIG_PIN 15
#define ECHO_PIN 16
#define LED_PIN 8
#define STEPPER_MASK 0x000000F0  // P0.4 to P0.7

// Stepper motor sequence
unsigned int step_sequence[] = {
    0x10, // 00010000
    0x20, // 00100000
    0x40, // 01000000
    0x80  // 10000000
};

// LCD control
#define RS (1 << 27)
#define EN (1 << 28)
#define LCD_DATA_MASK 0x07800000  // P0.23 to P0.26

void delay_us(uint32_t us) {
    LPC_TIM1->TCR = 0x02;
    LPC_TIM1->PR = 99;
    LPC_TIM1->TCR = 0x01;
    while (LPC_TIM1->TC < us);
    LPC_TIM1->TCR = 0x00;
}

void delay_ms(uint32_t ms) {
	int i;
    for ( i = 0; i < ms; i++) {
        delay_us(1000);
    }
}

void init_GPIO() {
    LPC_GPIO0->FIODIR |= (1 << TRIG_PIN) | (1 << LED_PIN);  // Output
    LPC_GPIO0->FIODIR &= ~(1 << ECHO_PIN);                  // Input
    LPC_GPIO0->FIODIR |= STEPPER_MASK;                      // Stepper motor
    LPC_GPIO0->FIODIR |= RS | EN | LCD_DATA_MASK;           // LCD
}

void init_timer1() {
    LPC_SC->PCONP |= (1 << 2);  // Enable Timer1 power
    LPC_TIM1->TCR = 0x00;
    LPC_TIM1->PR = 0;
    LPC_TIM1->TCR = 0x02;  // Reset Timer1
}

uint32_t measure_distance_cm() {
    uint32_t duration;

    LPC_GPIO0->FIOCLR = (1 << TRIG_PIN);
    delay_us(2);
    LPC_GPIO0->FIOSET = (1 << TRIG_PIN);
    delay_us(10);
    LPC_GPIO0->FIOCLR = (1 << TRIG_PIN);

    while (!(LPC_GPIO0->FIOPIN & (1 << ECHO_PIN)));
    LPC_TIM1->TCR = 0x02;
    LPC_TIM1->TCR = 0x01;

    while (LPC_GPIO0->FIOPIN & (1 << ECHO_PIN));
    LPC_TIM1->TCR = 0x00;
    duration = LPC_TIM1->TC;

    return duration / 58;
}

// ---------- LCD Functions ----------
void lcd_enable_pulse() {
    LPC_GPIO0->FIOSET = EN;
    delay_us(10);
    LPC_GPIO0->FIOCLR = EN;
    delay_us(10);
}

void lcd_send_nibble(unsigned int nibble) {
    LPC_GPIO0->FIOCLR = LCD_DATA_MASK;
    LPC_GPIO0->FIOSET = (nibble << 23) & LCD_DATA_MASK;
    lcd_enable_pulse();
}

void lcd_cmd(unsigned char cmd) {
    LPC_GPIO0->FIOCLR = RS;
    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);
    delay_ms(2);
}

void lcd_data(unsigned char data) {
    LPC_GPIO0->FIOSET = RS;
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    delay_ms(2);
}

void lcd_init() {
    delay_ms(20);
    lcd_send_nibble(0x03);
    delay_ms(5);
    lcd_send_nibble(0x03);
    delay_us(100);
    lcd_send_nibble(0x03);
    lcd_send_nibble(0x02);

    lcd_cmd(0x28); // 4-bit, 2 lines, 5x8
    lcd_cmd(0x0C); // Display on, cursor off
    lcd_cmd(0x06); // Increment cursor
    lcd_cmd(0x01); // Clear display
}

void lcd_print(char *msg) {
    int i = 0;
    while (msg[i]) {
        lcd_data(msg[i++]);
    }
}

// ---------- Stepper Motor ----------
void stepper_rotate(int direction, int steps) {
    int i, j;
    for (j = 0; j < steps; j++) {
        for (i = 0; i < 4; i++) {
            int index = direction ? i : 3 - i;
            LPC_GPIO0->FIOPIN &= ~STEPPER_MASK;
            LPC_GPIO0->FIOPIN |= step_sequence[index];
            delay_ms(10);
        }
    }
    LPC_GPIO0->FIOPIN &= ~STEPPER_MASK;
}

// ---------- Main ----------
int main(void) {
    SystemInit();
    init_GPIO();
    init_timer1();
    lcd_init();

    while (1) {
        uint32_t distance = measure_distance_cm();

        if (distance > 0 && distance < 30) {
            LPC_GPIO0->FIOSET = (1 << LED_PIN); // Turn on LED

            lcd_cmd(0x01); // Clear
            lcd_cmd(0x80);
            lcd_print("Dustbin Open");

            stepper_rotate(0, 28);  // Anticlockwise 180°

            delay_ms(500);

            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_print("Dustbin Close");

            stepper_rotate(1, 28);  // Clockwise 180°
        } else {
            LPC_GPIO0->FIOCLR = (1 << LED_PIN); // Turn off LED
        }

        delay_ms(300);
    }
}