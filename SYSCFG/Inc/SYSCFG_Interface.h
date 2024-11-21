#ifndef SYSCFG_INTERFACE_H
#define SYSCFG_INTERFACE_H


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
	SYSCFG_PIN0,  /**< External Interrupt Line 0 */
	SYSCFG_PIN1,  /**< External Interrupt Line 1 */
	SYSCFG_PIN2,  /**< External Interrupt Line 2 */
	SYSCFG_PIN3,  /**< External Interrupt Line 3 */
	SYSCFG_PIN4,  /**< External Interrupt Line 4 */
	SYSCFG_PIN5,  /**< External Interrupt Line 5 */
	SYSCFG_PIN6,  /**< External Interrupt Line 6 */
	SYSCFG_PIN7,  /**< External Interrupt Line 7 */
	SYSCFG_PIN8,  /**< External Interrupt Line 8 */
	SYSCFG_PIN9,  /**< External Interrupt Line 9 */
	SYSCFG_PIN10, /**< External Interrupt Line 10 */
	SYSCFG_PIN11, /**< External Interrupt Line 11 */
	SYSCFG_PIN12, /**< External Interrupt Line 12 */
	SYSCFG_PIN13, /**< External Interrupt Line 13 */
	SYSCFG_PIN14, /**< External Interrupt Line 14 */
	SYSCFG_PIN15  /**< External Interrupt Line 15 */

} SYSCFG_IRQNum;



typedef enum
{
	SYSCFG_PORTA,
	SYSCFG_PORTB,
	SYSCFG_PORTC,
	SYSCFG_PORTD,
	SYSCFG_PORTE,
	SYSCFG_PORTF,
	SYSCFG_PORTG,
	SYSCFG_PORTH



}SYSCFG_Port_t;


 void SYSCFG_voidSetEXTIPort(SYSCFG_Port_t copy_PortNum ,SYSCFG_IRQNum copy_LineNum );




#endif
