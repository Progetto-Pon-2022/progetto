import serial as srl
import imageGetter as ig
import threading

OBJ_NOT_FOUND = -1
# porta di accesso al serial device
port = "COM6"  #'/dev/ttyACM0' 
baudrate = 4800 # baudrate
global stop
stop = "on"

arduino = srl.Serial(port, baudrate) # comunicazione seriale con arduino

def stopper():
    global stop
    stop =arduino.readline().decode().replace("\r\n", "")
    print(f"stopper:{stop}")

if __name__ == "__main__":
    
    th = threading.Thread(target=stopper)
    th.start()

    #rilevo le dimensioni massime dello schermo e salvo la x
    xmax = ig.getDimensionMax()[1]
    
    #imposto le variabili necessarie per il modello
    net, outLayer = ig.setupNet()
    
    while True:
        if stop == "off":
            print("spento")
            continue
        print(stop)
        #leggo le coordinate
        x = ig.getCoordImage(net, outLayer)[0]

        if x == OBJ_NOT_FOUND:
            print("Non rilevato.")
            continue
        
        print(f"x:{x}")
        
        var = int(x*100 / xmax)
        arduino.write(bytes(str(var), 'utf-8'))
        print("invio effettuato")

        
        #print(f"input ricevuto: {arduino.readline()}".encode())

            
