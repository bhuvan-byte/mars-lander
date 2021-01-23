#pragma once
#include "point.h"
#include<bits/stdc++.h>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>


const int Width=7000;
const int Height=3000;
const int FourierN=5;
class Land{
public:
    int surfaceN;
    int landIndex;
    vector<Point2D<int>> points;
    vector<Point2D<int>> lineCoeff;
    vector<int> lengths,roadDistances;
    void takeInput(){
        freopen("input.txt","r",stdin);
        landIndex = -1;
        cin >> surfaceN;
        points = {Point2D<int>(2*Width,2*Height),Point2D<int>(-Width,2*Height),Point2D<int>(-Width,0)};
        Point2D<int> curr,prev(-1,-1);
        for (int i = 0; i < surfaceN; i++) {
            cin>>curr;
            if(curr.y==prev.y && abs(curr.x-prev.x)>=1000){
                landIndex= points.size();
                points.push_back(Point2D<int>((curr.x+prev.x)/2,curr.y));
            }
            points.push_back(curr);
            prev=curr;
        }
        points.insert(points.end(),{Point2D<int>(2*Width,0),Point2D<int>(2*Width,2*Height)});
        surfaceN+=6;
        outPut<<"Land:"<<points;
        calcLengths(); // automatically called when taking input
    }
    void calcLengths(){
        for(int i=0;i<surfaceN-1;i++){
            int dist = (points[i+1]-points[i]).abs();
            lengths.push_back(dist);
            // storing coeffcients in (x2-x1)(y-y1)-(y2-y1)(x-x1) : no longer done
        }
        roadDistances=vector<int> (surfaceN,0);
        // loger(landIndex,points[landIndex]);
        for(int i=landIndex+1; i<surfaceN; i++){
            roadDistances[i]=roadDistances[i-1]+lengths[i-1];
        }
        for(int i=landIndex-1; i>=0 ; i--){
            roadDistances[i]=roadDistances[i+1]+lengths[i];
        }
        // loger(roadDistances);
    }
    bool isInside(const Point2D<int>& pos){
        Point2D<int> out(3*Width,3*Height);
        bool ans=false;
        for(int i=0; i<surfaceN -1 ;i++){
            int num1 = pos.relPosition( points[i],points[i+1] );
            int num2 = out.relPosition( points[i],points[i+1] );
            int num3 = points[i].relPosition( pos,out);
            int num4 = points[i+1].relPosition(pos,out);
            int b1 = num1*num2;
            int b2 = num3*num4;
            // if any of b1 or b2 is +ve  no intersection
            // in case of any {-1,0} isInside=true for safe side
            if(b1>0 || b2>0) {}
            else if(b1<0 && b2<0) ans=!ans;
            else { loger("returned inInside true: uncertain",pos,points[i],points[i+1]); return true;}
        }
        return ans;
    }
    int minDistance(const Point2D<int>& pos){
        int mndist=INT_MAX;
        int ind=-1;
        for(int i=0;i<surfaceN-1;i++){
            int dist= pos.perpDistance(points[i],points[i+1]);
            if(dist<mndist){
                mndist=dist;
                ind=i;
            }
        }
        assert(ind>=0);
        if(roadDistances[ind+1] < roadDistances[ind]) ind++;
        int dist_point= (pos-points[ind]).abs();
        // loger(pos,ind,dist_point,roadDistances[ind]);
        return dist_point + roadDistances[ind];
    }
};
class Ship{
public:
    Point2D<int> pos,vel;
    int fuel,rotate,power;
    void takeInput(){
        cin>>pos>>vel>>fuel>>rotate>>power;
    }

};

class Game{
public:
    Ship readLive;
    Ship curr;
    Land land;
    array<vector<float>,FourierN> preSin;
    array<vector<float>,FourierN> preCos;
    vector<int> arrPower,arrRotate;
    vector<Point2D<float>> arrVel;
    vector<Point2D<int>> arrPosition;
    int Num;
    int crashIndex=-1;
    int finFuel=-1;

    void takeInput(){
        land.takeInput();
        readLive.takeInput();
        Num = readLive.fuel/3 +1;
        arrPower.resize(Num+1);
        arrRotate.resize(Num+1);
        arrPosition.resize(Num+1);
        arrVel.resize(Num+1);
        arrPower[0]=readLive.power;
        arrRotate[0]=readLive.rotate;
        arrPosition[0]=readLive.pos;
        arrVel[0]=readLive.vel;
        for(int j=0;j<FourierN;j++){
            for(int i=0; i<Num; i++){
                preSin[j].push_back( sin((j+1)*i*2*PI/Num));
                preCos[j].push_back( cos((j+1)*i*2*PI/Num));
            }
        }
    }
    void simulate(const vector<float>& param){
        //param length should be 16; 0-7 for sin; 8-15 for cos 
        int len=param.size()/2;
        vector<float> sinParam(param.begin(),param.begin()+len);
        vector<float> cosParam(param.begin()+len,param.end());
        vector<float> tempRotate(Num),tempPower(Num);
        
        for(int j=0;j<FourierN;j++){
            for(int i=0;i<Num;i++){
                tempRotate[i]+=preSin[j][i]*sinParam[j];
                tempRotate[i]+=preCos[j][i]*cosParam[j];
                tempPower[i]+=preSin[j][i]*sinParam[j+len-FourierN];
                tempPower[i]+=preCos[j][i]*cosParam[j+len-FourierN];
            }
        }
        
        for(int i=0;i<Num;i++){
            int orotate = max(-90, min(90, (int) (tempRotate[i]*90*0.5)) );
            int opower = max(0, min(4, (int) (tempPower[i]*2 + 4))) ;
            
            // opower=2+i%3;   //testing correctness of simulation
            // orotate=-90 + (i*10)%150; // simple test case

            arrRotate[i+1] = arrRotate[i] + max(-15,min(15, orotate - arrRotate[i]));
            arrPower[i+1] = arrPower[i] + max(-1,min(opower - arrPower[i], 1 ));
        }

        Point2D<float> tempPos; tempPos = arrPosition[0];
        for(int i=0;i<Num;i++){
            arrVel[i+1].x=arrVel[i].x - arrPower[i+1]*sin(arrRotate[i]*PI/180);
            arrVel[i+1].y=arrVel[i].y - 3.711 + arrPower[i+1]*cos(arrRotate[i]*PI/180);
            tempPos += arrVel[i+1];
            arrPosition[i+1] = tempPos;
        }
        // freopen("output.txt","w",stderr);
        
        crashIndex=Num;
        vector<bool> crash;
        for(int i=0;i<Num;i++){
            bool b=land.isInside(arrPosition[i]);
            crash.push_back(b);
            if(b==false && crashIndex==Num) crashIndex=i;
        }
        outPut<<arrRotate<<arrPower;
        outPut<<arrVel;
        outPut<<arrPosition;
        outPut<<crashIndex<<" ";
        // loger(crash);
        // loger(crashIndex,arrPosition[crashIndex],arrVel[crashIndex]);
        
        //fuel left
        finFuel = readLive.fuel;
        for(int i=0;i<crashIndex;i++) finFuel-=arrPower[i]; 

    }
    float getCost(const vector<float>& param){
        // it should calculate & return float for derivability purposes
        simulate(param);
        auto finVel=arrVel[crashIndex];
        auto finPos=arrPosition[crashIndex];
        int mndist=land.minDistance(finPos);
        float vx = abs(finVel.x) , vy = abs(finVel.y);
        float velCost = (vx>10 ? 10*vx : vx) + (vy>35 ? 10*vy : vy); 
        // mndist is actually not accurate
        int distCost = mndist>300 ? 4*mndist : mndist/2; // top priority
        int fuelCost = (finFuel < 50 ? 30 : 0) - finFuel/2; 
        float cost = distCost + velCost + fuelCost;
        // loger(finVel,finPos,mndist);
        // loger(cost,distCost,velCost,fuelCost);
        outPut<<cost<<"\n";
        return cost;
    }
};




//        // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
//        cout << "-20 3" << endl;
//    }

