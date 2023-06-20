#include <Arduino.h>
#include <ServoMotor.h>
#include <unity.h>

void test_servo_motor() {
  ServoMotor motor(D7);
  motor.reset();

  TEST_ASSERT_FALSE(motor.isFlipped());

  motor.flip();
  TEST_ASSERT_FALSE(motor.isFlipped());

  motor.update(true);
  motor.flip();
  TEST_ASSERT_TRUE(motor.isFlipped());

  motor.update(false);
  motor.flip();
  TEST_ASSERT_TRUE(motor.isFlipped());
}

void setup()
{
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_servo_motor);
  UNITY_END();
}

void loop()
{
}
