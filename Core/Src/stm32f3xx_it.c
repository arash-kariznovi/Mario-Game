/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "LiquidCrystal.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

extern int mario;
extern char * main_field[4][60];
extern char * field[4][60];
extern int mario_col;
int y;


float time_counter;
int coin_amount = 0;
int start_flag = 0;
int offset = 0;
int heart = 3;
int score = 0;
int not_pause = 1;

char score_char [3];
char coin_char [3];


/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */


void start(){

	start_flag = 1;
	for(int col=0; col <20; col++){
						  for(int row=0; row<4; row++){
							  field[row][col] = main_field[row][col];
						  }
						  }
	clear();
	  for(int col=0; col <20; col++){
					  for(int row=0; row<4; row++){
						  if(strcmp(main_field[row][col],"B")==0){

						  							  setCursor(col, row);
						  									  write(6);}
						  else if(strcmp(main_field[row][col],"G")==0){

							  setCursor(col, row);
									  write(0);

						  }else if(strcmp(main_field[row][col],"M")==0){

							  setCursor(col, row);
									  write(1);
						  }
						  else if(strcmp(main_field[row][col],"H")==0){
						  			  setCursor(col, row);
						  					  write(2);
						  		  }
						  else if(strcmp(main_field[row][col],"T")==0){
						  			  setCursor(col, row);
						  					  write(3);
						  		  }
						  else if(strcmp(main_field[row][col],"C")==0){
						  			  setCursor(col, row);
						  					  write(4);
						  		  }
					  }
				  }
	  setCursor(mario_col, 2);
	  		write(1);

	  		coin_amount= 0;

}

void win(){


	start_flag = 0;
	clear();
	setCursor(7, 1);
	print("YOU Win!");

	setCursor(7, 2);
	print("SCORE:");
	sprintf(score_char,"%d",score);
	setCursor(13, 2);
	print(score_char);

	setCursor(7, 3);
	print("Coins:");
	sprintf(coin_char,"%d",coin_amount);
	setCursor(13, 3);
	print(coin_char);


}


void lose(){

	mario_col = 1;
	not_pause=1;
if(heart==3){

	heart--;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 0);
	offset = 0;
	start();
	setCursor(mario_col, 2);

	write(1);

} else if (heart==2) {

	heart--;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 0);
	offset = 0;
	start();
	setCursor(mario_col, 2);

	write(1);

}else{
	start_flag = 0;
	heart--;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 0);
	clear();
	setCursor(7, 1);
	print("YOU LOSE!");

	setCursor(7, 2);
	print("SCORE:");
	sprintf(score_char,"%d",score);
	setCursor(13, 2);
	print(score_char);

	setCursor(7, 3);
	print("Coins:");
	sprintf(coin_char,"%d",coin_amount);
	setCursor(13, 3);
	print(coin_char);


}



}
 void jump(){


	 setCursor(mario_col, 2);
	 print(" ");

	 setCursor(mario_col, 1);

	 write(1);
	 HAL_Delay(50);
	 setCursor(mario_col, 1);
	 print(" ");



	 setCursor(mario_col, 0);
	 write(1);
	 HAL_Delay(50);
	 setCursor(mario_col, 0);
	 print(" ");

	 setCursor(mario_col, 1);
	 	 write(1);
	 	 HAL_Delay(50);
	 	setCursor(mario_col, 1);
	 	 print(" ");

	 	setCursor(mario_col, 2);
	 		 write(1);


	 		 if(strcmp(field[0][mario_col + offset-1],"C")==0){
	 			 	 			coin_amount++;
	 			 	 			field[0][mario_col + offset-1] = "N";
	 			 	 		}
	 		 if(strcmp(field[1][mario_col + offset-1],"C")==0){
	 			 			 	 			coin_amount++;
	 			 			 	 			field[1][mario_col + offset-1] = "N";
	 			 			 	 		}


 }

 void jumpAhead(){

	 setCursor(mario_col, 2);
	 print(" ");

	 setCursor(mario_col+1, 1);
	 write(1);
	 HAL_Delay(50);
	 setCursor(mario_col+1, 1);
	 print(" ");

	mario_col =  mario_col+2;
	setCursor(mario_col, 2);
	write(1);



 }


void moveAhead(){

	setCursor(mario_col, 2);
	print(" ");

	if(strcmp(field[3][mario_col+ offset],"H")==0){

		lose();
	}else if(strcmp(field[2][mario_col+ offset],"T")==0){
		setCursor(mario_col , 2);
			write(1);
	}else{
	mario_col = mario_col+1;
	setCursor(mario_col, 2);
	write(1);
}
}




void clearField(){

	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, 1);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, 1);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, 1);
		heart = 3;
		mario_col = 1 ;
		offset = 0;
		start();


}

void numberBcd(int i){


		int x1=i&1;
		int x2=i&2;
		int x3=i&4;
		int x4=i&8;
		if(x1>0) x1=1;
		if(x2>0) x2=1;
		if(x3>0) x3=1;
		if(x4>0) x4=1;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, x2);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, x3);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, x4);
		HAL_Delay(4);


}



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */


  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */



  for(int i=0; i<4; i++){
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);


 	  if(i==3){
 		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
 				  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)){

 					start();


 				  }
 	  }
   }

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
  while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0));

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */
  for(int i=0; i<4; i++){
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);


  	if(i==2){
  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  				  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)){

  					jump();


  				  }
  	  }else if(i==3){
  		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
  		  				  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)){

  		  					jumpAhead();
  	  }
  	  }else if(i==0){
   		 HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
   		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)){

	  			if(not_pause==1){
	  				not_pause= 0;
	  				setCursor(1, 0);
	  			   	print("Pause");
	  			}else{
	  				not_pause=1;
	  				setCursor(1, 0);
	  				print("     ");
	  			}
   		}

   	  }
    }
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
   while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1));

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line2 and Touch Sense controller.
  */
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */

  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */



	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);



 		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
 				  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)){

 					  moveAhead();


 				  }



  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
  while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2));
  /* USER CODE END EXTI2_TSC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */

  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
 	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);



  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
  				  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3)){
  					 HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);

  					 clearField();


  				  }

   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
    while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3));
  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
if(not_pause==1){
  if(start_flag==1 && offset<=40){

	  clear();
	  mario_col--;
	  if(mario_col==0){
		  start_flag = 0;
		  lose();
	  }else if(start_flag==1){
		  setCursor(mario_col, 2);
		 		   						   write(1);
		 		  for(int row=0; row < 4 ; row++){
		 			  if(strcmp(field[row][0],"G")==0){
		 			  	   							  setCursor(0, row);
		 			  	   									  write(0);}
		 			  else if(strcmp(field[row][0],"B")==0){
		 				  setCursor(0, row);
		 				  			  	   									  write(6);
		 			  }
		 		  }
		 	   	  for(int col=1+offset; col <20+offset; col++){
		 	   					  for(int row=0; row<4; row++){

		 	   						  if(strcmp(field[row][col],"G")==0){
		 	   							  setCursor(col-offset, row);
		 	   									  write(0);
		 	   						  }else if(strcmp(field[row][col],"M")==0){
		 	   							  setCursor(col-offset, row);
		 	   									  write(1);
		 	   						  }
		 	   						  else if(strcmp(field[row][col],"H")==0){
		 	   						  			  setCursor(col-offset, row);
		 	   						  					  write(2);
		 	   						  		  }
		 	   						  else if(strcmp(field[row][col],"T")==0){
		 	   						  			  setCursor(col-offset, row);
		 	   						  					  write(3);
		 	   						  		  }
		 	   						  else if(strcmp(field[row][col],"C")==0){
		 	   						  			  setCursor(col-offset, row);
		 	   						  					  write(4);
		 	   						  		  }
		 	   					  }
		 	   				  }

		 	   	  offset++;


	  }
  }else if(mario_col>=19 && offset==41){

  		 	  win();

  }
}

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0 |GPIO_PIN_1 , 1);
		  				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0, 0);
		  				y =  coin_amount / 10;
		  				numberBcd( coin_amount%10);
		  				HAL_Delay(4);

		  				HAL_GPIO_WritePin(GPIOD,   GPIO_PIN_0  , 1);
		  				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, 0);
		  				numberBcd(y%10);
		  				y = y / 10;
		  				HAL_Delay(4);
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
