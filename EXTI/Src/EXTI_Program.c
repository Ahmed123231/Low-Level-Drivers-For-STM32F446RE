/**
 * @file    EXTI_Driver.c
 * @brief   Implementation of the EXTI driver for STM32F446xx microcontroller.
 * @details This file provides functions to configure and control the EXTI peripheral,
 *          including initialization, enabling/disabling interrupts, and handling callback functions.
 */

#include <stdint.h>
#include <stdlib.h>
#include "STM32F446xx.h"
#include "ErrType.h"
#include "EXTI_Interface.h"
#include "EXTI_Private.h"

/**
 * @brief Global array of pointers to functions for handling EXTI callbacks.
 * @note  Each index corresponds to an EXTI line.
 */
static void (*EXTI_CallBackFunctionPtr[EXTI_LINES_NUM])(void) = {NULL};

/**
 * @brief Initializes the EXTI peripheral with the specified configuration.
 *
 * @param[in]  copy_cfg  Pointer to a configuration structure of type EXTI_Config_t.
 *
 * @return uint8_t
 * @retval OK             Operation successful.
 * @retval NOK            Invalid trigger source or state.
 * @retval NULL_PTR_ERR   The provided configuration pointer is NULL.
 *
 * @note The configuration structure must be properly initialized before calling this function.
 */
uint8_t EXTI_u8Init(EXTI_Config_t* copy_cfg)
{
    uint8_t Loc_u8ErrorState = OK;

    /* Validate input parameters */
    if ((copy_cfg != NULL) && (copy_cfg->PinNum < EXTI_LINES_NUM))
    {
        /* Configure the trigger source */
        switch (copy_cfg->Trigger_Src)
        {
            case RISING_TRIG:
                EXTI->RTSR |= (1U << (copy_cfg->PinNum));  /**< Enable rising edge trigger */
                EXTI->FTSR &= ~(1U << (copy_cfg->PinNum)); /**< Disable falling edge trigger */
                break;
            case FALLING_TRIG:
                EXTI->FTSR |= (1U << (copy_cfg->PinNum));  /**< Enable falling edge trigger */
                EXTI->RTSR &= ~(1U << (copy_cfg->PinNum)); /**< Disable rising edge trigger */
                break;
            case FALLING_RISING_TRIG:
                EXTI->RTSR |= (1U << (copy_cfg->PinNum));  /**< Enable both triggers */
                EXTI->FTSR |= (1U << (copy_cfg->PinNum));
                break;
            default:
                Loc_u8ErrorState = NOK;
                break;
        }

        /* Configure interrupt enable/disable state */
        if (copy_cfg->Init_State == ENABLED)
        {
            EXTI->IMR |= (1U << (copy_cfg->PinNum)); /**< Enable interrupt for the specified line */
        }
        else if (copy_cfg->Init_State == DISABLED)
        {
            EXTI->IMR &= ~(1U << (copy_cfg->PinNum)); /**< Disable interrupt for the specified line */
        }
        else
        {
            Loc_u8ErrorState = NOK;
        }

        /* Set the callback function pointer */
        if (copy_cfg->CallBackFunc != NULL)
        {
            EXTI_CallBackFunctionPtr[copy_cfg->PinNum] = copy_cfg->CallBackFunc;
        }
        else
        {
            Loc_u8ErrorState = NULL_PTR_ERR;
        }
    }
    else
    {
        Loc_u8ErrorState = NULL_PTR_ERR;
    }

    return Loc_u8ErrorState;
}

/**
 * @brief Sets the trigger source for the specified EXTI line.
 *
 * @param[in] copy_TriggerSrc The desired trigger source (rising, falling, or both).
 * @param[in] Copy_LineNum    The EXTI line number.
 *
 * @return uint8_t
 * @retval OK  Operation successful.
 * @retval NOK Invalid trigger source.
 */
uint8_t EXTI_u8SetTriggerSrc(EXTI_TiggerSrc_t copy_TriggerSrc, EXTI_IRQNum Copy_LineNum)
{
    uint8_t Loc_u8ErrorState = OK;

    switch (copy_TriggerSrc)
    {
        case RISING_TRIG:
            EXTI->RTSR |= (1U << Copy_LineNum);  /**< Enable rising edge trigger */
            EXTI->FTSR &= ~(1U << Copy_LineNum); /**< Disable falling edge trigger */
            break;
        case FALLING_TRIG:
            EXTI->FTSR |= (1U << Copy_LineNum);  /**< Enable falling edge trigger */
            EXTI->RTSR &= ~(1U << Copy_LineNum); /**< Disable rising edge trigger */
            break;
        case FALLING_RISING_TRIG:
            EXTI->RTSR |= (1U << Copy_LineNum);  /**< Enable both triggers */
            EXTI->FTSR |= (1U << Copy_LineNum);
            break;
        default:
            Loc_u8ErrorState = NOK;
            break;
    }

    return Loc_u8ErrorState;
}

/**
 * @brief Enables the specified EXTI line interrupt.
 *
 * @param[in] Copy_LineNum The EXTI line number to enable.
 */
void EXTI_u8EnableIRQ(EXTI_IRQNum Copy_LineNum)
{
    EXTI->IMR |= (1U << Copy_LineNum); /**< Unmask the interrupt line */
}

/**
 * @brief Disables the specified EXTI line interrupt.
 *
 * @param[in] Copy_LineNum The EXTI line number to disable.
 */
void EXTI_u8DisableIRQ(EXTI_IRQNum Copy_LineNum)
{
    EXTI->IMR &= ~(1U << Copy_LineNum); /**< Mask the interrupt line */
}

/**
 * @brief Clears the pending flag for the specified EXTI line.
 *
 * @param[in] Copy_LineNum The EXTI line number.
 */
void EXTI_u8ClearPendingFlag(EXTI_IRQNum Copy_LineNum)
{
    EXTI->PR = (1U << Copy_LineNum); /**< Clear the pending flag */
}

/**
 * @brief Reads the pending flag for the specified EXTI line.
 *
 * @param[in]  Copy_LineNum    The EXTI line number.
 * @param[out] copy_flagStatus Pointer to a variable to store the flag status (1 if set, 0 otherwise).
 *
 * @return uint8_t
 * @retval OK  Operation successful.
 * @retval NOK NULL pointer error.
 */
uint8_t EXTI_u8ReadPendingFlag(EXTI_IRQNum Copy_LineNum, uint8_t* copy_flagStatus)
{
    uint8_t Loc_u8ErrorState = OK;

    if (copy_flagStatus != NULL)
    {
        *copy_flagStatus = (uint8_t)((EXTI->PR >> Copy_LineNum) & 1U); /**< Read the flag status */
    }
    else
    {
        Loc_u8ErrorState = NOK;
    }

    return Loc_u8ErrorState;
}
