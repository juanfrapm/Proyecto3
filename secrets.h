#include <pgmspace.h>
 
#define SECRET
 
const char WIFI_SSID[] = "juanfra";               //TAMIM2.4G
const char WIFI_PASSWORD[] = "juanfrapm";           //0544287380
 
#define THINGNAME "esp_8266"
 
int8_t TIME_ZONE = -5; //NYC(USA): -5 UTC
 
const char MQTT_HOST[] = "a11v845s8l1ki7-ats.iot.us-east-2.amazonaws.com";
 
 
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUeh+b0OxhEU6N+ZQrylm8bk85eXswDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MTAxMDIxMDk1
M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALqaET6n/Cnd55AvRtQt
qrGr6WbLsmi0g56MqUWuc8IcC/zMEv/orhpDP0hxO6mXumDPeTmR1TUtSN9p1Cde
3KJepRZX7DzkWfYITQ7p75vVIwhN7dHkD54vvr3/NolJd4D7p6jtXCl103+Fgn0K
oI72BRAN7hE7Xkyh+wKuXnjSAFIAnHO0D34+B7SdvqPzbMv/ktOAPHY94XwmTn60
tStwdTQnCQfYQxqaYahSWCCqEWXc2Hz9g9Pga2cAexZDEHaHAnYTY3U1iC78Uo4Q
oWDxNRBddDdi8xXmzJDeWdJNoMZA44c3lWgCqzCmDSSad1aJbCi3/9W9YjJY9758
4YECAwEAAaNgMF4wHwYDVR0jBBgwFoAUrTbYnVF5swdshooAvbm/vRtQ1+wwHQYD
VR0OBBYEFO4FezAk01ze51ASpSEwfa8vgc4SMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBpevHL+z8z+XIm10PPLXnE7rK4
pKfTmUanAVckdAhtt7/p0JmowrW8HuwQNV1oldUe9o9IdlmVen4Qo1vv+1h4VmkP
n2nYfHlMDl19V3JrjMaKfSjTDh8Y5OeXV6uz8ogkKQQ+ftxAY7PFBiNkeIMmOKIl
r4PnuUcuV1DUndQb9EmScCm+t5byteTAKWAGtjTQfWk73pLQO2ynj0LStNrZxeFa
g42Jf/WojqyMLJKT6rzgZ7DOjZs2A4/OS95nujjluDSU5rgMihXOWXJD9m2yt+kS
0XInidsKKlUwPxG4o1s4kRGoulIcmCR4ZJze/woA+FsNiOmxICtkoZe/6urj
-----END CERTIFICATE-----
 
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAupoRPqf8Kd3nkC9G1C2qsavpZsuyaLSDnoypRa5zwhwL/MwS
/+iuGkM/SHE7qZe6YM95OZHVNS1I32nUJ17col6lFlfsPORZ9ghNDunvm9UjCE3t
0eQPni++vf82iUl3gPunqO1cKXXTf4WCfQqgjvYFEA3uETteTKH7Aq5eeNIAUgCc
c7QPfj4HtJ2+o/Nsy/+S04A8dj3hfCZOfrS1K3B1NCcJB9hDGpphqFJYIKoRZdzY
fP2D0+BrZwB7FkMQdocCdhNjdTWILvxSjhChYPE1EF10N2LzFebMkN5Z0k2gxkDj
hzeVaAKrMKYNJJp3VolsKLf/1b1iMlj3vnzhgQIDAQABAoIBACOP/T1dsncgLWOT
PwJs+Z0G0GKg64186aCr2g7HopQZ2EcDdZOD+rpSmprpyZ8WpZSRtd685k9OJBdA
Cgi+0Xm4Y+oQM5ufQW3cQyNWfi3KvvR0NaDMwBU7sDRxkSk08SuJyngtVGUqaXZi
MW43OkZEqM5YeUibcetU64ulQ6fuuoLx/y6YdG/9gCRjbN9873V0AeCa9GEwoAVI
AGyC8qmX/VN4SRNDxKdfjCoFvK249onYCH8r9lbisSLCgWjL+AcZ2X8O7qZuitp7
kceq5bCDQOGX+Qd+eCEdGU7V2hYNrPb4gDV9HJAMTXhpsno4sbYEeypMQl1SZzVS
EYNQl0kCgYEA3jZzR1cEG8kTKk4yLC0BSaFScqvfunhBwmQIEEOlNt9Pyou0D7dS
01kheKRZPVUvHWvbpBlF1Uv5/LV+ZYXmrNK1no1QAqKgfRf7NCQOlYczaSglkLTr
UQCxRvKvnTggfFa7L0j/lJ8GswBkAGmyrqkFr/gjjdZG68dzV4vyQdMCgYEA1vl6
BbJmg0FdM4c5Kod4SZGpPrkNZ8t2DNq14aiQrbcGAKGHgAatCYmN03ZN0okey78B
HZ0jlbZ84CG2eDT1r3RkS9PuGUMfvJFRdZSV66RucmcIUwVeGjNFyZXWVl4/7+ke
LE+nlZstdSku7cg+uyK1hGHybZ7JN1XXbNiZ5tsCgYEAi+9wQzHKFZFXr2GU+PrS
f8LGwA36k1wd1UPXTB69UUPp5Jx7pRYGY7ASgv3EcPpO9FEy/TEpJ/xzji/hTB+5
t4Xt98333+D3/i7288vtHz8IIiW1Gl7EfbtY6Fv2OaTZ2FNqB4oJ4VcQCfOqBhSK
ALHSMhGqmiyhduOggDZSNh8CgYEAt+8ZMoqkH6Xros0OYo8qonfZAWvARpDVXsY7
XOqnb5rrrdqHX0lXAJQLH2VXzM255cZ1o+rxqYVMb1EpGMznccn6js60KDVAkE0e
D6akZ8x3G7eAbdhn3a8FBSgJDjjyJ8mkIXG+B8mQKXClUJpG4kMeYDiV/qkfrRLr
kZv6goUCgYBAUnB3G+5IF550mxzCf1qdwYulA+cOAr0F9oHRwwhol8Q2A04Kvd8n
mKNg7K9xYZH9OiH7WpJUK9YgUhhby18Yoyu32k18EHR0Sk3HYHUDFxBoPvtH54o1
tUhLbkfkJodngg3g/fsWqPaKFbhPTjDUJf2dpkFctkXJ3CPODuvlWQ==
-----END RSA PRIVATE KEY-----
 
)KEY";
