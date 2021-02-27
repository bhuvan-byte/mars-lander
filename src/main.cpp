#pragma GCC optimize("O2")
#include <iostream>
#include "point.h"
#include "game.h"
using namespace std;
inline float random(float s=0.0,float e=1.0);
inline float random(float s /*=0.0*/,float e /*=1.0*/){
    return (rand()%10000)/10000.0 * (e-s) + s ;
}
inline int randInt(int s=0,int e=100){
    return rand()%(e-s) + s;
}

const int popSize=20;
const int geneSize=20;
struct Gene{
    float cost;
    vector<float> param;
    Gene(){
        for(int i=0;i<geneSize;i++) param.push_back(random(-1.0,1.0));
    }
    void randomise(float weight){
        for(int i=0;i<geneSize;i++){
            param[i] += weight*random(-1.0,1.0);
            param[i] = clamp(param[i],-1.0f,1.0f);
        }
    }
    void crossover(const vector<float>& par1, const vector<float>& par2){
        for(int i=0;i<geneSize;i++){
            float ratio= random(-0.2,0.8); // resulting gene closer to par1
            float pb= par1[i]*(1-ratio) + par2[i]*ratio;
            pb = clamp(pb,-1.0f,1.0f);
            param[i]= pb;
        }
    }
    void inherit(const vector<float>& better, float degree){
        for(int i=0;i<geneSize;i++){
            if(random()<0.95 ){
                param[i] = (1-degree)*better[i] + (degree)* random(-1.0,1.0);
            } else{
                param[i] = random(-1.0,1.0);
            }
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

        }
        const int s=popSize/10;
        float factorRand=clamp(population[0].cost/20000.0f,0.01f,0.08f);
        for(int i=s;i<6*s;i++){
            if(random()>0.9) continue;
            population[i].inherit(population[i%s].param, factorRand * i/(2*s));
        }
        for(int i=6*s ;i<popSize;i++){
            int l=randInt(0,6*s);
            int r=randInt(0,6*s);
            population[i].crossover(population[l].param,population[r].param);
        }
    }
};

int main()
{Timer t_;
    // Point2D<int> p1(10,20);
    // Point2D<float> p2;
    // loger(p2); p2=p1; loger(p2);
    
    srand(time(0));
    outCost_.open("data/outcost.txt");
    outPut_.open("data/output.txt");
    // debug_cost =debug_put= debug_cerr=0;
    outPut<<popSize<<"\n";
    Population population;
    const int Iterations = 101;
    rep(i,Iterations){
        if(i%1==0)     debug_cost =debug_put= debug_cerr=1;
        population.run();
        debug_cost =debug_put= debug_cerr=0;
    }

    cout<<"end";
    return 0;
}
