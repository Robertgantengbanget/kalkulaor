#include <bits/stdc++.h>
using namespace std;

string urldecode(const string &s) {
    string o; o.reserve(s.size());
    for (size_t i=0; i<s.size(); ++i) {
        if (s[i]=='+') o.push_back(' ');
        else if (s[i]=='%' && i+2<s.size()) {
            string h = s.substr(i+1,2);
            char c = (char)strtol(h.c_str(), nullptr, 16);
            o.push_back(c);
            i+=2;
        } else o.push_back(s[i]);
    }
    return o;
}

map<string,string> parseBody(const string &body) {
    map<string,string> m;
    stringstream ss(body);
    string pair;
    while(getline(ss,pair,'&')){
        size_t eq = pair.find('=');
        if (eq!=string::npos)
            m[urldecode(pair.substr(0,eq))] = urldecode(pair.substr(eq+1));
    }
    return m;
}

string toTable(double A[3][4]) {
    ostringstream o;
    o << "<table border=1 cellpadding=4 cellspacing=0>";
    for (int i=0;i<3;i++){
        o << "<tr>";
        for (int j=0;j<4;j++) o<<"<td>"<<setprecision(6)<<A[i][j]<<"</td>";
        o << "</tr>";
    }
    o << "</table>";
    return o.str();
}

int main(){
    cout << "Content-Type: text/html\n\n";
    int len = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
    string body(len,'\0');
    cin.read(&body[0], len);
    auto p = parseBody(body);

    double A[3][4];
    string names[3][4] = {{"a11","a12","a13","b1"},
                          {"a21","a22","a23","b2"},
                          {"a31","a32","a33","b3"}};
    for(int i=0;i<3;i++)
      for(int j=0;j<4;j++)
        A[i][j] = stod(p[names[i][j]]);

    cout << "<html><head><meta charset='utf-8'><title>Hasil Gauss</title></head><body style='font-family:Arial;background:#f7f9fc;padding:20px'>";
    cout << "<h2>Langkah-langkah Eliminasi Gauss</h2>";
    cout << "<h3>Matriks awal</h3>" << toTable(A);

    auto step=[&](string s){ cout << "<h4>"<<s<<"</h4>"<<toTable(A); };

    double pivot,factor;

    pivot=A[0][0]; for(int j=0;j<4;j++)A[0][j]/=pivot;
    for(int i=1;i<3;i++){ factor=A[i][0]; for(int j=0;j<4;j++)A[i][j]-=factor*A[0][j]; }
    step("Setelah eliminasi a21,a31 (pivot a11)");

    pivot=A[1][1]; for(int j=0;j<4;j++)A[1][j]/=pivot;
    factor=A[0][1]; for(int j=0;j<4;j++)A[0][j]-=factor*A[1][j];
    factor=A[2][1]; for(int j=0;j<4;j++)A[2][j]-=factor*A[1][j];
    step("Setelah eliminasi a12,a32 (pivot a22)");

    pivot=A[2][2]; for(int j=0;j<4;j++)A[2][j]/=pivot;
    factor=A[0][2]; for(int j=0;j<4;j++)A[0][j]-=factor*A[2][j];
    factor=A[1][2]; for(int j=0;j<4;j++)A[1][j]-=factor*A[2][j];
    step("Setelah eliminasi a13,a23 (pivot a33)");

    cout << "<h3>Hasil akhir</h3>"<<toTable(A);
    cout << "<h3>Solusi:</h3>"
         << "<p>x1 = "<<A[0][3]<<", x2 = "<<A[1][3]<<", x3 = "<<A[2][3]<<"</p>";
    cout << "<p><a href='../index.html'>← Kembali</a></p></body></html>";
}
