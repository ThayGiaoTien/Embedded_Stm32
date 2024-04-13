The HAL_ADCEx_Calibration_Start() function is called to start an automatic calibration. This function takes in a parameter which is the pointer to a ADC_HandleTypeDef structure that contains the configuration information for the specified ADC. It is ‘&hadc1’ in our case.

HAL_ADCEx_Calibration_Start(&hadc1);
Inside the while loop, we call HAL_ADC_Start() to enable the ADC and start the conversion of the regular channels. It takes in a single parameter ‘hadc’ which is the pointer to a ADC_HandleTypeDef structure that contains the configuration information for the specified ADC. It is ‘&hadc1’ in our case.

HAL_ADC_Start(&hadc1);
Then we call HAL_ADC_PollForConversion() to poll for regular conversion. It takes in two parameters. The first parameter is the pointer to a ADC_HandleTypeDef structure that contains the configuration information for the specified ADC which is ‘&hadc1’ in our case. The second parameter is the timeout in milliseconds which we have specified as 1 millisecond.

HAL_ADC_PollForConversion(&hadc1, 1);
After that the ADC conversion value from data register of regular channel is acquired by using HAL_ADC_GetValue() and mapped to the PWM duty cycle. The ADC conversion value is read and shifted to the timer CCR register which sets the PWM duty cycle percentage for the output LED pin.

 AD_RES = HAL_ADC_GetValue(&hadc1);
 TIM2->CCR1 = (AD_RES<<4);
