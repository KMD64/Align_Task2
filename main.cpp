#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

struct vector2f{
    float x;
    float y;
    float sqlength() const {
        return x*x+y*y;
    }
    float length() const{
        return sqrt(sqlength());
    }
    vector2f to_polar(){
        return {atan2f(y,x),length()};
    }
};
//Перегрузка оператора вывода потока для vector2f
ostream &operator<<(ostream &out,const vector2f &vect){
    out<<vect.x<<" "<<vect.y;
    return out;
}

int main()
{
    uint32_t n;
    cin>>n;
    vector<vector2f> points(n);
    //Заполнение массива точек
    std::mt19937 rand_gen(time(nullptr));

    for(uint32_t i=0;i<n;++i){
        points[i].x = (rand_gen())%199-100;
        points[i].y = (rand_gen())%199-100;
    }

    const float rad = 80;
    const float dist = 10;
    //Фильтрация точек (длина Е (rad-dist,rad+dist))
    vector<vector2f> filtered;
    std::copy_if(points.begin(),points.end(),back_inserter(filtered),[rad,dist](vector2f &pt){
        //abs(pt.length()-rad)<dist;
        return pt.sqlength()>pow(rad-dist,2)&&pt.sqlength()<pow(rad+dist,2);
    });

    //Сортировка по значению угла в полярных координатах (против часовой стрелки)
    std::sort(filtered.begin(),filtered.end(),[](vector2f &pt1,vector2f &pt2){
        return atan2f(pt1.y,pt1.x)<atan2f(pt2.y,pt2.x);
    });

    for(auto &pt:filtered){
        cout<<pt<<endl;
        //Для наглядности произведен перевод в полярные координаты
        //clog<<"#"<<pt<<":"<<pt.to_polar()<<endl;
    }

    return 0;
}
