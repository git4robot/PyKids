#!/usr/bin/python
# -*- coding: utf-8 -*-
# ----------------------------------------------
# --- Author         : Ahmet Ozlu
# --- Mail           : ahmetozlu93@gmail.com
# --- Date           : 31st December 2017 - new year eve :)
# ----------------------------------------------

import csv
import random
import math
import operator
import cv2

class KNNClassifier:
    # initialize pre-trained data
    def __init__(self, trained_file):
        self.training_feature_vector=[]

        with open(trained_file) as csvfile:
            lines = csv.reader(csvfile)
            dataset = list(lines)
            for x in range(len(dataset)):
                for y in range(3):
                    dataset[x][y] = float(dataset[x][y])
                self.training_feature_vector.append(dataset[x])
        self.feature_len = len(self.training_feature_vector)

    # calculation of euclidead distance
    def calculateEuclideanDistance(self, variable1, variable2, length):
        distance = 0
        for x in range(length):
            distance += pow(variable1[x] - variable2[x], 2)
        return math.sqrt(distance)


    # get k nearest neigbors
    def kNearestNeighbors(self, testInstance, k):
        distances = []
        length = len(testInstance) - 1
        for x in range(self.feature_len):
            dist = self.calculateEuclideanDistance(testInstance,
                    self.training_feature_vector[x], length)
            distances.append((self.training_feature_vector[x], dist))
        distances.sort(key=operator.itemgetter(1))
        neighbors = []
        for x in range(k):
            neighbors.append(distances[x][0])
        return neighbors


    # votes of neighbors
    def responseOfNeighbors(self, neighbors):
        all_possible_neighbors = {}
        for x in range(len(neighbors)):
            response = neighbors[x][-1]
            if response in all_possible_neighbors:
                all_possible_neighbors[response] += 1
            else:
                all_possible_neighbors[response] = 1
        sortedVotes = sorted(all_possible_neighbors.items(),
                            key=operator.itemgetter(1), reverse=True)
        return sortedVotes[0][0]


    # Load image feature data to training feature vectors and test feature vector
    def loadDataset(self, 
        filename,
        filename2,
        training_feature_vector=[],
        test_feature_vector=[],
        ):
        with open(filename) as csvfile:
            lines = csv.reader(csvfile)
            dataset = list(lines)
            for x in range(len(dataset)):
                for y in range(3):
                    dataset[x][y] = float(dataset[x][y])
                training_feature_vector.append(dataset[x])

        with open(filename2) as csvfile:
            lines = csv.reader(csvfile)
            dataset = list(lines)
            for x in range(len(dataset)):
                for y in range(3):
                    dataset[x][y] = float(dataset[x][y])
                test_feature_vector.append(dataset[x])


    def color_histogram_of_test_image(self, test_src_image):

        # load the image
        image = test_src_image

        chans = cv2.split(image)
        colors = ('b', 'g', 'r')
        features = []
        feature_data = ''
        counter = 0
        for (chan, color) in zip(chans, colors):
            counter = counter + 1

            hist = cv2.calcHist([chan], [0], None, [256], [0, 256])
            features.extend(hist)

            # find the peak pixel values for R, G, and B
            elem = np.argmax(hist)

            if counter == 1:
                blue = str(elem)
            elif counter == 2:
                green = str(elem)
            elif counter == 3:
                red = str(elem)
                feature_data = red + ',' + green + ',' + blue
                # print(feature_data)

        with open('test.data', 'w') as myfile:
            myfile.write(feature_data)


    def predict(self, source_image):
        training_feature_vector = []  # training feature vector
        test_feature_vector = []  # test feature vector

        # load the image
        image = test_src_image

        chans = cv2.split(image)
        colors = ('b', 'g', 'r')
        features = []
        feature_data = ''
        counter = 0
        for (chan, color) in zip(chans, colors):
            counter = counter + 1

            hist = cv2.calcHist([chan], [0], None, [256], [0, 256])
            features.extend(hist)

            # find the peak pixel values for R, G, and B
            elem = np.argmax(hist)

            if counter == 1:
                blue = str(elem)
            elif counter == 2:
                green = str(elem)
            elif counter == 3:
                red = str(elem)
                feature_data = red + ',' + green + ',' + blue
                # print(feature_data)

        with open('test.data', 'w') as myfile:
            myfile.write(feature_data)            

            with open(filename2) as csvfile:
                lines = csv.reader(csvfile)
                dataset = list(lines)
                for x in range(len(dataset)):
                    for y in range(3):
                        dataset[x][y] = float(dataset[x][y])
                    test_feature_vector.append(dataset[x])

        #loadDataset(training_data, test_data, training_feature_vector, test_feature_vector)
        classifier_prediction = []  # predictions
        k = 3  # K value of k nearest neighbor
        for x in range(len(test_feature_vector)):
            neighbors = self.kNearestNeighbors(test_feature_vector[x], k)
            result = self.responseOfNeighbors(neighbors)
            classifier_prediction.append(result)

        return classifier_prediction[0]		
