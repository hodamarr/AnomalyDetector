//
// Hod Amar and Ofek Avergil
//

#include "CLI.h"
/**
 * constructor
 * @param dio - chosen IO object
 */
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->data = new AnomalyDetectorData();
    //fill the map with the six types of commands
    this->options.insert({1,new UploadCommand(this->dio, this->data)});
    this->options.insert({2,new SettingsCommand(this->dio, this->data)});
    this->options.insert({3,new AnomalyDetectionCommand(this->dio, this->data)});
    this->options.insert({4,new ResultCommand(this->dio, this->data)});
    this->options.insert({5,new AnalyzeCommand(this->dio, this->data)});
    this->options.insert({6,new ExitCommand(this->dio, this->data)});
}

/**
 * the function prints the menu, and call the chosen commands.
 */
void CLI::start(){
    //print the menu
    this->dio->write("Welcome to the Anomaly Detection Server.\n"
                     "Please choose an option:\n");

    for (auto &iter : options) {
        this->dio->write(to_string(iter.first));
        this->dio->write(".");
        this->dio->write(iter.second->getDes());
        this->dio->write("\n");
    }

    //direct to the chosen command
    float option;
    this->dio->read(&option);
    if (option >= 1 && option <= 6) {
        this->options.find(option)->second->execute();
    }

    //finish the program if necessary or start over
    if (option == 6) {
        return;
    } else {
        this->start();
    }
}

/**
 * destructor
 */
CLI::~CLI() {
}

