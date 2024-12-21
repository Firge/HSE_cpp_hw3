#include "generate.cpp"
#include <string>
#include <stdio.h>
#include <iostream>
#include <cstring>

struct Triplet_int {
    int a, b, c;
};

struct Triplet_str {
    string a, b, c;
    Triplet_int triplet_int;
    string route = "";
};

void prepare(Triplet_str& val, string& s) {
    if (s[s.size()-1] == ',') {
        s.resize(s.size()-1);
    }
    if (s.compare(0, 9, "--p-type=") == 0) {
        val.a = s.substr(9, s.size() - 9);
        val.triplet_int.a = 1;
    };
    if (s.compare(0, 9, "--v-type=") == 0) {
        val.b = s.substr(9, s.size() - 9);
        val.triplet_int.b = 1;
    };
    if (s.compare(0, 14, "--v-flow-type=") == 0) {
        val.c = s.substr(14, s.size() - 14);
        val.triplet_int.c = 1;
    };
    if (s.compare(0, 8, "--route=") == 0) {
        val.route = s.substr(9, s.size() - 9);
    }
}

pair<string, string> TakeName(vector<string>& data) {
    Triplet_str triplet;
    for (int i = 0; i < data.size(); ++i) {
        prepare(triplet, data[i]);
    }
    if (!(triplet.triplet_int.a == 1 && triplet.triplet_int.b == 1 && triplet.triplet_int.c == 1)) {
        throw std::invalid_argument("Triplet is not a valid triplet");
    }
    if (triplet.a[triplet.a.size() - 1] == ')') {
        triplet.a.resize(triplet.a.size() - 1);
    }
    if (triplet.b[triplet.b.size() - 1] == ')') {
        triplet.b.resize(triplet.b.size() - 1);
    }
    if (triplet.c[triplet.c.size() - 1] == ')') {
        triplet.c.resize(triplet.c.size() - 1);
    }
    string s1 = triplet.a + "_" + triplet.b + "_" + triplet.c;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] == '(' || s1[i] == ')' || s1[i] == ',') {
            s1[i] = '_';
        }
    }
    string s2 = triplet.route;
    return make_pair(s1, s2);
}


int main(int argc, char* argv[]) {
    cout << argc << endl;
    std::vector<string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    for (auto it = args.begin(); it != args.end(); it++) {
        cout << *it << endl;
    }
    FluidFactory ff = Generate();
    string s1, s2;
    pair<string,string> p = TakeName(args);
    s1 = p.first;
    s2 = p.second;
    if (s2 == "") {
        int N = 36;
        int M = 84;
        s1 = "f_" + to_string(N) + "_" + to_string(M) + "_" + s1;
    }
    else {

    }
    std::unique_ptr<FluidBase> t = ff.create(s1);
    t->fluid();
}