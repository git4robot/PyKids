#!/usr/bin/python
# -*- coding: utf-8 -*-
# -------------------------------------------------------------------------
# --- Author         : Ahmet Ozlu
# --- Mail           : ahmetozlu93@gmail.com
# --- Date           : 8th July 2018 - before Google inside look 2018 :)
# -------------------------------------------------------------------------

import cv2
from color_recognition_api import color_histogram_feature_extraction
from color_recognition_api import knn_classifier
import os
import os.path


# checking whether the training data is ready
PATH = './training.data'

def demo(knn_classifier, src_image):
    # read the test image
    source_image = cv2.imread(src_image)
    if source_image is None:
        print("File Open Failed! ",src_image)
        return

    prediction = 'n.a.'

    prediction = knn_classifier.predict(source_image)
    print(prediction, src_image)
    #cv2.putText(source_image,'Prediction: ' + prediction,(15, 45),cv2.FONT_HERSHEY_PLAIN,3,200,)

    # Display the resulting frame
    #cv2.imshow('color classifier', source_image)
    #cv2.waitKey(0)		


if __name__ == "__main__":

    if os.path.isfile(PATH) and os.access(PATH, os.R_OK):
        print ('training data is ready, classifier is loading...')
    else:
        print ('training data is being created...')
        open('training.data', 'w')
        color_histogram_feature_extraction.training()
        print ('training data is ready, classifier is loading...')

    # get the prediction
    knn_classifier = knn_classifier.KNNClassifier(PATH)

    #demo(knn_classifier, "./pieces/blue1r7.jpg")
    #demo(knn_classifier, "./pieces/greenr4.jpg")

    for f in os.listdir('./pieces'):
        demo(knn_classifier, './pieces/'+f)
