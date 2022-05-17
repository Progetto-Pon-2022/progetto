import cv2
import numpy as np

COD_OBJECT_TO_FOLLOW = 39
MIN_CONFIDENCE = 0.5

# funzione per avere il frame dell'immagine ottenuta dalla telecamera
def getFrameImage():
    cap = cv2.VideoCapture(0)
    _ ,frame = cap.read()
    cap.release()
    return frame

def getDimensionMax():
    c = cv2.VideoCapture(0)
    _ , frame = c.read()
    
    return frame.shape

def setupNet():
    net = cv2.dnn.readNet("yolov3.weights", "yolov3.cfg")
    outputlayer  = net.getUnconnectedOutLayersNames()
    return net, outputlayer


def getCoordImage(net, outputlayer):
    img = getFrameImage()
    height, width, _ = img.shape
    
    #dobbiamo trasformare un'immmagine in un blob, che servirà all'algoritmo per funzionare
    # il blob tiene traccia di tutti i canali dellimmagine (r,g,b) per esaminarli separatamente
    scaleFactor = 0.00392 # non so cosa sia
    size = (416,416)
    invertingBlueRed = True # l'inversione serve all'algoritmo per funzionare
    blob = cv2.dnn.blobFromImage(img, scaleFactor,size, (0,0,0), invertingBlueRed, crop=False )

    net.setInput(blob)
    #outs contiene tutte le informazioni del rilevamento degli oggetti
    outs = net.forward(outputlayer)

    class_ids = []
    centerOfImages = []

    # far vedere le informazioni a schermo
    for out in outs:
        for detection in out:
            #confidenza è quanto l'algoritmo è sicuro che un oggetto sia presente; da 0 a 1
            scores = detection[5:]
            class_id = np.argmax(scores) # numero associato con le classi lette dal file coco
            confidence = scores[class_id]

            if confidence > MIN_CONFIDENCE:
                # dobbiamo moltiplicare per le relative dimensioni perchè l'immagine elaborata
                #   dall'algoritmo viene ridimensionata quando viene trasformata in blob 
                center_x = int(detection[0] * width)
                center_y = int(detection[1] * height)

                #salvo le informazioni per tutti gli oggetti salvati
                centerOfImages.append([center_x,center_y])
                class_ids.append(class_id)

    """
    cv2.imshow("Image", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    """

    if COD_OBJECT_TO_FOLLOW in class_ids:
        #print(f"coordinate del centro dell'immagine: ({centerOfImages[0]}, {centerOfImages[1]}) ")
        return  centerOfImages[class_ids.index(COD_OBJECT_TO_FOLLOW)]
    else:
        return [-1, -1] #
