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

DigitalOut led1(LED1);

int main() {
    RawSerial serial(USBTX, USBRX);

    serial.printf("Hello world\r\n");
    char c;

    while (true) {
        if (serial.readable()) {
			c = serial.getc();
			if (c == '\n' || c == '\r')
				serial.printf("\n\r");
			else
				serial.putc(c);
			
			/* LED Debug, to see if we are reading */
			if (c & 0x01)
				led1 = 1;
			else
				led1 = 0;
        }
    }
}
