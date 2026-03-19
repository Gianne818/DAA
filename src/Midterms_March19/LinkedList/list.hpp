
class List{
public:
    virtual void addFirst(int n) = 0;
    virtual void addLast(int n) = 0;
    virtual int get(int pos) = 0;
    virtual int removeFirst() = 0;
    virtual int removeLast() = 0;
    virtual void print() = 0;
};

/*
- implement all functions for both singly and double linked list, where they inherit this list.
- standard implementation for singly and doubly
- remove functions return the number removed
- pos is 1-based indexing
- no twist whatsoever even on main. just choose between S and D in main
*/