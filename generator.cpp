#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;


#ifndef TYPES
//#define TYPES "FLOAT,FIXED(32,5),DOUBLE"
#endif

#ifndef SIZES
//#define SIZES "S(1920,1080),S(10,10),S(42,1337)"
#endif

struct Triplet {
    string name;
    int N;
    int M;
};

 vector<Triplet> ParseTypes(const string &s) {
    vector<Triplet> result;
    int i = 0;
    while (i < s.size()) {
        Triplet t;
        while (i < s.size() && s[i] == ' ') {
            i++;
        }
        int j = i;
        while (j < s.size() && (s[j] != ',' || s[j] == ',' && (s[j - 1] >= '0' && s[j - 1] <= '9'))) {
            j++;
        }
        t.name = s.substr(i, j - i);
        if (t.name == "DOUBLE" || t.name == "FLOAT") {
            t.N = 0;
            t.M = 0;
        }
        string qq = t.name.substr(0, 10);
        string qqq = t.name.substr(0, 5);
        if (qq == "FAST_FIXED") {
            int ii = 10;
            while (t.name[ii] != ',') {
                ii++;
            }
            t.N = stoi(t.name.substr(11, ii));
            t.M = stoi(t.name.substr(ii+1, t.name.length()));
            t.name = "FAST_FIXED";
        }
        else if (qqq == "FIXED") {
            int ii = 5;
            while (t.name[ii] != ',') {
                ii++;
            }
            t.N = stoi(t.name.substr(6, ii));
            t.M = stoi(t.name.substr(ii+1, t.name.length()));
            t.name = "FIXED";
        }
        result.emplace_back(t);
        i = j + 1;
    }
    return result;
}

struct Duplet {
    int N;
    int M;
};

 vector<Duplet> ParseSizes(const string &s) {
    vector<Duplet> result;
    int i = 0;
    while (i < s.size()) {
        while (i < s.size() && s[i] == ' ') {
            i++;
        }
        Duplet t;
        int j = i;
        while (j < s.size() && (s[j] != ',' || s[j] == ',' && (s[j - 1] >= '0' && s[j - 1] <= '9'))) {
            j++;
        }
        {
            int ii = i;
            while (s[ii] != ',') {
                ii++;
            }
            t.N = stoi(s.substr(i + 2, ii - i));
            t.M = stoi(s.substr(ii+1, j - ii + 1));
        }
        result.emplace_back(t);
        i = j + 1;
    }
    return result;
}

void add(string& s, string &ss, Triplet &t) {
    if (t.name == "DOUBLE") {
        s += "double";
        ss += "double";
    }
    if (t.name == "FLOAT") {
        s += "float";
        ss += "float";
    }
    if (t.name == "FAST_FIXED") {
        s += "FastFixed<";
        ss += "FastFixed_";
        s += to_string(t.N);
        ss += to_string(t.N);
        s+= ",";
        ss+= "_";
        s += to_string(t.M);
        ss += to_string(t.M);
        s += ">";
    }
    if (t.name == "FIXED") {
        s += "Fixed<";
        ss += "Fixed_";
        s += to_string(t.N);
        ss += to_string(t.N);
        s+= ",";
        ss+= "_";
        s += to_string(t.M);
        ss += to_string(t.M);
        s += ">";
    }
}

int main() {
    vector<Duplet> duplets = ParseSizes(SIZES);
    vector<Triplet> triplets = ParseTypes(TYPES);
     if (duplets.size() == 0) {
         duplets.push_back({36, 84});
     }

    ofstream out;          // поток для записи
    out.open("../generate.cpp");

    string s = R"(
#include "fluid.cpp"
#include <vector>
#include <string>
using namespace std;
string s = "";

FluidFactory Generate() {
    FluidFactory ff = FluidFactory();

)";
    out << s;
    string ss;
    int num = 0;
for (int i = 0; i < triplets.size(); i++) {
    for(int j = 0; j < triplets.size(); j++) {
        for(int k = 0; k < triplets.size(); k++) {
            for (int m = 0; m < duplets.size(); m++) {
                s = "ff.registerType<";
                s+= to_string(duplets[m].N);
                s+= ",";
                s+= to_string(duplets[m].M);
                s+= ",";
                ss = "f_";
                ss+= to_string(duplets[m].N);
                ss+= "_";
                ss+= to_string(duplets[m].M);
                ss+= "_";
                add(s, ss, triplets[i]);
                s += ",";
                ss += "_";
                add(s, ss, triplets[j]);
                s += ",";
                ss += "_";
                add(s, ss, triplets[k]);
                s += ">";
                s += "(\"" + ss + "\")"+ ";";
                s += "\n";
                out << s;
                num++;
            }
        }
    }
}



    s = R"(
return ff;
}
)";
    out << s;
    out.close();
    return 0;
}
