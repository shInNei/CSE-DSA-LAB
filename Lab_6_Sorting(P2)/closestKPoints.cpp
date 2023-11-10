/* Your helping functions go here */
Point des;
bool cmp(const Point& a, const Point& b) {
    int da = sqrt(pow(a.x - des.x,2) + pow(a.y - des.y,2));
    int db = sqrt(pow(b.x - des.x,2) + pow(b.y - des.y,2));
    return da < db;
}
void closestKPoints(Point points[], int n, Point &des_point, int k){
    //TODO
    if(k > n) k = n;
    des.x = des_point.x;
    des.y = des_point.y;
    stable_sort(points, points + n, cmp);
    int i = 0;
    while(k) {
        points[i].display();
        cout << endl;
        k--;
        i++;
    }
}
