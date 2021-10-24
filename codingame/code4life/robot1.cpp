#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 * Bring data on patient samples from the diagnosis machine to the laboratory with enough molecules to produce medicine!
 **/

 /* ------------------------------ SAMPLE ------------------------------------ */
 // Usually in a .h and .cpp appart from this one

 class Sample {
 public:
 	typedef enum carried_by_t {
 		carried_by_me = 0,
 		carried_by_it = 1,
 		carried_by_none = -1,
 	} carried_by_t;
 private:
 	int sampleId;         /**< Unique ID for the sample */
 	carried_by_t carriedBy; /**< which robot is carriying the sample */
 	int rank;               /**< Ignore for this league */
 	string expertiseGain;   /**< Ignore for this league */
 	int health;             /**< Health points you gain for this sample */
 	int costA;              /**< Molecules of type A needed to produce */
 	int costB;              /**< Molecules of type B needed to produce */
 	int costC;              /**< Molecules of type C needed to produce */
 	int costD;              /**< Molecules of type D needed to produce */
 	int costE;              /**< Molecules of type E needed to produce */
 public:
 	/**
 	 * @brief default constructor (needed for array)
 	 */
 	 Sample();

 	/**
 	 * @brief Conversion function
 	 */
 	carried_by_t num2enum(int carriedBy);

 	/**
 	 * @brief Conversion function
 	 */
 	int enum2num(carried_by_t carriedBy);

 	/**
 	 * @brief sets the information for the sample
 	 */
 	void set(int sampleId, int carriedBy, int rank, string expertiseGain,
 	         int health, int costA, int costB, int costC, int costD, int costE);

 	/**
 	 * @brief debug information
 	 */
 	void debug();

 	/* --- getters --- */
 	inline int getSampleId() {return sampleId;};
  	inline carried_by_t getCarriedBy() {return carriedBy;}
  	inline int getRank() {return rank;}
  	inline string getExpertiseGain() {return expertiseGain;}
  	inline int getHealth() {return health;}
  	inline int getCostA() {return costA;}
  	inline int getCostB() {return costB;}
  	inline int getCostC() {return costC;}
  	inline int getCostD() {return costD;}
  	inline int getCostE() {return costE;}
 };
 /* --- Sample API implementation --- */
 Sample::Sample()
 {
 	sampleId = 0;
 	carriedBy = carried_by_none;
 	rank = 0;
 	expertiseGain = "";
 	health = 0;
 	costA = 0;
 	costB = 0;
 	costC = 0;
 	costD = 0;
 	costE = 0;
 }

 void Sample::set(int sampleId, int carriedBy, int rank, string expertiseGain,
                  int health, int costA, int costB, int costC, int costD,
                  int costE)
 {
 	this->sampleId = sampleId;
 	this->carriedBy = static_cast<carried_by_t>(carriedBy);
 	this->rank = rank;
 	this->expertiseGain = expertiseGain;
 	this->health = health;
 	this->costA = costA;
 	this->costB = costB;
 	this->costC = costC;
 	this->costD = costD;
 	this->costE = costE;
 }

 void Sample::debug()
 {
 	cerr << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
 	cerr << "Sample " << sampleId << " carriedBy " << carriedBy << endl;
 	cerr << "Rank " << rank << " expertiseGain " << expertiseGain << endl;
 	cerr << "Health" << health << endl;
 	cerr << "Costs " << costA << ", " << costB << ", "
 	     << costC << ", " << costD << ", " << costE << endl;
 	cerr << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
 }

/* ------------------------------- ROBOT ------------------------------------ */
// Usually in a .h and .cpp appart from this one

/**
 * @brief Defines the robot data and functionality
 */
class Robot {
private:
	static int id_c;/**< ID counter */
	int id;         /**< Personal ID */
	string target;  /**< Where is going */
	int eta;        /**< Ignore for this league */
	int score;      /**< Player number of points */
	Sample sample;  /**< Chosen sample */
	int storageA;   /**< Molecules of type A held by the robot */
	int storageB;   /**< Molecules of type B held by the robot */
	int storageC;   /**< Molecules of type C held by the robot */
	int storageD;   /**< Molecules of type D held by the robot */
	int storageE;   /**< Molecules of type E held by the robot */
	int expertiseA; /**< Ignore for this league */
	int expertiseB; /**< Ignore for this league */
	int expertiseC; /**< Ignore for this league */
	int expertiseD; /**< Ignore for this league */
	int expertiseE; /**< Ignore for this league */
	int QuantityA;  /**< Ignore for this league */
	int QuantityB;  /**< Ignore for this league */
	int QuantityC;  /**< Ignore for this league */
	int QuantityD;  /**< Ignore for this league */
	int QuantityE;  /**< Ignore for this league */

	typedef enum module_st_t {
		module_st_diagnosis_pre,  // Travel
		module_st_diagnosis_get,  // Collect
		module_st_molecules,      // Collect || Travel
		module_st_laboratory_pre, // Travel
		module_st_laboratory_get, // Produce
		module_st_start_pos,      // Start possition
	} module_st_t;
	module_st_t status; /**< Where the robot is */

	/**
	 * @brief converts status to string
	 */
	string module_st2txt(module_st_t st);
public:
	Robot();
	/**
	 * @brief Sets the environment data into the robot
	 */
	void set(string target, int eta, int score, int storageA, int storageB,
	         int storageC, int storageD, int storageE, int expertiseA,
	         int expertiseB, int expertiseC, int expertiseD, int expertiseE);

	/**
	 * @brief Sets the robot in motion, it will output a command given
	          its internal data
	*/
	string act(vector<Sample> samples);

	/**
	 * @brief Prints debug information about the robot
	 */
	void debug();

	/**
	 * @brief Choses best sample
	 */
	void setSample(const vector<Sample> & samples);
};

int Robot::id_c = 0; // Static allocation

/* --- Robot API implementation --- */
Robot::Robot()
{
	id = id_c;
	id_c++;
	this->status = module_st_start_pos;
	QuantityA = 0;
	QuantityB = 0;
	QuantityC = 0;
	QuantityD = 0;
	QuantityE = 0;
	sample = Sample();
}

void Robot::set(string target, int eta, int score, int storageA, int storageB,
                int storageC, int storageD, int storageE, int expertiseA,
                int expertiseB, int expertiseC, int expertiseD, int expertiseE)
{
	this->target = target;
	// TODO: check target with status
	this->eta = eta;
	this->score = score;
	this->storageA = storageA;
	this->storageB = storageB;
	this->storageC = storageC;
	this->storageD = storageD;
	this->storageE = storageE;
	this->expertiseA = expertiseA;
	this->expertiseB = expertiseB;
	this->expertiseC = expertiseC;
	this->expertiseD = expertiseD;
	this->expertiseE = expertiseE;
}

string Robot::act(vector<Sample> samples)
{
	/*
		1. Start possition
		2. Max 3 sample data and 10 molecules
		3. Goto module
		4. Connect
	*/
	ostringstream res;
	switch (this->status) {
	case module_st_diagnosis_pre:
        this->setSample(samples);
		this->status = module_st_diagnosis_get;
		res << "CONNECT " << this->sample.getSampleId();
		break;
	case module_st_diagnosis_get:
		this->status = module_st_molecules;
		res << "GOTO " << module_st2txt(this->status);
		break;
	case module_st_molecules:
    {
		// 1. get required molecules
		int owned[] = {this->QuantityA, this->QuantityB, this->QuantityC,
		               this->QuantityD, this->QuantityE};
		int required[] = {this->sample.getCostA(), this->sample.getCostB(),
		                  this->sample.getCostC(), this->sample.getCostD(),
		                  this->sample.getCostE()};
		int i = 0;
		while(i < 5) {
            cerr << i << ": " << owned[i] << " - " << required[i] << endl;
			if (required[i] > owned[i])
				break;
			i++;
		}
		char molecules[] = {'A','B','C','D','E'};
			// connect
		if (i < 5) {
            // TODO: A robot cannot hold more than 10 molecules, escape condition needed
			res << "CONNECT " << molecules[i];
            owned[i]++;
            this->QuantityA = owned[0];
            this->QuantityB = owned[1];
            this->QuantityC = owned[2];
            this->QuantityD = owned[3];
            this->QuantityE = owned[4];
		} else {
			// advance
			this->status = module_st_laboratory_pre;
			res << "GOTO " << module_st2txt(this->status);
		}
    }
		break;
	case module_st_laboratory_pre:
        this->status = module_st_laboratory_get;
		res << "CONNECT " << this->sample.getSampleId();
        this->QuantityA -= this->sample.getCostA();
        this->QuantityB -= this->sample.getCostB();
        this->QuantityC -= this->sample.getCostC();
        this->QuantityD -= this->sample.getCostD();
        this->QuantityE -= this->sample.getCostE();
		break;
	case module_st_laboratory_get:
	case module_st_start_pos:
		this->status = module_st_diagnosis_pre;
		res << "GOTO " << module_st2txt(this->status);
		break;
	}
	return res.str();
}

void Robot::setSample(const vector<Sample> & samples)
{
	// First strategy is to go for the cheapest sample available to manufacture
	struct cost_t {
		int cost;
		Sample s;
	};
	cost_t best_sample;
	best_sample.cost = 10000; // TODO
	for (auto s : samples) {
		if (s.getCarriedBy() != Sample::carried_by_none)
			continue;
		int tmp_cost = (s.getCostA() - this->QuantityA)
		             + (s.getCostB() - this->QuantityB)
		             + (s.getCostC() - this->QuantityC)
		             + (s.getCostD() - this->QuantityD)
		             + (s.getCostE() - this->QuantityE);
		if (tmp_cost < best_sample.cost) {
            cerr << "Sample " << s.getSampleId() << " is the best at " << tmp_cost << endl;
			best_sample.cost = tmp_cost;
			best_sample.s = s;
		}
	}
	this->sample = best_sample.s;
}

void Robot::debug()
{
	cerr << "------------------------------------------------------" << endl;
	cerr << "Robot " << id << " is in " << module_st2txt(status) << endl;
	cerr << "Score " << score << " eta " << eta << endl;
	cerr << "Storage " << storageA << ", " << storageB << ", "
	     << storageC << ", " << storageD << ", " << storageE << endl;
	cerr << "Expertise " << expertiseA << ", " << expertiseB << ", "
	     << expertiseC << ", " << expertiseD << ", " << expertiseE << endl;
	cerr << "Quantity " << QuantityA << ", " << QuantityB << ", "
	     << QuantityC << ", " << QuantityD << ", " << QuantityE << endl;
	cerr << "------------------------------------------------------" << endl;
}

string Robot::module_st2txt(module_st_t st)
{
	switch (st) {
	case module_st_diagnosis_pre:
	case module_st_diagnosis_get:
		return "DIAGNOSIS";
	case module_st_molecules:
		return "MOLECULES";
	case module_st_laboratory_pre:
	case module_st_laboratory_get:
		return "LABORATORY";
	case module_st_start_pos:
		return "START_POS";
	default: return "ukn";
	}
}

/** Number of avaliable modules */
typedef struct available_t {
	int availableA;
	int availableB;
	int availableC;
	int availableD;
	int availableE;

	void debug()
	{
		cerr << "List of availables " << availableA << ", " << availableB << ", "
		     << availableC << ", " << availableD << ", " << availableE << endl;
	}
} available_t;

int main()
{
	int projectCount;
	cin >> projectCount; cin.ignore();
	cerr << "projectCount: " << projectCount << endl;
	for (int i = 0; i < projectCount; i++) {
		int a;
		int b;
		int c;
		int d;
		int e;
		cin >> a >> b >> c >> d >> e; cin.ignore();
		cerr << "abcde " << a << b << c << d << e << endl;
	}

	Robot r1;
	Robot r2;
	// game loop
	while (1) {
		for (int i = 0; i < 2; i++) {
			string target;
			int eta;
			int score;
			int storageA;
			int storageB;
			int storageC;
			int storageD;
			int storageE;
			int expertiseA;
			int expertiseB;
			int expertiseC;
			int expertiseD;
			int expertiseE;
			cin >> target >> eta >> score >> storageA >> storageB >> storageC >>
			       storageD >> storageE >> expertiseA >> expertiseB >>
			       expertiseC >> expertiseD >> expertiseE; cin.ignore();
			if (!i) {
				r1.set(target, eta, score, storageA, storageB, storageC,
				       storageD, storageE, expertiseA, expertiseB, expertiseC,
				       expertiseD, expertiseE);
			} else {
				r2.set(target, eta, score, storageA, storageB, storageC,
				       storageD, storageE, expertiseA, expertiseB, expertiseC,
				       expertiseD, expertiseE);
			}
		}
		r1.debug();
		r2.debug();
		available_t av;
		cin >> av.availableA >> av.availableB >> av.availableC >>
		       av.availableD >> av.availableE; cin.ignore();
		av.debug();
		int sampleCount;
		cin >> sampleCount; cin.ignore();
		vector<Sample> samples;
		for (int i = 0; i < sampleCount; i++) {
			Sample s;
			int sampleId;
			int carriedBy;
			int rank;
			string expertiseGain;
			int health;
			int costA;
			int costB;
			int costC;
			int costD;
			int costE;
			cin >> sampleId >> carriedBy >> rank >> expertiseGain >> health >>
			       costA >> costB >> costC >> costD >> costE; cin.ignore();
			s.set(sampleId, carriedBy, rank, expertiseGain, health,
			      costA, costB, costC, costD, costE);
			//s.debug();
			samples.push_back(s);
		}

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		cout << r1.act(samples) << endl;
	}
}
