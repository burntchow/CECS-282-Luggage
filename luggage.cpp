// Name: Aveline Villaganas
// Class (CECS 282-04)
// Project Name (Program 6 - Inheritance/Virtual Functions)
// Due Date (5/5/2022)
//
// I certify that this program is my own original work. I did not copy any part of this program from any other source. 
// I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <iomanip>
#include <string> 
#include <vector> 
#include <map> 
#include <cmath> 
using namespace std; 

class Luggage{ // ========================================================
  private:
    static double totalVolume;
  protected: 
    string type; 
    static int count; 
    int serialNumber; 
    static int serialNumGen; 
  public:
    Luggage(){
      type = "Luggage"; 
      count++; 
      ++serialNumGen;
      serialNumber = serialNumGen; 
      cout << "Creating luggage" << getSerialNum() << endl; 
    } 
  
    virtual ~Luggage(){ // Need to subtract from luggage count 
      cout << "luggage destructor" << getSerialNum() << endl; 
      count--; 
    } 
    static int getCount(){
      return count; 
    }
    string getType(){
      return type; 
    }

    string getSerialNum(){ // Difference between serialNumber and serialNumGen HMMM del later
      return "(SN: " + to_string(serialNumber) + ")";
    }

    static double getTotalVolumeLug(){
      return totalVolume; 
    }
    virtual double getVolume() = 0; 

    static double getTotalVolume(){
      return totalVolume;
    }
    
    void poolVolumes(double vol){
      totalVolume += vol; 
    }

    friend ostream &operator<<(ostream &out, Luggage *lptr){
      //cout << "stream reached" << endl;  
      out << setw(10) << left << lptr->getType() << ": " << setw(6) << right << setprecision(1) << fixed << lptr->getVolume() << setw(12) << right << lptr->getSerialNum(); 
    
      return out; 
    }
};

class Cube: public Luggage{ // ============================================
  private:
    double side; 
    static int count; 
    static double totalVolume; 
  public: 

    Cube(double s){
      side = s;
      count++;
      type = "Cube"; 
      poolVolumes(getVolume());
      totalVolume += getVolume();
    }

    ~Cube(){
      count--; 
      poolVolumes(-1 * getVolume());
      totalVolume -= getVolume();
    }

    double getVolume(){
      return pow(side,3);  
    }

    static double getTotalVolume(){
      return totalVolume; 
    }

    static int getCount(){
      return count; 
    }

};

class Box: public Luggage{ // ===========================================
  private:
    double length;
    double width; 
    double height; 
    static int count; 
    static double totalVolume; 
  public: 

    Box(double l, double w, double h){
      length = l;// not sure if this is necessary yet 
      width = w; 
      height = h; 
      count++;
      type = "Box"; 
      totalVolume += getVolume(); 
      poolVolumes(getVolume());
    }

    ~Box(){
      count--; 
      poolVolumes(-1 * getVolume());
      totalVolume -= getVolume(); 
    }

    double getVolume(){
      return length * width * height;  
    }

    static double getTotalVolume(){
      return totalVolume; 
    }

    static int getCount(){
      return count; 
    } 
};

class Cylinder: public Luggage{ // =======================================
  private:
    double length;
    double radius; 
    static int count; 
    static double totalVolume; 
  public: 

    Cylinder(double r, double l){
      length = l;
      radius = r;
      count++;
      type = "Cylinder"; 
      poolVolumes(getVolume());
      totalVolume += getVolume(); 
    }

    ~Cylinder(){
      count--; 
      poolVolumes(-1 * getVolume());
      totalVolume -= getVolume(); 
    }

    double getVolume(){
      return 3.14159 * pow(radius,2) * length;  
    }

    static double getTotalVolume(){
      return totalVolume; 
    }

    static int getCount(){
      return count; 
    }
};


class Sphere: public Luggage{ // =======================================
  private:
    double radius; 
    static int count; 
    static double totalVolume; 
  public: 

    Sphere(double r){
      radius = r;
      count++;
      type = "Sphere"; 
      poolVolumes(getVolume());
      totalVolume += getVolume();
    }

    ~Sphere(){
      count--; 
      poolVolumes(-1 * getVolume());
      totalVolume -= getVolume();
    }

    double getVolume(){
      double frac = 1.33333333;
      return frac * M_PI * pow(radius,3);  
    }

    static double getTotalVolume(){
      return totalVolume; 
    }

    static int getCount(){
      return count; 
    }
};


class Pyramid: public Luggage{ // =======================================
  private:
    double base;
    double height; 
    static int count; 
    static double totalVolume; 
  public: 

    Pyramid(double b, double h){
      base = b;
      height = h;
      count++;
      type = "Pyramid"; 
      poolVolumes(getVolume());
      totalVolume += getVolume();
    }

    ~Pyramid(){
      count--; 
      poolVolumes(-1 * getVolume());
      totalVolume -= getVolume();
    }

    double getVolume(){
      //cout << "PYRAMID VOLUME HERE" << endl; 
      //double vol = (1/3) * pow(base,2) * height;
      double frac = 0.333333333333; 
      double vol = frac * pow(base,2) * height;
      //cout << "IT SHOULD BE : " << vol << endl; 
      return vol;  
    }

    static double getTotalVolume(){
      return totalVolume; 
    }

    static int getCount(){
      return count; 
    }
};


// Luggage Display stuff
void showAllLuggage(vector<Luggage*> container){ // This calls the << op 
  int count = 0; 
  //cout << "show lug reached" << endl; 
  for(auto l:container){ // container is vector<luggage*>
    cout << ++count << ") " << l << endl; 
    //cout << typeid(l).name() << endl; 
  } 
} 

void showAllTotals(vector<Luggage*> container){
  cout << "Total volume:";  
  cout << setw(15) << right << Luggage::getTotalVolumeLug() << endl;
  
  map<string, int> itemCounts; // Make a make to count frequency 
  for(auto l:container){
    itemCounts[l->getType()]++;
  }
  cout << endl; 
  
  cout << "Total Luggage Items:" << setw(8) << right << container.size() << endl;

  map<string, int>::iterator items;
  for(items = itemCounts.begin(); items != itemCounts.end(); items++){
    string part1 =  items->first + ":"; 
    cout << "Total " << setw(12) << left << part1 << setw(10) << right << items->second << endl;
  }
}

void showAllVolumes(vector<Luggage*> container){
  cout << setw(12) << left << "Item Type" << setw(13) << right << "Total Volume" << endl; 
  cout << setw(12) << left << "Cube" << setw(13) << right << setprecision(1) << Cube::getTotalVolume() << endl;
  cout << setw(12) << left << "Box" << setw(13) << right << setprecision(1) << Box::getTotalVolume() << endl;
  cout << setw(12) << left << "Cylinder" << setw(13) << right << setprecision(1) << Cylinder::getTotalVolume() << endl;
  cout << setw(12) << left << "Sphere" << setw(13) << right << setprecision(1) << Sphere::getTotalVolume() << endl;
  cout << setw(12) << left << "Pyramid" << setw(13) << right << setprecision(1) << Pyramid::getTotalVolume() << endl;
  cout << setw(12) << left << "Luggage" << setw(13) << right << Luggage::getTotalVolumeLug() << endl; 
}

// Menu Stuff 
int addLuggage(){
  int userChoice = 0;  
  cout << "Available Luggage Types:" << endl; 
  cout << "1) Cube" << endl;
  cout << "2) Box" << endl; 
  cout << "3) Cylinder" << endl;
  cout << "4) Sphere" << endl;
  cout << "5) Pyramid" << endl; 
  cin >> userChoice; 
  cout << endl;
  return userChoice; 
}

int menu(){
  int userChoice = 0;
  cout << "Menu:" << endl;
  cout << "1) Add luggage to storage container" << endl; 
  cout << "2) Remove luggage from storage container" << endl; 
  cout << "3) Show all luggage" << endl;
  cout << "4) Show total volumes" << endl; 
  cout << "5) Quit" << endl; 
  cin >> userChoice;
  cout << endl;
  return userChoice; 
}


// Total Volumes defined: 
double Cube::totalVolume = 0; 
double Box::totalVolume = 0; 
double Cylinder::totalVolume = 0; 
double Sphere::totalVolume = 0; 
double Pyramid::totalVolume = 0; 

// Counts defined: 
int Luggage::count = 0;
int Cube::count = 0; 
int Box::count = 0; 
int Cylinder::count = 0; 
int Sphere::count = 0; 
int Pyramid::count = 0; 

int Luggage::serialNumGen = 0; // start off at 1 
double Luggage::totalVolume = 0;


int main() { // ======================================================

  vector<Luggage*> lugContainer;
 
  int userChoice = -1; 
  while(userChoice != 5){
    userChoice = menu(); 

    if(userChoice == 1){ // Add Luggage -------------------------------
      int luggageChoice = addLuggage(); 
      if(luggageChoice == 1){
        double side = 0; 
        cout << "You have chosen CUBE." << endl; 
        cout << "Enter Parameters for SIDE: " << endl; 
        cin >> side;
        Luggage *anotherLug = new Cube(side); 
        lugContainer.push_back(anotherLug); 
        
      }else if(luggageChoice == 2){
        double length = 0; 
        double width = 0; 
        double height = 0; 
        cout << "You have chosen BOX." << endl; 
        cout << "Enter Parameters for LENGTH: " << endl; 
        cin >> length; 
        cout << "Enter Parameters for WIDTH: " << endl;
        cin >> width; 
        cout << "Enter Paramters for HEIGHT: " << endl; 
        cin >> height; 
        Luggage *anotherLug = new Box(length, width, height); 
        lugContainer.push_back(anotherLug); 
        
      }else if(luggageChoice == 3){
        double radius = 0;
        double length = 0; 
        cout << "You have chosen CYLINDER." << endl; 
        cout << "Enter Parameters for RADIUS: " << endl; 
        cin >> radius; 
        cout << "Enter Parameters for LENGTH: " << endl; 
        cin >> length; 
        Luggage *anotherLug = new Cylinder(radius, length); 
        lugContainer.push_back(anotherLug);
        
      }else if(luggageChoice == 4){
        double radius = 0; 
        cout << "You have chosen SPHERE." << endl; 
        cout << "Enter Parameters for RADIUS: " << endl; 
        cin >> radius; 
        double frac = 1.33333333;
        //cout << "PREDICTED: " << frac * 3.14159 * pow(radius,3) << endl; 
        Luggage *anotherLug = new Sphere(radius); 
        lugContainer.push_back(anotherLug); 
        
      }else if(luggageChoice == 5){
        double base = 0; 
        double height = 0; 
        cout << "You have chosen PYRAMID." << endl; 
        cout << "Enter Parameters for BASE: " << endl; 
        cin >> base; 
        cout << "Enter Parameters for HEIGHT: " << endl; 
        cin >> height; 
        Luggage *anotherLug = new Pyramid(base, height);
        lugContainer.push_back(anotherLug); 
      }
      cout << endl; 
    }else if(userChoice == 2){ // Remove Luggage ------------------------- 
      int userRemoves = 0; 
      showAllLuggage(lugContainer);
      cout << "Enter which Luggage to remove: ";
      cin >> userRemoves; 

      delete lugContainer[userRemoves - 1]; // Destructor 
      lugContainer.erase(lugContainer.begin() + (userRemoves - 1));  
       
      cout << endl; 
      
    }else if(userChoice == 3){ // Show all luggage  ----------------------

      showAllLuggage(lugContainer);
      showAllTotals(lugContainer); 

      cout << endl; 
      
    }else if(userChoice == 4){ // Show total volume  ---------------------

      showAllVolumes(lugContainer);
      cout << endl; 
      
    }else if(userChoice == 5){ // Quit  ----------------------------------
      return 0; 
    }
  }
}