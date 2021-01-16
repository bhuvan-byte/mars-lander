#include <iostream>
#include "point.h"
#include "game.h"
using namespace std;
inline float random(float s=0.0,float e=1.0);
inline float random(float s /*=0.0*/,float e /*=1.0*/){
    return (rand()%10000)/10000.0 * (e-s) + s ;
}

const int popSize=100;
const int geneSize=16;
struct Gene{
    float cost;
    vector<float> param;
    Gene(){
        for(int i=0;i<geneSize;i++) param.push_back(random(-1.0,1.0));
    }
    void randomise(float weight){
        for(int i=0;i<geneSize;i++){
            param[i] += weight*random(-1.0,1.0);
            param[i] = max(-1.0f,min(1.0f,param[i]));
        }
    }
    bool operator<(const Gene& oth){ return cost<oth.cost;}
};
Game game;
struct Population{
    vector<Gene> population;
    Population(){
        game.takeInput();
        population.resize(popSize);
    }
    void run(){
        for(int i=0;i<popSize;i++){
            population[i].cost=game.getCost(population[i].param);
        }
        sort(population.begin(),population.end());
        for(int i=0;i<popSize;i++){
            outCost<<population[i].cost<<" \n"[i==popSize-1];
            
            population[i].randomise(random(0,i/(float)popSize));
        }
    }
};

int main()
{
    // Point2D<int> p1(10,20);
    // Point2D<float> p2;
    // loger(p2); p2=p1; loger(p2);

    srand(time(0));
    outCost_.open("outcost.txt");
    outPut_.open("output.txt");
    debug_put= debug_cerr=1;
    Population population;
    rep(i,100){
        if(i%10==0) debug_cost=1;
        population.run();
        debug_cost=0;
    }

    cout<<"end";
    return 0;
}
