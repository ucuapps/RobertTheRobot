/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2011, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *  * Neither the name of Willow Garage, Inc. nor the names of its
 *    contributors may be used to endorse or promote prducts derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STM32H7HARDWARE_H_
#define STM32H7HARDWARE_H_

#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"

/* There are two option for rosserial communication */
/* Via External USB to UART converter: UART7 on MCU side and ttyUSBx on the Linux side */
/* Via STLink on STM32 Nucleo board: USART7 on MCU side and ttyACMx on the Linux side  */
/* select appropriate way for rossserial communication */
/* It's NOT allowed to use both methods */

#define ROSSERIAL_STLINK_UART
//#define ROSSERIAL_EXT_USB_UART


class STM32F7Hardware
{
public:
	STM32F7Hardware()
	{
	}

	/*
	 * Method: init
	 * ----------------------------
	 *   Initialize the STM32F7 UART
	 *   parameters: none
	 *   returns: none
	 */
	void init(void)
	{
#ifdef ROSSERIAL_EXT_USB_UART
		MX_UART7_Init();
#else /* ROSSERIAL_STLINK_UART */
		MX_USART3_UART_Init();
#endif
	}

	/*
     * Method: read
	 * ----------------------------
	 *   Read a byte of data from ROS connection
	 *   parameters: none
	 *   returns: data, or -1 if there are no data
	 */
	int read(void)
	{
		int data;

#ifdef ROSSERIAL_EXT_USB_UART

		if (UART7->ISR & USART_ISR_ORE)
		{
			UART7->ICR = USART_ICR_ORECF; /* Clean Overrun Error */
		}

		if (UART7->ISR & USART_ISR_NE)
		{
			UART7->ICR = USART_ICR_NCF; /* Clean Noise Error */
		}

		if (UART7->ISR & USART_ISR_FE)
		{
			UART7->ICR = USART_ICR_FECF; /* Clean Framing Error */
		}

		if (!(UART7->ISR & USART_ISR_RXNE))
		{
			data = -1;
		}
		else
		{
			data = UART7->RDR;
		}

#else /* ROSSERIAL_STLINK_UART */

		if (USART3->ISR & USART_ISR_ORE)
		{
			USART3->ICR = USART_ICR_ORECF; /* Clean Overrun Error */
		}

	    if (USART3->ISR & USART_ISR_NE)
	    {
	    	USART3->ICR = USART_ICR_NCF; /* Clean Noise Error */
	    }


		if (USART3->ISR & USART_ISR_FE)
		{
			USART3->ICR = USART_ICR_FECF; /* Clean Framing Error */
		}

		if (!(USART3->ISR & USART_ISR_RXNE))
		{
			data = -1;
		}
		else
		{
			data = USART3->RDR;
		}
#endif

		return data;
	}

	/*
	 * Method: write
     * ----------------------------
	 *   Send a byte of data to ROS connection
	 *   parameters: pointer to data array, length of data
	 *   returns: none
	 */
	void write(uint8_t* data, uint32_t length)
	{
		for(uint32_t i = 0; i < length; i++)
		{
			//while (!(USART3->ISR & USART_ISR_TXE));
		    //USART3->TDR = data[i];
		    //while (!(USART3->ISR & USART_ISR_TC));
#ifdef ROSSERIAL_EXT_USB_UART

			if (UART7->ISR & USART_ISR_ORE)
			{
				UART7->ICR = USART_ICR_ORECF; /* Clean Overrun Error */
			}

			if (UART7->ISR & USART_ISR_NE)
			{
				UART7->ICR = USART_ICR_NCF; /* Clean Noise Error */
			}

			if (UART7->ISR & USART_ISR_FE)
			{
				UART7->ICR = USART_ICR_FECF; /* Clean Framing Error */
			}

			while (!(UART7->ISR & USART_ISR_TXE));
		    UART7->TDR = data[i];
			while (!(UART7->ISR & USART_ISR_TC));

#else /* ROSSERIAL_STLINK_UART */

			if (USART3->ISR & USART_ISR_ORE)
			{
				USART3->ICR = USART_ICR_ORECF; /* Clean Overrun Error */
			}

			if (USART3->ISR & USART_ISR_NE)
			{
				USART3->ICR = USART_ICR_NCF; /* Clean Noise Error */
			}

			if (USART3->ISR & USART_ISR_FE)
			{
				USART3->ICR = USART_ICR_FECF; /* Clean Framing Error */
			}

			while (!(USART3->ISR & USART_ISR_TXE));
			USART3->TDR = data[i];
			while (!(USART3->ISR & USART_ISR_TC));
#endif

		}
	}

	/*
	 * Method: time
	 * ----------------------------
     *   Returns milliseconds since start of program
	 *   parameters: none
	 *   returns: time in milliseconds
	 */
	uint32_t time(void)
	{
		return (uint32_t) xTaskGetTickCount();
	}

};

#endif /* STM32H7HARDWARE_H_ */
