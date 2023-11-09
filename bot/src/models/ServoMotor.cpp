// #include "models/ServoMotor.h"
// #include "ESP32Servo.h"

// /**
//  * @brief Construct a new Servo Motor:: Servo Motor object
//  *
//  * @param pin as pin the servo
//  */
// ServoMotor::ServoMotor(uint8_t pin)
// {
// 	enabled   = false;
// 	this->min = MIN_ANGLE_IN_US;
// 	this->max = MAX_ANGLE_IN_US;

// 	servo.attach(pin, this->min, this->max);
// }

// /**
//  * @brief Toggle the servo enable variable
//  *
//  * @param enable
//  */
// void ServoMotor::update(bool enable)
// {
// 	this->enabled = enable;
// }

// /**
//  * @brief Reset the servo to its initial state/angle.
//  *
//  */
// void ServoMotor::reset(void)
// {
// 	write(MIN_ANGLE_IN_US);
// 	flipped = false;
// }

// void ServoMotor::write(uint32_t usec)
// {
// 	usec = min(usec, this->max);
// 	usec = max(usec, this->min);
// 	servo.writeMicroseconds(usec);
// }

// /**
//  * @brief Flip the servo motor.
//  *
//  */
// void ServoMotor::flip(void)
// {
// 	if (!enabled) {
// 		return;
// 	}
// 	write(isFlipped() ? MAX_ANGLE_IN_US : MIN_ANGLE_IN_US);
// 	flipped = !flipped;
// }

// bool ServoMotor::isFlipped(void)
// {
// 	return flipped == true;
// }
