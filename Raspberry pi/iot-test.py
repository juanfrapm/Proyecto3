import time
import paho.mqtt.client as mqtt
import ssl
import json
import _thread

def on_connect(client, userdata, flags, rc):
    print("Connected to AWS IoT: " + str(rc))

client = mqtt.Client()
client.on_connect = on_connect
client.tls_set(ca_certs='./AmazonRootCA1.pem', certfile='./a43967a6452913e322fc8d827ae244ebe683cbf7f53261f42967e6be947685fc-certificate.pem.crt', keyfile='./a43967a6452913e322fc8d827ae244ebe683cbf7f53261f42967e6be947685fc-private.pem.key', tls_version=ssl.PROTOCOL_SSLv23)
client.tls_insecure_set(True)
client.connect("a11v845s8l1ki7-ats.iot.us-east-2.amazonaws.com", 8883, 60)

def publishData(txt):
    print(txt)
    ctr = 1
    while (True):
        time.sleep(5)
        with open("datos.csv", mode="r") as archivo:
            lineas = archivo.readlines()  # Leer todas las líneas
            encabezados = lineas[0].strip().split(",")  # Separar encabezados
            datos = []
            # Procesar cada línea de datos
            for linea in lineas[1:]:
                data = linea.strip().split(",")  # Separar valores
                 # Asignar cada campo a una variable
                timestamp = data[0]
                msg = data[1]
                codes = data[2]
                model = data[3]
                type_ = data[4]  # Usamos type_ ya que 'type' es una palabra reservada en Python
                id_ = data[5]    # Usamos id_ ya que 'id' es una palabra reservada en Python
                battery_ok = data[6] == 'true'  # Convertimos a booleano
                pressure_kPa = float(data[7])  # Convertimos a float
                temperature_C = float(data[8])  # Convertimos a float
                flags = data[9]
                fast_leak = data[10] == 'true'  # Convertimos a booleano
                inflate = data[11] == 'true'  # Convertimos a booleano
                mic = data[12]
                
                payload = {
                    "time": timestamp,  # Cambiado a timestamp
                    "msg": msg,
                    "codes": codes,
                    "model": model,
                    "type": type_,
                    "id": id_,
                    "battery_ok": battery_ok,
                    "pressure_kPa": pressure_kPa,
                    "temperature_C": temperature_C,
                    "flags": flags,
                    "fast_leak": fast_leak,
                    "inflate": inflate,
                    "mic": mic
                }

                json_payload = json.dumps(payload)
                print("Publishing data:", json_payload)
                client.publish("raspi/data", json_payload, qos=0, retain=False)
                
                # msg = "Hello world" + str(ctr)
                #print(msg)
                #client.publish("raspi/data", payload=json.dumps({"timestamp": timestamp}), qos=0, retain=False)
                #ctr = ctr + 1
                
                
        
_thread.start_new_thread(publishData,("Spin-up new Thread...",))

client.loop_forever()