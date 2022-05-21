//
// Hod Amar and Ofek Avergil
//

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
    float circThreshold;

public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    bool detectCorr(correlatedFeatures couple, Point *p );
    void fillCorr(correlatedFeatures* couple, Point** array, size_t size);
    bool checkIfCorr(float corr);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
