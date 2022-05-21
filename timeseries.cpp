//
// Hod Amar and Ofek Avergil
//

#include "timeseries.h"

///** constructor
///** initialize map of strings (keys) and vectors.
TimeSeries::TimeSeries(const char* CSVfileName) {
    string line, token;
    ifstream file;
    stringstream ss;

    /// open file and check it
    file.open(CSVfileName);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open file\n");
    }

    /// getting features name
    if (file.good()) {
        getline(file, line);
        ss.str(line);
        while (getline(ss, line, ',')) {
            features.push_back(line);
        }
    }

    /// making map of lines
    while (getline(file, line)) {
        std::stringstream ss1(line);
        /// making the vector and initial keymap
        for (auto element : features) {
            getline(ss1, token, ',');
            data[element].push_back(stof(token));
        }
    }
    vecLen = data[features[0]].size();
    //time = makeTimeVec();
    file.close();
}

const vector<string> TimeSeries::getFeaturesNames() const {
    return features;
}

vector<float> TimeSeries::getData(string s) const{
    /// we assome that the string is valid
    std::vector<float> v;
    v = data.find(s)-> second;
    return v;
}

map<string, vector<float>> TimeSeries::getMap() const {
    return this->data;
}

int TimeSeries::lineSize(){
    if (this->data.empty() && features.empty()){
        return 0;
    }
    else{
        return this->data[features[0]].size();;
    }
}

///** initialize time vector
//vector<float> TimeSeries::makeTimeVec(){
//    vector<float> v;
//    smatch m1;
//    regex r("[A-Za-z]*[Tt][Ii][Mm][Ee].*");
//    int flag = 0;
//    /// searching for "TIME" in features vector
//    for (std:: string element : features){
//        std:: regex_match(element,m1,r);
//        if (!m1.empty()){
//            flag = 1;
//            v = data[element];
//            break;
//        }
//    }
//    /// if doesnt exist - making with the same interval.
//    if (!flag) {
//        for (int i = 0; i < vecLen; ++i) {
//            v.push_back(i * 1);
//        }
//    }
//    return v;
//}

//float TimeSeries::returnTime(int i) const {
//    if (i <= vecLen){
//        return time[i];
//    }
//}

