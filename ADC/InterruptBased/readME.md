- The HAL_ADC_Start_IT() function is responsible for enabling the interrupt and starting ADC conversion of regular channels. It takes in a single parameter which is the pointer to the ADC_HandleTypeDef structure that contains the configuration parameters for the specified ADC. In our case it is ‘&hadc1.’
`
  HAL_ADC_Start_IT(&hadc1);
`
- The HAL_ADC_ConvCpItCallback() function is the regular conversion complete callback in non blocking mode. It also takes in the same parameter which is the pointer to the ADC_HandleTypeDef structure. Inside this callback, the ADC value is read and updated using HAL_ADC_GetValue().
```c
  void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
  {
    adcValue = HAL_ADC_GetValue(&hadc1);
  }  
```
- Don't forget to declare `c uint16_t adcValue=0;` globally. 
