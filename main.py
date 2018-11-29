# Arduino_IoTclient
# Created at 2018-11-21 17:39:59.994769
import iot.mqttsn.SNClient
import iot.mqtt.MQTTClient as MQTTClient
import config.configParser as configParser
import streams
import adc

streams.serial()

sleep(1000)
print('Reading config file ...')
new_resource("configFile")
user = configParser.Parser.getConfig('resource://configFile')
print('Config file Ok ')

#____________________________________________________________________Ethernet
import eth
#from espressif.esp32net import esp32eth as eth_driver
#eth_driver.init()
print("Establishing Link...")
try:
    eth.link()
except Exception as e:
    print('Error occured:' + str(e))
    while True:
        sleep(1000)
print('Link info: ' + str(eth.link_info()))

#___________________________________________________________________MQTT
if user.Protocol == 1: #MQTT
    client = MQTTClient.mqttClient(user)
    client.goConnect()
    if client.isConnected():
        #___________________________________________________________Read_Temperature
        while True:
            sensorValue = adc.read(A0)
            voltage = (sensorValue/4095)*5
            #print('voltage: ' + str(voltage))
            temp = (voltage -0.5)*100
            #print('temp: ' + str(temp))
            client.publish(user.Topics, user.qos, str(temp), user.retain, user.dup)
            sleep(user.timeout*1000)
    else:
        print('Error occured while connection (MQTT)...')
elif user.Protocol == 2: #MQTTSN
    client = SNClient.snClient(user)
    client.goConnect()
    if client.isConnected():
        #___________________________________________________________Read_Temperature
        while True:
            sensorValue = adc.read(A0)
            voltage = (sensorValue/4095)*5
            #print('voltage: ' + str(voltage))
            temp = (voltage -0.5)*100
            #print('temp: ' + str(temp))
            client.publish(user.Topics, user.qos, str(temp), user.retain, user.dup)
            sleep(user.timeout*1000)
    else:
        print('Error occured while connection (MQTTSN)...')