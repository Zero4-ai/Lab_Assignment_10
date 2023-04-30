#include<bits/stdc++.h>

using namespace std;

class Solution{
    int itr = 0;
    vector<float> randoms;
    double epsilon = 0.000005;
    double delta = INFINITY, GAMMA = 1, NOISE = 0.1;
    map<pair<int,int>,double> V;
    vector<pair<int,int>> S = {{0,0}, {0,1}, {0,2}, {0,3},
                           {1,0}, {1,2},
                           {2,0}, {2,1}, {2,2},
    };
    vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void make_randomNumbers() {
        srand(time(0));
        srand( (unsigned)time(NULL));
        for(int i = 0; i < 10000; i++) 
            randoms.push_back((float)rand()/RAND_MAX), randoms.back();

    }

    int opposite(int i) {
        if(!i)
            return 0;
        if(i == 1)
            return -1;
        return 1;
    }


    pair<pair<int, int>, pair<int, int>> nextState(pair<int, int>& pr) {
        int d = itr % 4;
        if(randoms[itr] > 0.8 && randoms[itr] <= 0.9) {
            return {{pr.first + opposite(dir[d].second), pr.second + opposite(dir[d].first)}, {opposite(dir[d].second), opposite(dir[d].first)}};
        }
        else if(randoms[itr++] > 0.9) {
            return {{pr.first + dir[d].second, pr.second + dir[d].first}, {dir[d].second, dir[d].first}};
        }
        return {{pr.first + dir[d].first, pr.second + dir[d].second}, {dir[d].first, dir[d].second}};
    }

public:
    void setup() {
        make_randomNumbers();
        for(auto it: S) {
            V[it] = 0;
        }
        V[{2, 3}] = 1, V[{1, 3}] = -1;
        traverse();
    }    

    void traverse() {
        int iter = 0;
        while (delta > epsilon) {
            delta = 0;
            double res = 0, num = 0, temp;
            for (auto it: S) {
                temp = V[it];
                pair<pair<int, int>, pair<int, int>> d = nextState(it);
                if(d.first.first == 1 && d.first.second == 1)
                {
                    num = 0 + (GAMMA * ((1-NOISE)* V[d.first] + (NOISE * V[d.second])));
                    temp = max(temp, num);
                }
                else if(d.first.first == 1 && d.first.second == 3)
                {
                    num = -1 + (GAMMA * ((1-NOISE)* V[d.first] + (NOISE * V[d.second])));
                    temp = max(temp, num);
                }
                else if(d.first.first == 2 && d.first.second == 3)
                {
                    num = 1 + (GAMMA * ((1-NOISE)* V[d.first] + (NOISE * V[d.second])));
                    temp = max(temp, num);
                }
                else if(d.first.first >= 0 && d.first.first < 3 && d.first.second >= 0 && d.first.second < 4) {
                    num = 0.1 + (GAMMA * ((1-NOISE)* V[d.first] + (NOISE * V[d.second])));
                    temp = max(temp, num);
                    
                }
                double old_v = V[it];
                V[it] = temp;
                delta = max(delta, abs(old_v - V[it]));
            }
            
            iter++;
        }
        cout << "\nFinal answer: \n\n" << "number of iterations: " << iter << endl;
        for(auto it: V) {
            cout << it.first.first << " and "  << it.first.second << ": " << it.second << " ";
            cout << endl;
        }
    }
};

int main() {
    Solution s;
    s.setup();
    return 0;
}
