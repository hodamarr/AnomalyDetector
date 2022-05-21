//
// Hod Amar and Ofek Avergil
//

#ifndef ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H
#define ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H

#include "timeseries.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"


struct correlatedFeatures{
    correlatedFeatures() : circ_reg(Point(0,0),0), isCirc(false){};
    string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle circ_reg;
    bool isCirc;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
protected:
    void fillCf(const TimeSeries& ts);
    float linThreshold;
    vector<correlatedFeatures> cf;
    virtual void fillCorr(correlatedFeatures* couple, Point **array,size_t size);

public:
    SimpleAnomalyDetector();
    SimpleAnomalyDetector(float thresh);
    virtual ~SimpleAnomalyDetector();

    float GetLinThresh(){
        return  linThreshold;
    }
    void ChangeLinThresh(float thresh);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }

    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);


    virtual bool detectCorr(correlatedFeatures couple, Point *p);

    virtual bool checkIfCorr(float corr);
};

#endif //ANOMALYDETECTOR_SIMPLEANOMALYDETECTOR_H
