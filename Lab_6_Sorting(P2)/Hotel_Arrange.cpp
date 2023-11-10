int maxNumberOfPeople(vector<int>& rooms, vector<int>& people, int k) {
    sort(rooms.begin(), rooms.end());
    sort(people.begin(), people.end());
    int i = 0, j = 0, res = 0;
    while(i < rooms.size() && j < people.size()) {
        if(abs(rooms[i] - people[j]) <= k) {
            res++;
            i++;
            j++;
        } else if(rooms[i] < people[j]) i++;
        else j++;
    }
    return res;
}
