#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/**
 * @file EXTI_Interface.h
 * @brief Interface for the External Interrupt (EXTI) module.
 *
 * This file contains enumerations, structures, and function prototypes
 * used to configure and control the EXTI peripheral for the STM32F446xx microcontroller.
 *
 * @version 1.0
 * @date 2024-11-20
 *
 * @note Ensure that the EXTI_Config_t structure is properly initialized before usage.
 * @warning Do not pass NULL pointers to any function to avoid undefined behavior.
 */

/* Enumeration Definitions */

/**
 * @enum EXTI_IRQNum
 * @brief EXTI line numbers corresponding to pins.
 */
typedef enum
{
	EXTI_PIN0,  /**< External Interrupt Line 0 */
	EXTI_PIN1,  /**< External Interrupt Line 1 */
	EXTI_PIN2,  /**< External Interrupt Line 2 */
	EXTI_PIN3,  /**< External Interrupt Line 3 */
	EXTI_PIN4,  /**< External Interrupt Line 4 */
	EXTI_PIN5,  /**< External Interrupt Line 5 */
	EXTI_PIN6,  /**< External Interrupt Line 6 */
	EXTI_PIN7,  /**< External Interrupt Line 7 */
	EXTI_PIN8,  /**< External Interrupt Line 8 */
	EXTI_PIN9,  /**< External Interrupt Line 9 */
	EXTI_PIN10, /**< External Interrupt Line 10 */
	EXTI_PIN11, /**< External Interrupt Line 11 */
	EXTI_PIN12, /**< External Interrupt Line 12 */
	EXTI_PIN13, /**< External Interrupt Line 13 */
	EXTI_PIN14, /**< External Interrupt Line 14 */
	EXTI_PIN15  /**< External Interrupt Line 15 */
} EXTI_IRQNum;

/**
 * @enum EXTI_TiggerSrc_t
 * @brief Trigger source configurations for EXTI.
 */
typedef enum
{
    FALLING_TRIG,        /**< Trigger on falling edge */
    RISING_TRIG,         /**< Trigger on rising edge */
    FALLING_RISING_TRIG  /**< Trigger on both edges */
} EXTI_TiggerSrc_t;

/**
 * @enum EXTI_InitState_t
 * @brief Initialization state of the EXTI line.
 */
typedef enum
{
    ENABLED,  /**< Enable EXTI line */
    DISABLED  /**< Disable EXTI line */
} EXTI_InitState_t;

/* Structure Definition */

/**
 * @struct EXTI_Config_t
 * @brief Configuration structure for the EXTI module.
 *
 * This structure holds the configuration parameters for an EXTI line, including
 * the pin number, trigger source, initialization state, and callback function.
 */
typedef struct
{
    EXTI_IRQNum PinNum;              /**< EXTI line number (0-15) */
    EXTI_TiggerSrc_t Trigger_Src;    /**< Trigger source configuration */
    EXTI_InitState_t Init_State;     /**< Initialization state (enabled/disabled) */
    void (*CallBackFunc)(void);      /**< Callback function pointer */
} EXTI_Config_t;

/* Function Prototypes */

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
uint8_t EXTI_u8Init(EXTI_Config_t* copy_cfg);

/**
 * @brief Sets the trigger source for a specified EXTI line.
 *
 * @param[in]  copy_TriggerSrc  Trigger source type (RISING, FALLING, or BOTH).
 * @param[in]  Copy_LineNum     EXTI line number (0-15).
 *
 * @return uint8_t
 * @retval OK   Operation successful.
 * @retval NOK  Invalid trigger source or line number.
 */
uint8_t EXTI_u8SetTriggerSrc(EXTI_TiggerSrc_t copy_TriggerSrc, EXTI_IRQNum Copy_LineNum);

/**
 * @brief Enables the interrupt for a specified EXTI line.
 *
 * @param[in]  Copy_LineNum  EXTI line number (0-15).
 *
 * @note This function modifies the Interrupt Mask Register (IMR).
 */
void EXTI_u8EnableIRQ(EXTI_IRQNum Copy_LineNum);

/**
 * @brief Disables the interrupt for a specified EXTI line.
 *
 * @param[in]  Copy_LineNum  EXTI line number (0-15).
 *
 * @note This function modifies the Interrupt Mask Register (IMR).
 */
void EXTI_u8DisableIRQ(EXTI_IRQNum Copy_LineNum);

/**
 * @brief Clears the pending flag for a specified EXTI line.
 *
 * @param[in]  Copy_LineNum  EXTI line number (0-15).
 *
 * @note Writing '1' to the Pending Register (PR) clears the corresponding flag.
 */
void EXTI_u8ClearPendingFlag(EXTI_IRQNum Copy_LineNum);

/**
 * @brief Reads the pending flag for a specified EXTI line.
 *
 * @param[in]   Copy_LineNum     EXTI line number (0-15).
 * @param[out]  copy_flagStatus  Pointer to store the pending flag status.
 *
 * @return uint8_t
 * @retval OK   Operation successful.
 * @retval NOK  NULL pointer passed for flag status.
 *
 * @note The pending flag status is stored as '1' if set, or '0' if cleared.
 */
uint8_t EXTI_u8ReadPendingFlag(EXTI_IRQNum Copy_LineNum, uint8_t* copy_flagStatus);

#endif /* EXTI_INTERFACE_H */
