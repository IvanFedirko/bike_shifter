# Installation

### SDK
**sdk5 17.1.0**

sdk5 17.1.0 совместима с SES 5.42a

![Segger_v5.42a](assets/imgs/Segger_v5.42a.jpg)

```
The following toolchains/devices have been used for testing and verification:
 
 - ARM: MDK-ARM version 5.25   
 - GCC: GCC ARM Embedded 9.2020-q2.major
 - IAR: IAR Workbench 7.80.4
 - SES: SES 5.42a
```

При запуске выбирать некоммерческое использование

![Segger_no_commercial](assets/imgs/Segger_no_commercial.jpg)


### Загрузка проекта

После подключения выбираем

***Target -> Connect J-Link***


Затем можно загрузить проект

![Download_project](assets/imgs/Download_project.jpg)

### Project path

Путь для SDK

```
C:\nRF5_SDK_17.1.0\

```
![Download_project](assets/imgs/sdk_path.jpg)


Общий путь

```
C:\nRF5_SDK_17.1.0\examples
```

заходим в директорию "examples" и загружаем репозиторий с git

```bash
C:\nRF5_SDK_17.1.0\examples\>git clone git@github.com:IvanFedirko/bike_shifter.git
```

Полный путь до проекта должен получиться

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter
```
# RTT Логгер


[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/oQFpEyBWAlI/0.jpg)](https://www.youtube.com/watch?v=oQFpEyBWAlI)


# Управление светодиодами (led_control)

Откройте Решение (SEGGER: File -> Open Solution)

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter\led_control\pca10056\blank\ses\led_control.emProject
```

Светодиоды подключены через VDD (active LOW), следовательно  **nrf_gpio_pin_set** - отключает, **nrf_gpio_pin_clear** - включает  и **nrf_gpio_pin_toggle** - переключает

* LED_BLUE **P0.28**
* LED_GREEN **P0.03**
* LED_RED **P0.02**


# Управление кнопкой (button_control)

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter\button_control\pca10056\blank\ses\button_control.emProject
```

Кнопка подключена на ***P0.29 = gpio pin 29***

Кнопка замыкает на **плюс**, следовательно делаем ее активной в высоком, и подключаем стягивающий резистор


```c
 nrf_gpio_cfg_input(button, NRF_GPIO_PIN_PULLDOWN);
```

Чтение кнопки

```c
   if (nrf_gpio_pin_read(button) == 1){}
```


# Глубокий сон и пробуждение по движению

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter\deep_sleep\pca10056\blank\ses\deep_sleep.emProject
```

Строки для того чтобы войти в Сон

```
  __SEV();
  __WFE();
  NRF_POWER->SYSTEMOFF = 1;
```

После пробуждения плата стартует с функции **main**

# Энкодер

Пин питания AS5600 P1.08 = пин №40

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter\encoder\pca10056\blank\ses\encoder.emProject
```


# Чтение тока и напряжения

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter\current_and_voltage\pca10056\blank\ses\current_and_voltage.emProject
```

* AIN6 - для вычисления тока
* AIN7 - для вычисления напряжение

**Напряжение = AIN7 * 3**

**Ток = AIN6 / 0.02**


# Стоп Сигнал, управление мотором

```
C:\nRF5_SDK_17.1.0\examples\bike_shifter\l2293qtr\pca10056\blank\ses\l2293qtr.emProject
```

![L2293QTR](assets/imgs/L2293QTR.jpg)


![L2293QTR_schematic](assets/imgs/L2293QTR_schematic.jpg)

![L2293QTR_truth_table](assets/imgs/L2293QTR_truth_table.jpg)

* OUT_1 - мотор
* OUT_2 - мотор
* OUt_3 - стоп-сигнал
  
  <br/>

* EN_1 - nRF P1.11 (43)
* EN_2 - U6 (VOUT)
  <br/>

* IN_1 (FWD) - nRF P1.12 (44)
* IN_2 (REV) - nRF P1.13 (45)
* IN_3 (LED) - nRF P1.14 (46)