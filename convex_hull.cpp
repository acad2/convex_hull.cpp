#include <bits/stdc++.h>
using namespace std;

bool hasOnly1ele(vector< pair<float,float> >);
bool myComparison(const pair<float,float> , const pair<float,float> );
float distance(pair<float,float>, pair<float,float>);
bool is_in_left(pair<float,float>, pair<float,float>, pair<float,float>);
vector< pair<int, float> > track_points(vector< pair<float,float> >);
pair<float,float> secondToTop(vector< pair<float,float> >);
pair<float,float> initial_point(vector< pair<float,float> >);

pair<float,float> init_p;
vector< pair<float,float> >convex_hull;

int main(){
  vector< pair<float,float> >points;
  int n;
  float x, y;

  cout<<"Enter the number of points: "; cin>>n;
  cout<<endl;

  for(int i=0; i<n; i++){
    cin>>x>>y;
    points.push_back(make_pair(x,y));
  }
  cout<<"All the points have been stored.\nThe points are: "<<endl;
  for(int i=0; i<n; i++){
    cout<<"("<<points[i].first<<","<<points[i].second<<")"<<endl;
  }
  cout<<"computing convex hull..."<<endl;

  init_p = initial_point(points);
  convex_hull.push_back(init_p);
  cout<<"Initial point chosen is: ("<<init_p.first<<","<<init_p.second<<")"<<endl;

  //vector< pair<int, float> >trackedPoints;
  //cout<<"points are bieng marked with their angles wrt x axis.."<<endl;
  //trackedPoints = track_points(points);
  //for(int i=0; i<n; i++){
  //  cout<<"("<<trackedPoints[i].first<<"->"<<trackedPoints[i].second<<")"<<endl;
  //}

  cout<<"Sorting according to the angle with x axis..."<<endl;
  sort(points.begin(),points.end(), myComparison);
  for(int i=0; i<n; i++){
    cout<<"("<<points[i].first<<","<<points[i].second<<")"<<endl;
  }

  pair<float,float> topstack;
  pair<float,float> secondtop;
  cout<<"finding convex hull..."<<endl;
  for(auto itr = points.begin(); itr != points.end(); itr++){
    pair<float,float> p = *itr;
    if(p == init_p){
      cout<<"end of scan!!"<<endl;
    }
    else{
      topstack = convex_hull.back();
      if(!hasOnly1ele(convex_hull)){
        secondtop = secondToTop(convex_hull);

        while(!is_in_left(p,topstack,secondtop)){
          convex_hull.pop_back();
          topstack = convex_hull.back();
          if(!hasOnly1ele(convex_hull)){
            secondtop = secondToTop(convex_hull);
          }
          else{
            break;
          }
        }
        convex_hull.push_back(p);
      }
      else{
        convex_hull.push_back(p);
      }
    }
  }

  cout<<"The convex hull is"<<endl;
  for(auto itr = convex_hull.begin(); itr != convex_hull.end(); itr++){
    cout<<"("<<itr->first<<","<<itr->second<<")"<<endl;
  }
}

bool myComparison(const pair<float,float> lhs, const pair<float,float> rhs){
  float l_dist = distance(lhs,init_p);
  float l_x;
  if(l_dist ==0){
    l_x = 0;
  }
  else{
    l_x = lhs.first/l_dist;
  }

  float r_dist = distance(rhs,init_p);
  float r_x;
  if(r_dist ==0){
    r_x = 0;
  }
  else{
    r_x = rhs.first/r_dist;
  }

  return l_x > r_x;
}

pair<float,float> initial_point(vector< pair<float,float> >points){
  int n = points.size();
  int init = 0;
  for(int i=0; i<n; i++){
    if(points[i].second < points[init].second){
      init = i;
    }
    else if(points[i].second == points[init].second){
      if(points[i].first < points[init].first){
        init = i;
      }
    }
  }
  return points[init];
}

float distance(pair<float,float> p1, pair<float,float> p2){
  float xsq = (p1.first - p2.first)*(p1.first - p2.first);
  float ysq = (p1.second - p2.second)*(p1.second - p2.second);

  return sqrt(xsq+ysq);
}

vector< pair<int, float> > track_points(vector< pair<float,float> >points){
  vector< pair<int, float> >trackedPoints;
  int n = points.size();

  for(int i=0; i<n; i++){
    pair<float, float> p = points[i];
    float lenp = distance(p, init_p);
    trackedPoints.push_back(make_pair(i,(p.first)/lenp));
  }
  return trackedPoints;
}

pair<float,float> secondToTop(vector< pair<float,float> >s){
  pair<float,float> h1 = s.back();
  pair<float,float> h2;
  s.pop_back();
  h2 = s.back();
  s.push_back(h1);
  return h2;
}

bool hasOnly1ele(vector< pair<float,float> > s){
  bool  res = false;
  pair<float,float> temp;
  temp = s.back();
  s.pop_back();
  if(s.empty()){
    res = true;
  }
  s.push_back(temp);
  return res;
}

bool is_in_left(pair<float,float>f, pair<float,float>m, pair<float,float>l){
  float fx = f.first, fy = f.second;
  float mx = m.first, my = m.second;
  float lx = l.first, ly = l.second;

  float z = ((mx-lx)*(fy-my) - (fx-mx)*(my-ly));

  if(z >= 0){
    return true;
  }
  else{
    return false;
  }
}
