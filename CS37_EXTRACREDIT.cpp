#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

//battle class definition
class Battle 
{
    //declare friend class relation
    friend class Mech;
    private:
        //Declare private variables
        int botsCount;
        float bossPower;
        int *botsPower;

    public:
        //Constructor
        Battle(int, int[], float);
        //Destructor
        ~Battle();
        //Declare function
        float total_damage(); 
        
};

//mech class definition
class Mech
{
    private:
        //Declare private variables
        float defenseMatrixPower;
        int microMissiles;

    public:
        //Constructor
        Mech();
        //Declare function
        float getMicroMissile();
        float getDefenseMatrixPower();
        float micro_missile(Battle &dvaBattle); //takes in a class battle object
        void load(float, float); //the matrixPowerRequired (float) and the missilePowerRequired (float).
    
};

//Constructor for battle 
//copy_n see stdl lecture
Battle::Battle(int botsCount, int botsPower[], float bossPower) 
{
    this->botsCount = botsCount;
    this->botsPower = botsPower;
    this->bossPower = bossPower;
    
}

//Constructor for Mech
Mech::Mech()
{
    defenseMatrixPower = 100.0;
    microMissiles = 10;
}

//function calculating total damage for battle object
float Battle::total_damage()
{
    float sum = 0;
    for (int i = 0; i < botsCount; i++)
    {
        //I know this is wrong but it is the only way currently for program to run.
        //ideal logic: sum += this->botsPower[i]
        sum += botsPower[i] ;
    }

    return (sum + bossPower);
}

//Destructor
Battle::~Battle() {
    delete [] botsPower;
}

float Mech::micro_missile(Battle &dvaBattle)
{
    //calculating missile power required
    float missilePowerRequired = 0;
  	for(int i = 0; i < dvaBattle.botsCount; i++) 
    {
        //I know this is wrong but it is the only way currently for program to run.
        //ideal logic: sum += dvaBattle.botsPower[i]
    	missilePowerRequired += (dvaBattle.botsPower[i]);
    }

  	missilePowerRequired += (dvaBattle.bossPower);
    
    return (3*missilePowerRequired);
    
}

void Mech::load(float matrixPowerRequired, float missilePowerRequired )
{
    //logic for loading defense matrix
    if (Mech::defenseMatrixPower < matrixPowerRequired)
    {
        this->defenseMatrixPower = matrixPowerRequired; 
    }

    //logic for loading missiles for attack
    float target = ceil(missilePowerRequired / 100);
    if ( target > Mech::microMissiles)
    {
        this->microMissiles = target;
    }

}

//getter functiont that returns microMissiles
float Mech::getMicroMissile()
{
    return this->microMissiles;
}

//getter function that returns defenseMatrixPower
float Mech::getDefenseMatrixPower()
{
    return this->defenseMatrixPower;
}

int main()
{
    //declare the variables
    int botsCount;
    float bossPower;
    int micromissile;
    float defensepower;
    float matrixPowerRequired;
    float missilePowerRequired;


    string combatFileName = "combat.txt";
    ifstream combatFile(combatFileName);

    //Check file open
    if (!combatFile.is_open())
    {
        cout << "File fail to open." << endl;
        return 0;      
    }

    //getting values from file
    combatFile >> botsCount;
    int botsPower[botsCount];

    //logic to get combat.txt second line values
    for (int i = 0; i < botsCount; i++)
    {
        combatFile >> botsPower[i];
    }

    //extract other value in combat.txt
    combatFile >> bossPower;

    //Initialize battle and dva
    Battle dvaBattle(botsCount, botsPower, bossPower);
    Mech dva; 

    //Calculate power needed
    matrixPowerRequired = dvaBattle.total_damage();
    missilePowerRequired = dva.micro_missile(dvaBattle);
        
  
    //Load D.Va
    dva.load(matrixPowerRequired, missilePowerRequired);
   
    //Report
    ofstream report;
    report.open("report.txt", ios::out);
    if(!report.is_open())
    {
        cout << "File fail to open." << endl; 
    }
    else
    {
        report << "D.Va's Combat Report" << endl;
        report << "Combat with " << botsCount << " enemy bots and one enemy boss with power " << bossPower << "." << endl;
        report << "Loaded mech with " << dva.getMicroMissile() << " micro missiles and the defense matrix with power " << dva.getDefenseMatrixPower() << "." << endl;
        report << "Ready for combat!";       
    }
    
    //close the files
    combatFile.close();   
    report.close();
    return 0;
}