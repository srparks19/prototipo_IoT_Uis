# prototipo_IoT_Uis

<p align="left">
   <img src="https://img.shields.io/badge/STATUS-EN%20DESAROLLO-green">
</p>

<h1>Definición de la arquitectura</h1>

La arquitectura propuesta para el prototipo se centra en establecer una comunicación eficiente entre los dispositivos y el servidor, garantizando una transmisión de datos fluida y confiable. Esta arquitectura se divide en dos componentes principales: el dispositivo de recolección de datos y el sistema de información en la página web.

En cuanto al dispositivo de recolección de datos, se implementarán los sensores necesarios en los medios de transporte para recopilar la información relevante. Estos dispositivos estarán encargados de capturar y enviar los datos al servidor de manera periódica. Se establecerá una comunicación estable utilizando tecnologías como Wi-Fi o Bluetooth, y se empleará el protocolo MQTT para enviar los datos al servidor de forma eficiente.

En resumen, la arquitectura propuesta busca establecer una comunicación efectiva entre los dispositivos de recolección de datos y el sistema de información en la página web, permitiendo una recopilación de datos eficiente y una presentación clara de la información al usuario final.

<h3>ESP32</h3>

Se realiza una comparación entre diferentes módulos de Arduino con comunicación Wifi para la creación de este prototipo, encontrando una simplificación de cada una de sus características de las cuales se decidió elegir el ESP32 como nuestro modulo Wifi siendo el cerebro que coordina el envío de información de cada uno de los dispositivos presentes en el prototipo.

![Imagen ilustratica de un ESP32](https://github.com/srparks19/prototipo_IoT_Uis/assets/66749108/b47ece12-dcf5-4434-9ec6-26a6fcb9c715)

<h3>MZ-H19B</h3>

Este sensor utiliza el principio de medición por infrarrojo u óptica, que es más preciso que la medición por sensores electroquímicos. El proceso de medición se basa en el uso de un pulso de luz de banda ancha, y a través de la intensidad relativa de la onda, el sensor determina la presencia y concentración del gas, en este caso, el CO2, en el ambiente.

![Imagen ilustrativa de un MZ-H19B](https://github.com/srparks19/prototipo_IoT_Uis/assets/66749108/fa472082-0b92-49d5-a24c-91f492bda7f2)

<h3>NEO-6M</h3>

Permite obtener la ubicación del dispositivo a través de señales satelitales. Este módulo se selecciona debido a su practicidad y economía en la implementación. Tiene un tamaño reducido y es fácil de utilizar. El margen de error de este módulo es de aproximadamente 3 metros. Cuenta con una antena que, al conectarse con el satélite más cercano, emite pulsos digitales para determinar la ubicación del dispositivo de manera precisa.

![Imagen ilustrativa de un NEO-6M](https://github.com/srparks19/prototipo_IoT_Uis/assets/66749108/595aa8d5-71d8-4022-b6ac-23bf52d1ee8c)


<h3>DS18B20</h3>

El sensor DS18B20 permitirá medir la temperatura ambiente, analizar su influencia en el comportamiento del gas. Este sensor es pequeño, económico y ampliamente utilizado debido a su sencilla implementación. Cuenta con un rango de medición de -55°C a 125°C, un solo bus de salida, un LED y una resistencia.

![Imagen ilustrativa de una DS18B20](https://github.com/srparks19/prototipo_IoT_Uis/assets/66749108/b0e36d0d-dc53-477d-93cf-49fd36e5db58)

<h2>Montaje</h2>
  
Teniendo en cuenta los manuales de los fabricantes y la información adquirida de diferentes fuentes, se realiza el montaje del prototipo con precaución, cuidando los niveles de voltaje recomendados para cada dispositivo. Se construye una estructura física que permite la obtención de datos de medición del aire y la ubicación de los medios de transporte público. El sistema de medición de calidad del aire se presenta de forma práctica y compacta.

![Iamgen ilustrativa del montaje del prototipo](https://github.com/srparks19/prototipo_IoT_Uis/assets/66749108/5f50389f-c22d-4933-9a92-ae6e5bca9ced)

<h2>Creación aplicativo web</h2>

El complemento que se implementó en la creación de este aplicativo se puede encontrar en la siguiente dirección:
<a href="https://github.com/srparks19/dashboard_iot_uis">Aqui</a>
