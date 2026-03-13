using namespace std;

class HashTable{
public:
    virtual int insert(string) = 0;
    virtual int remove(string) = 0;
    virtual int search(string) = 0;
    virtual void print() = 0; 

};

