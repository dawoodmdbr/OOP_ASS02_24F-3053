#include<iostream>
using namespace std;

class ResourceManager{
public:
    enum ResourceType { FUEL, FOOD, WATER, MEDICAL_SUPPLIES, TECHNOLOGY, MATERIALS };
    struct Resource{
        ResourceType type;
        double quantity;
        double value;
        string expirationDate;
        void consume (double amount){
            quantity -= amount;
        }
    };
    struct Resource resources[5];
    int resourceCount = 0;
    void addResource(Resource * resource){
        if(resourceCount < 5){
            resources[resourceCount++] = *resource;
        }
    }
    void displayResources(){
        for(int i = 0; i < resourceCount; i++){
            cout << "Type: " << resources[i].type << endl;
            cout << "Quantity: " << resources[i].quantity << endl;
            cout << "Value: " << resources[i].value << endl;
            cout << "Expiration Date: " << resources[i].expirationDate << endl;
        }
        cout<< endl;
    }
};

class CrewManager{
public:
    struct CrewMember{
        string name;
        string role;
        string rank;
        int experienceYears;
        struct Mission* assignedMission[5];
        int missionCount = 0;
        void assignMission(struct Mission* mission){
            if(missionCount < 5){
                assignedMission[missionCount++] = mission;
            }
        }
        void displayInfo(){
            cout << "Name: " << name << endl;
            cout << "Role: " << role << endl;
            cout << "Rank: " << rank << endl;
            cout << "Experience Years: " << experienceYears << endl << endl;
        }
    };
    struct CrewMember crew[5];
    int crewCount = 0;
    void addCrewMember(CrewMember* crewMember){
        if(crewCount < 5){
            crew[crewCount++] = *crewMember;
        }
    }
    void assignCrewToMission(CrewMember* crewMember, Mission* mission){
        crewMember->assignMission(mission);
    }
    void displayCrewInfo(){
        for(int i = 0; i < crewCount; i++){
            crew[i].displayInfo();
        }
        cout << endl;
    }
};

class VehicleManager{
public:
    enum VehicleType { SHUTTLE, ROVER, SPACE_STATION, FREIGHTER, PROBE };
    struct Vehicle{
        string name;
        enum VehicleType type;
        double fuelLevel;
        int crewCapacity;
        struct CrewMember* crewMembers[5];
        int crewCount = 0;
        void assignCrew(CrewMember* crewMember){
            if(crewCount < 5){
                crewMembers[crewCount++] = crewMember;
            }
        }
        void refuel(double amount){
            fuelLevel += amount;
        }
    };
    struct Vehicle vehicles[5];
    int vehicleCount = 0;
    void addVehicle(Vehicle* vehicle){
        if(vehicleCount < 5){
            vehicles[vehicleCount++] = *vehicle;
        }
    }
    void assignCrewToVehicle(CrewMember* crewMember, Vehicle* vehicle){
        vehicle->assignCrew(crewMember);
    }
    void refuelVehicle(Vehicle* vehicle, double amount){
        vehicle->refuel(amount);
    }
    void displayVehicleInfo(){
        for(int i = 0; i < vehicleCount; i++){
            cout << "Name: " << vehicles[i].name << endl;
            cout << "Type: " << vehicles[i].type << endl;
            cout << "Fuel Level: " << vehicles[i].fuelLevel << endl;
            cout << "Crew Capacity: " << vehicles[i].crewCapacity << endl;
            cout << "Crew Count: " << vehicles[i].crewCount << endl << endl;
        }
        cout<< endl;
    }
};

class MissionManager{
    public:
    enum MissionType { EXPLORATION, TRANSPORT, DEFENSE, REPAIR, COLONIZATION };
    struct Mission{
        string name;
        enum MissionType type;
        string startDate;
        string endDate;
        string status;
        struct CrewMember* assignedCrew[5];
        struct Vehicle* assignedVehicle;
        int crewCount = 0;
        int vehicleCount = 0;
        void assignCrewMember(CrewMember* crewMember){
            if(crewCount < 5){
                assignedCrew[crewCount++] = crewMember;
            }
        }
        void assignVehicle(Vehicle* vehicle){
            assignedVehicle = vehicle;
        }
        void updateMissionStatus(string s){
            s = status;
        }
        void displayMissionDetails(){
            cout << "Name: " << name << endl;
            cout << "Type: " << type << endl;
            cout << "Start Date: " << startDate << endl;
            cout << "End Date: " << endDate << endl;
            cout << "Status: " << status << endl << endl;
        }
    };
};


int main()
{
    cout << "Hello World" << endl;
    return 0;
}