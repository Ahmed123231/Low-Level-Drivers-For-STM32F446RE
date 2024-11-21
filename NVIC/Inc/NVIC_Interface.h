/**
 * @file NVIC_Interface.h
 * @brief Interface for the Nested Vectored Interrupt Controller (NVIC) driver.
 *
 * This file provides the function declarations required to control NVIC functionality
 * for enabling, disabling, setting priority, and managing interrupt states. 
 * All functions follow a consistent API for use with NVIC interrupts.
 *
 * @author Ahmed Atef
 * @date 2024-10-26
 */

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#include <stdint.h>  /**< Ensure the use of uint32_t data types */






/**
 * @enum IRQn_Type
 * @brief Enumerates IRQ numbers for STM32F4xx peripherals, arranged by their positions in the vector table.
 */
typedef enum {

    WWDG,                 /**< Window Watchdog Interrupt */
    PVD,                  /**< PVD through EXTI Line detection Interrupt */
    TAMP_STAMP,           /**< Tamper and TimeStamp Interrupt */
    RTC_WKUP,             /**< RTC Wakeup Interrupt through EXTI Line */
    FLASH,                /**< Flash global Interrupt */
    RCC,                  /**< RCC global Interrupt */
    EXTI0,                /**< EXTI Line0 Interrupt */
    EXTI1,                /**< EXTI Line1 Interrupt */
    EXTI2,                /**< EXTI Line2 Interrupt */
    EXTI3,                /**< EXTI Line3 Interrupt */
    EXTI4,                /**< EXTI Line4 Interrupt */
    DMA1_Stream0,         /**< DMA1 Stream 0 global Interrupt */
    DMA1_Stream1,         /**< DMA1 Stream 1 global Interrupt */
    DMA1_Stream2,         /**< DMA1 Stream 2 global Interrupt */
    DMA1_Stream3,         /**< DMA1 Stream 3 global Interrupt */
    DMA1_Stream4,         /**< DMA1 Stream 4 global Interrupt */
    DMA1_Stream5,         /**< DMA1 Stream 5 global Interrupt */
    DMA1_Stream6,         /**< DMA1 Stream 6 global Interrupt */
    ADC,                  /**< ADC1, ADC2 and ADC3 global Interrupts */
    CAN1_TX,              /**< CAN1 TX Interrupt */
    CAN1_RX0,             /**< CAN1 RX0 Interrupt */
    CAN1_RX1,             /**< CAN1 RX1 Interrupt */
    CAN1_SCE,             /**< CAN1 SCE Interrupt */
    EXTI9_5,              /**< EXTI Line[9:5] Interrupts */
    TIM1_BRK_TIM9,        /**< TIM1 Break and TIM9 global Interrupts */
    TIM1_UP_TIM10,        /**< TIM1 Update and TIM10 global Interrupts */
    TIM1_TRG_COM_TIM11,   /**< TIM1 Trigger and Commutation and TIM11 global Interrupts */
    TIM1_CC,              /**< TIM1 Capture Compare Interrupt */
    TIM2,                 /**< TIM2 global Interrupt */
    TIM3,                 /**< TIM3 global Interrupt */
    TIM4,                 /**< TIM4 global Interrupt */
    I2C1_EV,              /**< I2C1 Event Interrupt */
    I2C1_ER,              /**< I2C1 Error Interrupt */
    I2C2_EV,              /**< I2C2 Event Interrupt */
    I2C2_ER,              /**< I2C2 Error Interrupt */
    SPI1,                 /**< SPI1 global Interrupt */
    SPI2,                 /**< SPI2 global Interrupt */
    USART1,               /**< USART1 global Interrupt */
    USART2,               /**< USART2 global Interrupt */
    USART3,               /**< USART3 global Interrupt */
    EXTI5_10,             /**< EXTI Line[10:5] Interrupts */
    RTC_Alarm,            /**< RTC Alarm (A and B) through EXTI Line Interrupt */
    OTG_FS_WKUP,          /**< USB OTG FS Wakeup through EXTI line interrupt */
    TIM8_BRK_TIM12,       /**< TIM8 Break and TIM12 global Interrupts */
    TIM8_UP_TIM13,        /**< TIM8 Update and TIM13 global Interrupts */
    TIM8_TRG_COM_TIM14,   /**< TIM8 Trigger and Commutation and TIM14 global Interrupts */
    TIM8_CC,              /**< TIM8 Capture Compare Interrupt */
    DMA1_Stream7,         /**< DMA1 Stream7 global Interrupt */
    FMC,                  /**< FMC global Interrupt */
    SDIO,                 /**< SDIO global Interrupt */
    TIM5,                 /**< TIM5 global Interrupt */
    SPI3,                 /**< SPI3 global Interrupt */
    UART4,                /**< UART4 global Interrupt */
    UART5,                /**< UART5 global Interrupt */
    TIM6_DAC,             /**< TIM6 global and DAC1&2 underrun error Interrupts */
    TIM7,                 /**< TIM7 global Interrupt */
    DMA2_Stream0,         /**< DMA2 Stream 0 global Interrupt */
    DMA2_Stream1,         /**< DMA2 Stream 1 global Interrupt */
    DMA2_Stream2,         /**< DMA2 Stream 2 global Interrupt */
    DMA2_Stream3,         /**< DMA2 Stream 3 global Interrupt */
    DMA2_Stream4,         /**< DMA2 Stream 4 global Interrupt */
    CAN2_TX = 63,         /**< CAN2 TX Interrupt */
    CAN2_RX0,             /**< CAN2 RX0 Interrupt */
    CAN2_RX1,             /**< CAN2 RX1 Interrupt */
    CAN2_SCE,             /**< CAN2 SCE Interrupt */
    OTG_FS,               /**< USB OTG FS global Interrupt */
    DMA2_Stream5,         /**< DMA2 Stream 5 global Interrupt */
    DMA2_Stream6,         /**< DMA2 Stream 6 global Interrupt */
    DMA2_Stream7,         /**< DMA2 Stream 7 global Interrupt */
    USART6,               /**< USART6 global Interrupt */
    I2C3_EV,              /**< I2C3 Event Interrupt */
    I2C3_ER,              /**< I2C3 Error Interrupt */
    OTG_HS_EP1_OUT,       /**< USB OTG HS End Point 1 Out global Interrupt */
    OTG_HS_EP1_IN,        /**< USB OTG HS End Point 1 In global Interrupt */
    OTG_HS_WKUP,          /**< USB OTG HS Wakeup through EXTI interrupt */
    OTG_HS,               /**< USB OTG HS global Interrupt */
    DCMI,                 /**< DCMI global Interrupt */
    FPU = 81,             /**< Floating point unit Interrupt */
    SPI4 = 84,            /**< SPI4 global Interrupt */
    SAI1 = 87,            /**< SAI1 global Interrupt */
    SAI2 = 91,            /**< SAI2 global Interrupt */
    QuadSPI,              /**< QuadSPI global Interrupt */
    HDMI_CEC,             /**< HDMI-CEC global Interrupt */
    SPDIF_Rx,             /**< SPDIF-Rx global Interrupt */
    FMPI2C1,              /**< FMPI2C1 Event Interrupt */
    FMPI2C1_error         /**< FMPI2C1 Error Interrupt */

} IRQn_Type;



/**
 * @brief Enables the specified IRQ interrupt.
 *
 * Sets the enable bit for the specified IRQ interrupt, allowing it
 * to trigger when activated by an event.
 *
 * @param[in] IRQn  IRQ number to enable of type IRQn_Type.
 */
void NVIC_EnableIRQ(IRQn_Type IRQn);

/**
 * @brief Disables the specified IRQ interrupt.
 *
 * Clears the enable bit for the specified IRQ interrupt, preventing it
 * from triggering until re-enabled.
 *
 * @param[in] IRQn  IRQ number to disable of type IRQn_Type.
 */
void NVIC_DisableIRQ(IRQn_Type IRQn);

/**
 * @brief Sets the pending bit for the specified IRQ interrupt.
 *
 * Forces the specified interrupt to be pending, even if it is not
 * triggered by an external event.
 *
 * @param[in] IRQn  IRQ number to set as pending of type IRQn_Type.
 */
void NVIC_SetPendingIRQ(IRQn_Type IRQn);

/**
 * @brief Clears the pending bit for the specified IRQ interrupt.
 *
 * Clears the pending status of an interrupt, marking it as inactive.
 *
 * @param[in] IRQn  IRQ number to clear as pending of type IRQn_Type.
 */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn);

/**
 * @brief Retrieves the pending state of the specified IRQ interrupt.
 *
 * Returns the pending status of an interrupt, indicating whether it is currently marked as pending.
 *
 * @param[in] IRQn  IRQ number to check of type IRQn_Type.
 * @return uint32_t Returns a non-zero value if the interrupt is pending; 0 otherwise.
 */
uint8_t NVIC_GetPendingIRQ(IRQn_Type IRQn);

/**
 * @brief Sets the priority level for the specified IRQ interrupt.
 *
 * Sets the priority level for the specified IRQ interrupt, where a lower priority value indicates a higher priority.
 *
 * @param[in] IRQn     IRQ number to set the priority for, of type IRQn_Type.
 * @param[in] priority Priority level to set.
 */
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);

/**
 * @brief Retrieves the priority level of the specified IRQ interrupt.
 *
 * Returns the priority level of the specified IRQ interrupt.
 *
 * @param[in] IRQn  IRQ number to check of type IRQn_Type.
 * @return uint32_t Returns the priority level of the interrupt.
 */
uint32_t NVIC_GetPriority(IRQn_Type IRQn);

/**
 * @brief Reads the active flag status of the specified IRQ interrupt.
 *
 * Returns whether the specified interrupt is currently active.
 *
 * @param[in] IRQn  IRQ number to check of type IRQn_Type.
 * @return uint32_t Return the IRQ number of the active interrupt.
 */
uint8_t NVIC_GetActive(IRQn_Type IRQn);

#endif /* NVIC_INTERFACE_H */
