#include <iostream>
#include "game.h"
using namespace std;
inline float random(float s=0.0,float e=1.0);
inline float random(float s /*=0.0*/,float e /*=1.0*/){
    return (rand()%10000)/10000.0 * (e-s) + s ;
}
const int popSize=100;
const int geneSize=16;


int main()
{
    // Point2D<int> p1(10,20);
    // Point2D<float> p2;
    // loger(p2); p2=p1; loger(p2);
    
    srand(time(0));
    Game game;
    game.takeInput();

    vector<float> param;
    rep(i,16) param.push_back(random(-1,1));
    cerr<<param;
    game.getCost(param);
    cout<<"end";
    return 0;
}
