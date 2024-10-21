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