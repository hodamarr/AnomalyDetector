//
// Hod Amar and Ofek Avergil
//

#ifndef ANOMALYDETECTOR_TIMESERIES_H
#define ANOMALYDETECTOR_TIMESERIES_H
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>


using namespace std;

class TimeSeries{
    map<string, vector<float>> data;
    vector<string> features;
    int vecLen;
    //vector<float> time;

public:

    TimeSeries(const char* CSVfileName);

    const vector<string> getFeaturesNames() const;

    //float returnTime(int i) const;

    vector<float> getData(string s) const;

    map<string, vector<float>> getMap() const;

    //vector<float> makeTimeVec();

    int lineSize();
};



#endif //ANOMALYDETECTOR_TIMESERIES_H
