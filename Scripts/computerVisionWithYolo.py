
"""
IMPORTANTE:
    - avere in questa cartella i file: yolov3.weights, yolov3.cfg, coco.names per il corretto funzionamento

"""
import cv2
import numpy as np

# funzione per avere il frame dell'immagine ottenuta dalla telecamera
def getFrameImage():
    cap = cv2.VideoCapture(0)
    _ ,frame = cap.read()
    cap.release()
    return frame

# carico yolo
# seguire gli step sul sito per scaricarlo

net = cv2.dnn.readNet("yolov3.weights", "yolov3.cfg")
classes = []

#leggo i nomi delle classi riconosciute dall'algoritmo pre-addestrato
with open("coco.names","r") as f:
    classes = [line.strip() for line in f.readlines()]


outputlayer  = net.getUnconnectedOutLayersNames()
#FINE DEL CARICAMENTO DELL'ALGORITMO

#CARICARE UN'IMMAGINE DA UN FILE
"""
CARICAMENTO IMMAGINE DA FILE.
da andare a sostituire con l'eventuale lettura di immagini da fotocamera.
vedere ed integrare con streaming_video_cv2.py
"""

while True:
    img = getFrameImage()

    height, width, channels = img.shape
    """-------------------------------------------------------------"""
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
    confidences = []
    boxes = []

    # far vedere le informazioni a schermo
    for out in outs:
        for detection in out:
            #confidenza è quanto l'algoritmo è sicuro che un oggetto sia presente; da 0 a 1
            scores = detection[5:]
            class_id = np.argmax(scores) # numero associato con le classi lette dal file coco
            confidence = scores[class_id]

            if confidence > 0.5:
                #siamo abbastanza sicuri che l'oggetto sia stato rilevato

                # dobbiamo moltiplicare per le relative dimensioni perchè l'immagine elaborata
                #   dall'algoritmo viene ridimensionata quando viene trasformata in blob 
                center_x = int(detection[0] * width)
                center_y = int(detection[1] * height)
                w = int(detection[2] * width)
                h = int(detection[3]* height)

                # coordinate del rettangolo che circoscriverà l'oggetto trovato
                x = int(center_x - w/2)
                y = int(center_y - h/2)

                #salvo le informazioni per tutti gli oggetti salvati
                boxes.append([x,y,w,h])
                confidences.append(float(confidence))
                class_ids.append(class_id)

    #NMSBoxes serve per eliminare i box sovrapposti molto vicini.

    indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.5, 0.4)
    print(indexes)
    objectsdetected = []
    for i in indexes:
        x,y,w,h = boxes[i]
        #inserisco il rettangolo all'interno dell'immagine
        colorBox = (0,255,0)
        angoloAltoSinistra = (x,y)
        ancoloBassoDestra = (x+w, h+y)
        spessore = 2
        cv2.rectangle(img,angoloAltoSinistra , ancoloBassoDestra, colorBox, spessore)

        #scrivo il nome dell'oggetto rilevato per ogni rettangolo
        font = cv2.FONT_HERSHEY_PLAIN
        label = str(classes[class_ids[i]])
        coordText = (x,y+30)
        fontScale = 2
        cv2.putText(img, label, coordText, font, fontScale, (255,255,255))
        objectsdetected.append(label)

    print([obj for obj in objectsdetected])

    #cv2.imshow("Image", img)
    #cv2.waitKey(0)
    cv2.destroyAllWindows()
