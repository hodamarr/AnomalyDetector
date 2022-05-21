//
// Hod Amar and Ofek Avergil
//

#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"

#include <vector>
#include <algorithm>
using namespace std;

/**
 * finds for each feature a correlated feature, and create a correlativeFeatures object of them.
 * @param ts - TimeSeries object with the data
 */
void SimpleAnomalyDetector::fillCf(const TimeSeries &ts) {
    int size, i, j;
    float maxCorr, temp, *data1, *data2;
    string corrFeature, other, feature;
    vector<float> featureData, otherData;
    //get the names of the features
    vector<string> features = ts.getFeaturesNames();
    int featuresNum = (int)features.size();
    //for every feature in the list look for correlative feature.
    for(i=0; i<featuresNum; i++) {
        maxCorr = 0;
        feature = features.at(i);
        featureData = ts.getData(feature);
        data1 = &featureData[0];
        size = (int)featureData.size();
        //calculate with all the other features
        for (j = i + 1; j < featuresNum; j++) {
            other = features.at(j);
            otherData = ts.getData(other);
            data2 = &otherData[0];
            //find the correlation
            temp = pearson(data1 ,data2 ,size);
            //if correlation is bigger in absolute mark this feature as the correlated one.
            if(abs(temp) > abs(maxCorr)) {
                maxCorr = temp;
                corrFeature = other;
            }
        }
        //if we found correlative feature, create new correlatedFeatures
        if(checkIfCorr(maxCorr)) {
            correlatedFeatures couple;
            //fill data
            couple.feature1 = feature;
            couple.feature2 = corrFeature;
            couple.corrlation = maxCorr;
            //add to the correlative couples vector.
            cf.push_back(couple);
        }
    }
}

/**
 * checks if the correlation is over the minimum threshold
 * @param corr - the check correlated
 * @return - true if the correlation is big enough, false otherwise.
 */
bool SimpleAnomalyDetector::checkIfCorr(float corr) {
    return (abs(corr) >= linThreshold);
}

//auto-generated constructor
SimpleAnomalyDetector::SimpleAnomalyDetector() {
    this->linThreshold = 0.9;
}

//constructor while given minimum threshold for linear correlation
SimpleAnomalyDetector::SimpleAnomalyDetector(float thresh) {
    this->linThreshold = thresh;
}

//setter func for minThreshold
void SimpleAnomalyDetector::ChangeLinThresh(float thresh) {
    this->linThreshold = thresh;
}


//auto-generated destructor
SimpleAnomalyDetector::~SimpleAnomalyDetector() {}

/**
 * get the training data and arrange it's correlated features.
 * @param ts - TimeSeries object with the data
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    int i, size;
    fillCf(ts);
    for(correlatedFeatures& couple : cf) {
        vector<float> data1 = ts.getData(couple.feature1);
        vector<float> data2 = ts.getData(couple.feature2);
        size = (int)data1.size();
        //create a point array
        Point* array[size];
        for(i = 0; i < size; i++) {
            array[i] = new Point(data1.at(i), data2.at(i));
        }
        fillCorr(&couple,array,size);
    }
}
/**
 * fills the lin_reg and threshold fields of the linear correlated features
 * @param couple - correlatedfeature object
 * @param array  - array of pointer to points
 * @param size   - the size of the array;
 */
void SimpleAnomalyDetector:: fillCorr(correlatedFeatures* couple, Point** array, size_t size) {
    float temp , maxDev = 0;
    int i;
    couple->lin_reg = linear_reg(array, size);
    for(i = 0; i < size; i++) {
        temp = dev(*array[i], couple->lin_reg);
        if (abs(temp) > abs(maxDev)) {
            maxDev = temp;
        }
    }
    couple->threshold = abs(maxDev);
}

/**
 * gets the tested data and check each correlated features if there anomaly in their data
 * @param ts - the data
 * @return vector with all the reports of anomaly
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    int i,time, size;
    float dist, maxDist;
    vector<AnomalyReport> report;
    for(correlatedFeatures& couple : cf) {
        time = 1;
        vector<float> data1 = ts.getData(couple.feature1);
        vector<float> data2 = ts.getData(couple.feature2);
        size = (int)data1.size();
        //create points array
        Point* array[size];
        for(i = 0; i < size; i++) {
            array[i] = new Point(data1.at(i), data2.at(i));
        }
        for(Point* p :array) {
            if(detectCorr(couple,p)){
                string desc = (couple.feature1 + "-" + couple.feature2);
                //long timeStamp = (long) ts.returnTime(i);
                AnomalyReport* r = new AnomalyReport(desc ,time);
                report.push_back(*r);
            }
        time++;
        }
    }
    return report;
}

/**
 * check if there is anomaly in point p of a linear correlated couple
 * @param couple - correlatedfeatures object
 * @param p      - the checked point
 * @return True is there is an anomaly, false otherwise.
 */
bool SimpleAnomalyDetector:: detectCorr(correlatedFeatures couple, Point *p ) {
    float maxDist = 1.1 * abs(couple.threshold);
    float dist = dev(*p, couple.lin_reg);
    return (abs(dist) > maxDist);
}


