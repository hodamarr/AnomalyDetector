//
// Hod Amar and Ofek Avergil
//
#include "HybridAnomalyDetector.h"
#include "minCircle.h"

// Auto-generated constructor stub
HybridAnomalyDetector::HybridAnomalyDetector() {
    this->circThreshold = 0.5;
}

/**
 * if the corr is linear finds lin_reg and threshold, if the corr is circular finds the reg_circ
 * @param couple - correlated-features object
 * @param array  - array of pointer to points
 * @param size   - the size of the array;
 */
void HybridAnomalyDetector:: fillCorr(correlatedFeatures* couple, Point** array, size_t size) {
    // if the corr is linear, move to the simple detector fill func.
    if (couple->corrlation >= this->linThreshold) {
        this->SimpleAnomalyDetector::fillCorr(couple,array,size);
    } else{
        //if the corr is circular, find the circ reg
        couple->circ_reg = findMinCircle(array,size);
        couple->isCirc = true;
    }
}

/**
 * check if there is anomaly in point p of a  correlated couple
 * @param couple - correlated-features object
 * @param p      - the checked point
 * @return True is there is an anomaly, false otherwise.
 */
bool HybridAnomalyDetector:: detectCorr(correlatedFeatures couple, Point *p ) {
    if (couple.isCirc) {
        Circle bigger = couple.circ_reg;
        bigger.radius = bigger.radius * 1.1;
        return (!isInside(bigger, *p));
    } else {
        return this->SimpleAnomalyDetector::detectCorr(couple, p);
    }
}


//  Auto-generated destructor stub
 HybridAnomalyDetector:: ~HybridAnomalyDetector() {
}

/**
 * checks if the correlation is over the minimum threshold
 * @param corr - the check correlated
 * @return - true if the correlation is big enough, false otherwise.
 */
bool HybridAnomalyDetector::checkIfCorr(float corr) {
    return (abs(corr) >= this->circThreshold);
}



