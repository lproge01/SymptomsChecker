/*
Luke Rogers
CSE 130 Section 1
Final Project - Symptom Checker
4/17/24
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <string>

using namespace std;

//base class for other illnesses
class illness{
	public:
		virtual bool checkSymptoms(const vector<string>& symptoms) const = 0;
		virtual string getIllness() const = 0;
		virtual ~illness(){}
};

//derived class for Covid-19
class covid : public illness {
	public:
		bool checkSymptoms(const vector<string>& symptoms) const override{
			//check if symptoms match covid
			return(symptoms[0] == "present" && symptoms[1] == "present" && symptoms[2] == "present");
		}
		string getIllness() const override {return "Covid-19";}
};

//derived class for cold
class cold : public illness {
	public:
		bool checkSymptoms(const vector<string>& symptoms) const override{
			//check if symptoms match cold
			return(symptoms[3] == "present" && symptoms[5] == "present");
		}
		string getIllness() const override {return "Cold";}
};

//derived class for flu
class flu : public illness {
	public:
		bool checkSymptoms(const vector<string>& symptoms) const override{
			//check if symptoms match flu
			return(symptoms[0] == "present" && symptoms[1] == "present" && symptoms[4] == "present" && symptoms[6] == "present");
		}
		string getIllness() const override {return "Flu";}
};

//class for generating symptoms and checking for illness
class examiner{
	private:
		vector<illness*> illnesses;
		int covidAmount;
		int coldAmount;
		int fluAmount;
		int otherAmount;
		int totalPatients;
		
	public:
		//constructor
		examiner() : covidAmount(0), coldAmount(0), fluAmount(0), otherAmount(0), totalPatients(0){}
		
		//function to check symptoms
		void checkSymptoms(){
			//random symptom generator
			vector<string> symptoms;
			random_device rd;
			mt19937 rng(rd());
			for(int i = 0; i < 7; i++){
				symptoms.push_back((rng() % 2 == 0) ? "present" : "absent");
			}
			          
			//debug lines
//			cout << "Generated symptoms:";
//    		for(const auto& symptom : symptoms) {
//        	cout << " " << symptom;
//			}            
		   
			bool match = false;
			for(auto& illness : illnesses){
				if(illness->checkSymptoms(symptoms)){
					if(illness->getIllness() == "Covid-19"){
						covidAmount++;
					} else if(illness->getIllness() == "Cold"){
						coldAmount++;
					} else if(illness->getIllness() == "Flu"){
						fluAmount++;
					}
					match = true;
					break;
				}
			}
			if(!match){
				otherAmount++;
			}
			totalPatients++;
		}
		
		//function to gather and display results
		void results(){
			cout << "Patients diagnosed:" << endl;
			cout << "Covid-19: " << covidAmount << endl;
			cout << "Cold: " << coldAmount << endl;
			cout << "Flu: " << fluAmount << endl;
			cout << "Other: " << otherAmount << endl;	
		}
		
		//function to report percentages
		void percentages(){
			cout << "Percentage of patients with each illness:" << endl;
			cout << "Covid-19: " << (static_cast<double>(covidAmount) / totalPatients) * 100 << "%" << endl;
			cout << "Cold: " << (static_cast<double>(coldAmount) / totalPatients) * 100 << "%" << endl;
			cout << "Flu: " << (static_cast<double>(fluAmount) / totalPatients) * 100 << "%" << endl;
			cout << "Other: " << (static_cast<double>(otherAmount) / totalPatients) * 100 << "%" << endl;
 		}
 		
 		//function to include illnesses to examiner
 		void addIllness(illness* i){
 			illnesses.push_back(i);
		 }

};

int main(){
	//display the guide
	cout << "Welcome to Symptoms Checker" << endl;
	cout << "Guide:        * Common        + Sometimes/Rarely        - NO"    << endl;
	cout << "=============================================================="  << endl;
	cout << "Symptoms             |         COVID-19 |   Cold   |   Flu   |"  << endl;
	cout << "=============================================================="  << endl;
	cout << "Fever                |            *     |     +    |    *    |"  << endl;
	cout << "Cough                |            *     |     +    |    *    |"  << endl;
	cout << "Shortness of Breath  |            *     |     -    |    -    |"  << endl;
	cout << "Runny Nose           |            +     |     *    |    +    |"  << endl;
	cout << "Headaches            |            +     |     +    |    *    |"  << endl;
	cout << "Sneezing             |            -     |     *    |    -    |"  << endl;
	cout << "Fatigue              |            +     |     +    |    *    |"  << endl;
	cout << "=============================================================="  << endl;
	
	//ask for amount of patients
	int numPatients;
	cout << "Enter the number of patients to test: ";
	cin >> numPatients;
	cout << endl;
	
	examiner exam;
	exam.addIllness(new covid());
	exam.addIllness(new cold());
	exam.addIllness(new flu());
	
	for(int i = 0; i < numPatients; ++i){
		exam.checkSymptoms();
	}
	
	exam.results();
	cout << endl;
	exam.percentages();
	
	return 0;
}