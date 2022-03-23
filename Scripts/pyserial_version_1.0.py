#-librerie----------------------------------------------------------------------------------------------------------------------------------
import serial as srl
import time

#-arduino-----------------------------------------------------------------------------------------------------------------------------------
port = 'COM5' # porta di accesso al serial device
baudrate = 9600 # baudrate

arduino = srl.Serial(port, baudrate) # comunicazione seriale con arduino

#-funzioni----------------------------------------------------------------------------------------------------------------------------------
def movement(choice_input): # funzione usata nel main per ricorrere alla scelta del movimento 
    if choice_input == 'w':
        arduino.write(b'w') # invio di 'w' ad arduino per andare avanti
    elif choice_input == 's':
        arduino.write(b's') # invio di 's' ad arduino per andare indietro
    elif choice_input == 'a':
        arduino.write(b'a') # invio di 'a' ad arduino per andare a sinistra
    elif choice_input == 'd':
        arduino.write(b'd') # invio di 'd' ad arduino per andare a destra
    elif choice_input == 'r':
        arduino.write(b'r') # invio di 'r' ad arduino per stopparsi
    else:
        print("! ERROR - insert a movement !\n")

#-main--------------------------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    print("########## VERSION 1.0 - PYSERIAL ##########\n"
            "Python interface: ON\n"
            "\nPlease insert the movement you want:\n"
            "\t- w --> forward\n"
            "\t- a --> left\n"
            "\t- s --> backward\n"
            "\t- d --> right\n"
            "\t- r --> stop\n")

    while True:
        choice_input = str(input("\nInsert a movement: "))

        movement(choice_input)
        print(arduino.readline()) # stampo ciò che ci rimanda arduino

        # aspetto 1 secondo e fermo Wall-EEE
        time.sleep(1)
        arduino.write(b'r')