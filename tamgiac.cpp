#include <iostream>
#include <cmath>

using namespace std;

struct diem{
    double x;
    double y;
};
typedef struct diem diem; 
double kcach (diem a, diem b){
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

//chu vi
double chuvi (diem a, diem b, diem c){
    return kcach(a,b) + kcach(b,c) + kcach(c,a);
}

//dien tich
double dientich (diem a, diem b, diem c){
    double ab = kcach(a,b);
    double bc = kcach(b,c);
    double ca = kcach(c,a);
    double p = (ab + bc + ca) / 2;
    return sqrt(p*(p-ab)*(p-bc)*(p-ca));
}

// toạ độ trọng tâm
diem trongtam (diem a, diem b, diem c){
    diem g;
    g.x = (a.x + b.x + c.x) / 3;
    g.y = (a.y + b.y + c.y) / 3;
    return g;
}

// điểm có hoành độ lớn nhất
diem max_x(diem a, diem b, diem c){
    if (a.x > b.x) {
        if (a.x > c.x) return a;
        else return c;
    }
    else if (c.x > b.x) return c;
    else return b;
}

// điểm có tung độ nhỏ nhất
diem min_y (diem a, diem b, diem c){
    if (a.y < b.y) {
        if (a.y < c.y) return a;
        else return c;
    }
    else if (c.y < b.y) return c;
    else return b;
}

// khoảng cách tổng từ P(x,y) tới 3 đỉnh
double khoangcachP (diem a, diem b, diem c, diem p){
    return kcach(a,p) + kcach(b,p) + kcach(c,p);
}

// kiểm tra điểm nằm trong hay ngoài tam giác
void kiemtradiem(diem a, diem b, diem c, diem m){
    double s_abc = dientich(a, b, c);
    double s_abm = dientich(a, b, m);
    double s_acm = dientich(a, c, m);
    double s_bcm = dientich(b, c, m);
    
    if (abs(s_abc - (s_abm + s_acm + s_bcm)) <= 1e-9) 
        cout << "Điểm nằm trong tam giác";
    else 
        cout << "Điểm không nằm trong tam giác";
}


// Dạng của tam giác
void dangtamgiac (diem a, diem b, diem c){
    double ab = kcach(a, b);
    double bc = kcach(b, c);
    double ca = kcach(c, a);
    double a2 = ab * ab;
    double b2 = bc * bc;
    double c2 = ca * ca;
    if (ab == bc && bc == ca) {
        cout << "Tam giác đều" << endl;
    }
    else if (ab == bc || bc == ca || ca == ab) {
        if (a2 == b2 + c2 || b2 == a2 + c2 || c2 == a2 + b2) {
            cout << "Tam giác vuông cân" << endl;
        }
        else cout << "Tam giác cân" << endl;
    }
    else if (a2 == b2 + c2 || b2 == a2 + c2 || c2 == a2 + b2) {
        cout << "Tam giác vuông" << endl;
    }
    else cout << "Tam giác thường" << endl;
}

// Kiểm tra tam giác
void kiemtratamgiac (diem a, diem b, diem c){
    double ab = kcach(a, b);
    double bc = kcach(b, c);
    double ca = kcach(c, a);
    if (ab + bc > ca && bc + ca > ab && ca + ab > bc)
        cout << "Là tam giác" << endl;
    else cout << "Không là tam giác" << endl;
}

int main() {
    diem a, b, c;
    cout << "Nhập tọa độ điểm A: ";
    cin >> a.x >> a.y;
    cout << "Nhập tọa độ điểm B: ";
    cin >> b.x >> b.y;
    cout << "Nhập tọa độ điểm C: ";
    cin >> c.x >> c.y;

    kiemtratamgiac(a, b, c);
    dangtamgiac(a, b, c);

    diem g = trongtam(a, b, c);
    cout << "Tọa độ điểm trọng tâm: (" << g.x << ", " << g.y << ")" << endl;

    diem max_x_point = max_x(a, b, c);
    cout << "Điểm có hoành độ lớn nhất: (" << max_x_point.x << ", " << max_x_point.y << ")" << endl;

    diem min_y_point = min_y(a, b, c);
    cout << "Điểm có tung độ nhỏ nhất: (" << min_y_point.x << ", " << min_y_point.y << ")" << endl;

    double chu_vi = chuvi(a, b, c);
    cout << "Chu vi tam giác: " << chu_vi << endl;

    double dien_tich = dientich(a, b, c);
    cout << "Diện tích tam giác: " << dien_tich << endl;

    diem m;
    cout << "Nhập tọa độ điểm M: ";
    cin >> m.x >> m.y;
    kiemtradiem(a, b, c, m);

    return 0;
}

/* test case: 
Nhập toạ độ điểm A: 0 0
Nhập toạ độ điểm B: 0 3
Nhập toạ độ điểm C: 4 0
- Kết quả kiểm tra tam giác: Là tam giác
- Dạng của tam giác: Tam giác vuông
- Toạ độ trọng tâm: (1.33333, 1)
- Điểm có hoành độ lớn nhất: (4, 0)
- Điểm có tung độ nhỏ nhất: (0, 0)
- Chu vi tam giác: 12
- Diện tích tam giác: 6
- Nhập toạ độ điểm M: 1 1
- Kết quả kiểm tra điểm M: Nằm trong tam giác
Test case 2: 
Nhập toạ độ điểm A: 1 1
Nhập toạ độ điểm B: 2 3
Nhập toạ độ điểm C: 4 2
- Kết quả kiểm tra tam giác: Là tam giác
- Dạng của tam giác: Tam giác thường
- Toạ độ trọng tâm: (2.33333, 2)
- Điểm có hoành độ lớn nhất: (4, 2)
- Điểm có tung độ nhỏ nhất: (1, 1)
- Chu vi tam giác: 8.67283
- Diện tích tam giác: 1.5
- Nhập toạ độ điểm M: 3 2
- Kết quả kiểm tra điểm M: Nằm trong tam giác
Test case 3: 
Nhập toạ độ điểm A: 0 0
Nhập toạ độ điểm B: 0 1
Nhập toạ độ điểm C: 0 2
- Kết quả kiểm tra tam giác: Không thành tam giác
*/
