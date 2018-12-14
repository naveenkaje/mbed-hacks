/* mbed Example Program
 * Copyright (c) 2006-2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"

// Read temperature from LM75BD

I2C i2c(I2C_SDA0, I2C_SCL0);
DigitalOut led1(LED1);

const int addr7bit = 0x48;      // 7 bit I2C address
const int addr8bit = 0x48 << 1; // 8bit I2C address, 0x90

int main() {
        Serial ser(USBTX, USBRX);
        char cmd[2];

        ser.printf("begin\n\r");
        led1 = 1;
        wait(0.5);
        led1 = 0;
        wait(5);

        while (1) {
                cmd[0] = 0x01;
                cmd[1] = 0x00;
				led1 = 1;
                wait(0.5);
                led1 = 0;
                i2c.write(addr8bit, cmd, 2);

                led1 = !led1;
                wait(0.25);
                led1 = !led1;
                wait(0.25);

                cmd[0] = 0x00;
                i2c.write(addr8bit, cmd, 1);
                i2c.read( addr8bit, cmd, 2);

                float tmp = (float((cmd[0]<<8)|cmd[1]) / 256.0);
                ser.printf("Temp = %.2f\n\r", tmp);
            }
}
