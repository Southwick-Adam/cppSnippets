#include <iostream>
#include <vector>
#include <string>
using namespace std;

//global variable
char **gridPtr;
const int gridSize = 20;

bool testgrid(int posx, int posy);
char** setUpGrid();
void print();

class Organism {
    int age;
    int breedAge;
    int posX;
    int posY;
    char symbol;
    public:
        Organism(){
            age = 0;
            breedAge = 0;
            posX = 0;
            posY = 0;
            symbol = '?';
        }
        Organism(int newBreedAge, int newposx, int newposy, char sym){
            age = 0;
            breedAge = newBreedAge;
            posX = newposx;
            posY = newposy;
            symbol = sym;
        }
        void setPos(int x, int y) {posX = x; posY = y;}
        int getPosX() { return posX; }
        int getPosY() { return posY; }
        int getAge() { return age; }
        int getBreedAge() { return breedAge; }
        void ageUp() { age++; }
        void ageReset() { age = 0; }
        virtual void step();
        virtual void move();
        void tryBreed();
        virtual void breed(int px, int py);
        char getSymbol() { return symbol; }
};

void Organism::step(){
    ageUp();
    move();
}

void Organism::move(){
    int random = rand() % 4;
    int testpos[2] = {posX, posY};
    if (random == 0){
        testpos[0]++;
    } else if (random == 1){
        testpos[0]--;
    } else if (random == 2){
        testpos[1]++;
    } else {
        testpos[1]--;
    }
    if (testgrid(testpos[0], testpos[1])){
        gridPtr[posX][posY] = '-';
        posX = testpos[0];
        posY = testpos[1];
        gridPtr[posX][posY] = symbol;
    }
    tryBreed();//After moving they try and reproduce.
}

void Organism::tryBreed(){
    if (age >= breedAge){
        int xVal = posX;
        int yVal = posY;
        if (testgrid(posX+1, posY)){
            xVal++;
        } else if (testgrid(posX-1, posY)){
            xVal--;
        } else if (testgrid(posX, posY+1)){
            yVal++;
        } else if (testgrid(posX, posY-1)){
            yVal--;
        }else{
            return;
        }
        breed(xVal, yVal);
    }else{
        return;
    }
}

void Organism::breed(int px, int py){
    ageReset();
    return;
}

class Ant :public Organism {
    public:
        Ant() : Organism(3, 0, 0, 'o'){}
        Ant(int px, int py) : Organism(3, px, py, 'o'){}
        void breed(int px, int py);
        void move();
};

void spawnAnt(int posx, int posy);

vector<Ant*> antVec;

void Ant::move(){
    int random = rand() % 4;
    int px = getPosX();
    int py = getPosY();
    int testpos[2] = {px, py};
    if (random == 0){
        testpos[0]++;
    } else if (random == 1){
        testpos[0]--;
    } else if (random == 2){
        testpos[1]++;
    } else {
        testpos[1]--;
    }
    if (testgrid(testpos[0], testpos[1])){
        gridPtr[px][py] = '-';
        setPos(px, py);
        gridPtr[px][py] = getSymbol();
    }
    tryBreed();//After moving they try and reproduce.
}

void Ant::breed(int px, int py){
    spawnAnt(px, py);
    ageReset();
}

class Doodlebug : public Organism {
    int timeSinceFed;
    int starveTime;
    bool movedToEat;
    public:
        Doodlebug() : Organism(8, 0, 0, 'X'){
            timeSinceFed = 0;
            starveTime = 3;
            movedToEat = false;
        }
        Doodlebug(int px, int py) : Organism(8, px, py, 'X'){
            timeSinceFed = 0;
            starveTime = 3;
            movedToEat = false;
        }
        void timeSinceFedUp() { timeSinceFed++; }
        void setMovedToEat(bool b) { movedToEat = b; }
        void move();
        void tryEat();
        void eatAnt(int px, int py);
        void step();
        bool checkStarve();
        void starve();
        void breed(int px, int py);
};

vector<Doodlebug*> doodVec;

void Doodlebug::step(){
    setMovedToEat(false);
    ageUp();
    timeSinceFedUp();
    tryEat();
    if (checkStarve()){
        starve();
    }else{
        move(); 
    }
}

void Doodlebug::tryEat(){
    int px = getPosX();
    int py = getPosY();
    
    if (px < gridSize - 1){//this check is to avoid trying to call a cell that isnt there
        if (gridPtr[px + 1][py] == 'o'){
            eatAnt(px + 1, py);
            return;
        }
    }
    if (px > 0){
        if (gridPtr[px - 1][py] == 'o'){
            eatAnt(px - 1, py);
            return;
        }
    }
    if (py < gridSize - 1){
        if (gridPtr[px][py + 1] == 'o'){
            eatAnt(px, py + 1);
            return;
        }
    }
    if (py > 0){
        if (gridPtr[px][py - 1] == 'o'){
            eatAnt(px, py - 1);
            return;
        }
    }
}

void Doodlebug::eatAnt(int px, int py){
    Ant* temp = nullptr;
    vector<Ant*> tempVec;
    for (int v = 0; v < antVec.size(); v++){
        if((antVec[v]->getPosX() == px) && (antVec[v]->getPosY() == py)){
            delete[] antVec[v];
            temp = antVec[v];
        }else{
            tempVec.push_back(antVec[v]);
        }
    }
    antVec.clear();
    for (int v = 0; v < tempVec.size(); v++){
        antVec.push_back(tempVec[v]);
    }
    timeSinceFed = 0;
    setMovedToEat(true);
    gridPtr[getPosX()][getPosY()] = '-';
    setPos(px, py);
    gridPtr[getPosX()][getPosY()] = getSymbol();
}

bool Doodlebug::checkStarve(){
    if (timeSinceFed >= 3){
        return true;
    }
    return false;
}

void Doodlebug::starve(){
    gridPtr[getPosX()][getPosY()] = '-';
    Doodlebug* temp = nullptr;
    vector<Doodlebug*> tempVec;
    for (int v = 0; v < doodVec.size(); v++){
        if((doodVec[v]->getPosX() == getPosX()) && (doodVec[v]->getPosY() == getPosY())){
            delete[] doodVec[v];
            temp = doodVec[v];
        }else{
            tempVec.push_back(doodVec[v]);
        }
    }
    doodVec.clear();
    for (int v = 0; v < tempVec.size(); v++){
        doodVec.push_back(tempVec[v]);
    }
}

void Doodlebug::move(){
    if (movedToEat){
        tryBreed();//skip past moving to breed
        return;
    }
    int random = rand() % 4;
    int px = getPosX();
    int py = getPosY();
    int testpos[2] = {px, py};
    if (random == 0){
        testpos[0]++;
    } else if (random == 1){
        testpos[0]--;
    } else if (random == 2){
        testpos[1]++;
    } else {
        testpos[1]--;
    }
    if (testgrid(testpos[0], testpos[1])){
        gridPtr[px][py] = '-';
        setPos(px, py);
        gridPtr[px][py] = getSymbol();
    }
    tryBreed();//After moving they try and reproduce.
}

void spawnDood(int posx, int posy);

void Doodlebug::breed(int px, int py){
    spawnDood(px, py);
    ageReset();
}

int main(){
    const int initAntNum = 100;
    const int initDoodNum = 5;

    cout<<"Press 'q' at any step to end the program.\n\n";

    //SET UP
    gridPtr = setUpGrid();

    srand((unsigned) time(NULL));
    int n = 0;
    while (n < initAntNum){
	    int random = rand() % gridSize;
        int random2 = rand() % gridSize;
        if (testgrid(random, random2)){
            spawnAnt(random, random2);
            n++;
        }
    }
    n = 0; //reset
    while (n < initDoodNum){
	    int random = rand() % gridSize;
        int random2 = rand() % gridSize;
        if (testgrid(random, random2)){
            spawnDood(random, random2);
            n++;
        }
    }
    print();
    cout<<endl;

    string input;
    //ask for input for time steps
    while(true){
        cout<<"Press Enter ";
        getline(cin, input);
        cout<<endl;

        if (input == "q") {
            break;
        }
        //Doodlebugs go first
        for (int x = 0; x < doodVec.size(); x++){
            doodVec[x]->step();
        }
        //Ants act second
        for (int o = 0; o < antVec.size(); o++){
            if (antVec[o]->getSymbol() == 'o'){
                antVec[o]->step();
            }
        }
        print();
        cout<<"\n";
    }
    cout << "Exiting program--\n";
    //delete all the Organism objects
    for (int j = 0; j < antVec.size(); j++){
        delete[] antVec[j];
    }
    for (int k = 0; k < doodVec.size(); k++){
        delete[] doodVec[k];
    }
    //delete arrays that make the grid on the heap
    for (int i = 0; i < gridSize; i++){
        delete[] gridPtr[i];
    }
    delete[] gridPtr;
    return 0;
}

char** setUpGrid(){
    char** grid = new char* [gridSize];
    for (int k = 0; k < gridSize; k++){
        grid[k] = new char[gridSize];
        for (int l = 0; l < gridSize; l++){
            grid[k][l] = '-';
        }
    }
    return grid;
}

bool testgrid(int posx, int posy){
    if (posx < 0 || posx >= gridSize){
        return false;
    }
    if (posy < 0 || posy >= gridSize){
        return false;
    }
    if (gridPtr[posx][posy] == '-'){
        return true;
    }
    return false;
}

void print(){
    for (int k = 0; k < gridSize; k++){
        for (int i = 0; i < gridSize; i++){
            cout<<gridPtr[k][i]<<" ";
        }
        cout<<endl;
    }
}

void spawnAnt(int posx, int posy){
    Ant* a = new Ant(posx, posy);
    Ant A = *a;
    gridPtr[A.getPosX()][A.getPosY()] = 'o';
    antVec.push_back(a);
}

void spawnDood(int posx, int posy){
    Doodlebug* d = new Doodlebug(posx, posy);
    Doodlebug D = *d;
    gridPtr[D.getPosX()][D.getPosY()] = 'X';
    doodVec.push_back(d);
}