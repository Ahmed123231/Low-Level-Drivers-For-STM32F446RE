/**
 * @file  SYSCFG_Program.c
 * @brief This file contains the implementation of the SYSCFG (System Configuration)
 *        driver for configuring EXTI (External Interrupt) lines on the STM32F446RE
 *        microcontroller. The driver provides functions to configure the EXTI line
 *        source and trigger type for interrupt handling.
 */

#include <stdint.h>
#include "SYSCFG_Interface.h"
#include "SYSCFG_Private.h"
#include "STM32F446xx.h"

/**
 * @brief Configures the EXTI port for the specified line number.
 *
 * This function sets the EXTI line's source port (like GPIO port A, B, etc.)
 * for the given EXTI line.
 *
 * @param[in] copy_PortNum  The port to configure for the EXTI line.
 * @param[in] copy_LineNum  The EXTI line number (0 to 15).
 *
 * @return void
 */
void SYSCFG_voidSetEXTIPort(SYSCFG_Port_t copy_PortNum ,SYSCFG_IRQNum copy_LineNum )
{
    // Find the register (EXTICR0-EXTICR3)
    uint8_t Local_u8RegisterNum = (uint8_t)(copy_LineNum / 4);

    // Find the bit position inside the register (each register handles 4 EXTI lines)
    uint8_t Local_u8BitNum = (uint8_t)((copy_LineNum % 4) * 4);

    // Clear the previous configuration for the corresponding bits
    SYSCFG->EXTICR[Local_u8RegisterNum] &= ~(0b1111 << Local_u8BitNum);

    // Set the new configuration for the corresponding bits
    SYSCFG->EXTICR[Local_u8RegisterNum] |= (copy_PortNum << Local_u8BitNum);
}
