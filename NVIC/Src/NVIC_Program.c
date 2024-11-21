/**
 * @file NVIC_Interface.c
 * @brief Program for the Nested Vectored Interrupt Controller (NVIC) driver.
 *
 * This file provides the function definitions required to control NVIC functionality
 * for enabling, disabling, setting priority, and managing interrupt states. 
 * All functions follow a consistent API for use with NVIC interrupts.
 *
 * @author Ahmed Atef
 * @date 2024-10-26
 */

#include "../Inc/NVIC_Interface.h"
#include "../Inc/NVIC_Private.h"
#include "../../../LIB/STM32F446xx.h"
#include "../../../LIB/ErrType.h"


/**
 * @brief Enables the specified IRQ in the NVIC.
 * @param[in] IRQn IRQ number to enable, as defined in IRQn_Type.
 * @note The function calculates the appropriate register and bit based on the IRQ number.
 */
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    uint8_t RegNum = (uint8_t)(IRQn / 32U);  /**< Register index in the ISER array */
    uint8_t BitNum = (uint8_t)(IRQn % 32U);  /**< Bit position within the register */

    NVIC->ISER[RegNum] = (uint32_t)(1UL << BitNum); /**< Enable the IRQ by setting the corresponding bit */
}

/**
 * @brief Disables the specified IRQ interrupt.
 * 
 * Clears the enable bit for the specified IRQ interrupt, preventing it
 * from triggering until re-enabled.
 * 
 * @param[in] IRQn IRQ number to disable of type IRQn_Type.
 */
void NVIC_DisableIRQ(IRQn_Type IRQn)
{
    uint8_t RegNum = (uint8_t)(IRQn / 32U);  /**< Register index in the ICER array */
    uint8_t BitNum = (uint8_t)(IRQn % 32U);  /**< Bit position within the register */

    NVIC->ICER[RegNum] = (uint32_t)(1UL << BitNum); /**< Disable the IRQ by clearing the corresponding bit */
}

/**
 * @brief Sets the pending bit for the specified IRQ interrupt.
 * 
 * Forces the specified interrupt to be pending, even if it is not
 * triggered by an external event.
 * 
 * @param[in] IRQn IRQ number to set as pending of type IRQn_Type.
 */
void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    uint8_t RegNum = (uint8_t)(IRQn / 32U);  /**< Register index in the ISPR array */
    uint8_t BitNum = (uint8_t)(IRQn % 32U);  /**< Bit position within the register */

    NVIC->ISPR[RegNum] = (uint32_t)(1UL << BitNum); /**< Set the Pending IRQ by setting the corresponding bit */
}

/**
 * @brief Clears the pending bit for the specified IRQ interrupt.
 * 
 * Clears the pending status of an interrupt, marking it as inactive.
 * 
 * @param[in] IRQn IRQ number to clear as pending of type IRQn_Type.
 */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    uint8_t RegNum = (uint8_t)(IRQn / 32U);  /**< Register index in the ICPR array */
    uint8_t BitNum = (uint8_t)(IRQn % 32U);  /**< Bit position within the register */

    NVIC->ICPR[RegNum] = (uint32_t)(1UL << BitNum); /**< Clear the Pending IRQ by setting the corresponding bit */
}

/**
 * @brief Retrieves the pending state of the specified IRQ interrupt.
 * 
 * Returns the pending status of an interrupt, indicating whether it is currently marked as pending.
 * 
 * @param[in] IRQn IRQ number to check of type IRQn_Type.
 * @return uint32_t Returns 1 if the interrupt is pending; 0 otherwise.
 */
uint8_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
    uint8_t RegNum = (uint8_t)(IRQn / 32U);  /**< Register index in the ISPR array */
    uint8_t BitNum = (uint8_t)(IRQn % 32U);  /**< Bit position within the register */

    uint8_t PendingStatus = 0U;

   PendingStatus=(NVIC->ISPR[RegNum] & (1UL << BitNum)) ;

    return PendingStatus;
}


/**
 * @brief Sets the priority level for the specified IRQ interrupt.
 *
 * Sets the priority level for the specified IRQ interrupt, where a lower priority value indicates a higher priority.
 *
 * @param[in] IRQn     IRQ number to set the priority for, of type IRQn_Type.
 * @param[in] priority Priority level to set.
 */
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    uint8_t RegIndex=0;    /**< Register index in the IPR array */
    uint8_t PriorityPos=0; /**< Position of priority within the IPR register */

    /* Ensure priority is within the 4-bit range (0-15) */
    if (priority > 15U)
    {
        priority = 15U;
    }
    else{
    /* Calculate the register index and position within the register */
    RegIndex = (uint8_t)(IRQn / 4U);          /**< Each IPR register holds 4 IRQ priorities */
    PriorityPos = (uint8_t)((IRQn % 4U) * 8U); /**< Each priority field is 8 bits */

    /* Assign the 4-bit priority level to the specific IRQ */
    NVIC->IPR[RegIndex] &= ~(0xF0U << PriorityPos);       /**< Clear the priority field */
    NVIC->IPR[RegIndex] |= ((priority & 0xFU) << (PriorityPos + 4U)); /**< Set the priority */

    }

}

/**
 * @brief Retrieves the priority level of the specified IRQ interrupt.
 *
 * Returns the priority level of the specified IRQ interrupt.
 *
 * @param[in] IRQn  IRQ number to check of type IRQn_Type.
 * @return uint32_t Returns the priority level of the interrupt (0-15).
 */
uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{
    uint8_t RegIndex=0;    /**< Register index in the IPR array */
    uint8_t PriorityPos=0; /**< Position of priority within the register */
    uint32_t priority=0;   /**< Priority level to return */

    /* Calculate the register index and bit position */
    RegIndex = (uint8_t)(IRQn / 4U);          /**< Each IPR register holds 4 IRQ priorities */
    PriorityPos = (uint8_t)((IRQn % 4U) * 8U); /**< Each priority field is 8 bits */

    /* Read the priority from the IPR register, masking to only upper 4 bits */
    priority = (NVIC->IPR[RegIndex] >> (PriorityPos + 4U)) & 0x0FU;

    return priority;
}

/**
 * @brief Reads the active flag status of the specified IRQ interrupt.
 *
 * Returns whether the specified interrupt is currently active.
 *
 * @param[in] IRQn  IRQ number to check of type IRQn_Type.
 * @return uint8_t Returns 1 if the IRQ is active; 0 otherwise.
 */
uint8_t NVIC_GetActive(IRQn_Type IRQn)
{
    uint8_t RegNum=0;      /**< Register index in the IABR array */
    uint8_t BitNum=0;      /**< Bit position within the register */
    uint8_t isActive=0;    /**< Active status to return */

    /* Calculate the register index and bit position */
    RegNum = (uint8_t)(IRQn / 32U);  /**< Each IABR register holds 32 IRQ flags */
    BitNum = (uint8_t)(IRQn % 32U);  /**< Specific bit within the register */

    /* Check if the bit is set in the IABR register */
    isActive = (uint8_t)((NVIC->IABR[RegNum] & (1UL << BitNum)) ? 1U : 0U);

    return isActive;
}
