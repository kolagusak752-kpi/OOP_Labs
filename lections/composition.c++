#include <string>
#include <iostream>
#include <vector>
class PC {

    private:
    std::string* Monitor;
    std::string CPU;
    public:
    PC();
    void setMonitor(std::string* Monitor) {
        this->Monitor = Monitor;
    };
};

class Player {
    private:
    class Inventory {
        public:
        Inventory() {
            this->array = new int[100];
        }
        private:
        int* array;
    };
    Inventory inventory;
    public:
    void additem(int item) {

    }

};

class Armor {
    private:
    int physicResist;
    int magicResist;
    public:
    Armor(int physicResist, int magicResist): physicResist(physicResist), magicResist(magicResist) {};
    Armor operator+(Armor& armor) {
        int physicResist = this->physicResist + armor.physicResist;
        int magicResist = this->magicResist + armor.magicResist;
        return Armor(physicResist, magicResist);
    }
        int* getResists() {
        int resists[2];
        resists[0] = physicResist;
        resists[1] = magicResist;
        return resists;
    }
};

Armor v1(10,20);
Armor v2(30,40);

Armor v3 = v1 + v2;
int main() {
    std::cout << v3.getResists()[0] << "and" << v3.getResists()[1];
    return 0;
}