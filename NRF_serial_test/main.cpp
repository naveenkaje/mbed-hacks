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
/*
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
			
			// LED Debug, to see if we are reading
			if (c & 0x01)
				led1 = 1;
			else
				led1 = 0;
        }
    }
}
*/

#include "mbed.h"
#include "debug_io.h"
#include "mbed_critical.h"


int main()
{
    uint8_t buf[1];
    uint8_t prev = 0xff;
    uint32_t total = 0;
    uint32_t mismatch = 0;
    UARTSerial serial(USBTX, USBRX, 115200);
//    serial.set_flow_control(SerialBase::RTSCTS, STDIO_UART_RTS, STDIO_UART_CTS);

    while (true) {
        ssize_t size = serial.read(buf, sizeof(buf));

        static uint32_t count = 0;
        count++;
        if ((count % 100) == 0) {
            core_util_critical_section_enter();
            wait_us(100);
            core_util_critical_section_exit();
        }

        for (ssize_t i = 0; i < size; i++) {
            if (buf[i] != ((prev + 1) & 0xFF)) {
                char printf_buf[256];
                int len = sprintf(printf_buf, "Mismatch! Expected 0x%x got 0x%x\r\n", prev + 1, buf[i]);
                serial.write(printf_buf, len);
                printf("Mismatch! Expected %i got %i\r\n", prev + 1, buf[i]);
                set_pin(5, 1);
                mismatch++;
                set_pin(5, 0);
            }
            prev = buf[i];
            total++;
            if (total % 1000 == 0) {
                char printf_buf[256];
                int len = sprintf(printf_buf, "Received %i bytes mismatch %i\r\n", total, mismatch);
                serial.write(printf_buf, len);
            }
        }

    }
    return 0;
}

