// STRICTLY DONT EDIT CODES BELOW
#include <cstdlib>
#include <iostream>
using namespace std;

class Edge {
    private:
    int name;
    char origin;
    char destination;

    public:
    Edge(int n, char o, char d) : name(n), origin(o), destination(d) {};

    int getName(){
        return name;
    }

    char getOrigin(){
        return origin;
    }

    char getDestination(){
        return destination;
    }

    void setName(int x){
        name = x;
    }

    void setOrigin(char x){
        origin = x;
    }

    void setDestination(char x){
        destination = x; 
    }

    void toString(){
        cout << name << " | (" << origin <<  " -> " << destination << ")";
    }
};