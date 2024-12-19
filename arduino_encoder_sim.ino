void toggle_soft_pwm1(void)
{
    static bool value = false;

    value = !value;
    digitalWrite(2, value);
}
void toggle_soft_pwm2(void)
{
    static bool value = false;

    value = !value;
    digitalWrite(3, value);
}

void setup()
{
	pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
}

void loop()
{
    static unsigned long pwm_micros = 0;

    if ((micros() - pwm_micros) > 1000)
    {
        pwm_micros = micros();

        typedef enum
        {
            PWM_STATE_nA_nB,
            PWM_STATE_A_nB,
            PWM_STATE_A_B,
            PWM_STATE_nA_B
        } pwm_engine_states;

        static bool pwm1 = false;
        static bool pwm2 = false;
        static pwm_engine_states pwm_state = PWM_STATE_nA_nB;

        switch (pwm_state)
        {
        case PWM_STATE_nA_nB:
            toggle_soft_pwm1();
            pwm_state = PWM_STATE_A_nB;
            break;
        case PWM_STATE_A_nB:
            toggle_soft_pwm2();
            pwm_state = PWM_STATE_A_B;
            break;
        case PWM_STATE_A_B:
            toggle_soft_pwm1();
            pwm_state = PWM_STATE_nA_B;
            break;
        case PWM_STATE_nA_B:
            toggle_soft_pwm2();
            pwm_state = PWM_STATE_nA_nB;
            break;
        default:
            break;
        }
    }
}
