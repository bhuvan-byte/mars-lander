#pragma once

#include <bits/stdc++.h>
#include <fstream>
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define fore(i,a,b) for(i=(a);i<=(int)(b);i++)
#define ford(i,a,b) for(i=(a);i>=(int)(b);i--)
std::ofstream outCost_,outPut_; 

bool debug_cerr=1, debug_put=1, debug_cost=1;
#define outPut if(!debug_put) {} else outPut_
#define outCost if(!debug_cost) {} else outCost_
#define Cerr if(!debug_cerr) {} else cerr   
#define loger(...) Cerr << '>' << #__VA_ARGS__ << ": "; dbg_out(__VA_ARGS__);
using namespace std;
void dbg_out() { Cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { Cerr<<H<<", "; dbg_out(T...); }
template<class A,class B> ostream& operator<<(ostream &os,const pair<A, B> &p){return os<<'('<<p.first<<", "<<p.second<<')';}
template <typename T> ostream& operator<<(ostream& stream,const vector<T>& obj){
    stream<<"[";for(auto x:obj)stream<<x<<", ";stream<<"]"<<((obj.size()>3)?"\n":""); return stream; }
template <typename T,size_t N> ostream& operator<<(ostream& stream,const array<T,N>& obj){
    stream<<"[";for(auto x:obj)stream<<x<<", ";stream<<"]"<<((N>3)?"\n":"");return stream;}
template <typename T> void printarr(T arr[],int n){Cerr<<"Array ";for(int i=0;i<n;i++){Cerr<<arr[i]<<" ";}Cerr<<endl;}
template <typename T> void printarr(T arr){Cerr<<">>";for(auto it=arr.begin();it!=arr.end();it++){Cerr<<*it<<" ";}Cerr<<endl;}
typedef long long ll;typedef unsigned long long ull;
const ll mod=1000000007;

const double PI = 3.1415926535;
const double EPS = (1e-9);
template <typename T>
struct Point2D {
    T x, y;
    Point2D() :x(0), y(0) {}
    Point2D(T x, T y) :x(x), y(y) {}
    Point2D operator+(const Point2D& ot) const{ return Point2D(x + ot.x, y + ot.y); }
    Point2D operator-(const Point2D& ot) const { return Point2D(x - ot.x, y - ot.y); }
    Point2D operator*(const float& f) const { return Point2D(x * f, y * f); }
    Point2D& operator+=(const Point2D& ot) { x += ot.x; y += ot.y; return *this; }
    Point2D& operator-=(const Point2D& ot) { x -= ot.x; y -= ot.y; return *this; }
    float dot(const Point2D& ot) const{ return x*ot.x+y*ot.y; }
    inline float abs() const{ return sqrt(x * x + y * y); }
    inline T abs2() const{ return x*x + y*y ;}
    int angle() {
        int ang = (180 / PI) * atan(y / (x + EPS * (x == 0)));
        if (x < 0) ang += 180;
        ang = (ang + 360) % 360;
        return ang;
    }
    inline int relPosition(const Point2D& A,const Point2D& B) const{
        int num=((B.x-A.x)*(y-A.y) - (B.y-A.y)*(x-A.x)) ;
        return (num>0) - (num<0);
    }
    inline float perpDistance(const Point2D& p1,const Point2D& p2) const{
        const Point2D& POS = *this;
        const Point2D line = p2-p1;
        const float length2 = line.abs2();
        const float t =  max(0.0f,min(1.0f,line.dot(POS-p1)/length2 )) ;
        const Point2D foot = p1 + line*t;
        return (foot-POS).abs();
    }


    friend std::ostream& operator<<(std::ostream& stream, Point2D& out) {
        stream << out.x << " " << out.y;
        return stream;
    }
    friend std::istream& operator>>(std::istream& stream, Point2D& inp) {
        stream >> inp.x >> inp.y;
        return stream;
    }
    template <typename OTH>
    Point2D<T>& operator=(const Point2D<OTH>& oth){
        x=oth.x;
        y=oth.y;
        return *this;
    }
};
