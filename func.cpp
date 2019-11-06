//
// Created by Slava Karpii on 03.11.2019.
//

#include "func.h"

vector<point> bucket_sort(vector<point> arr) {
    point min_el(0, 0);
    point max_el(width, height);
    int num_b = 3;
    for (int i = 0; i < arr.size() - 1; i++) {
        min_el = min(min_el, arr[i]);
        max_el = max(max_el, arr[i]);
    }
    int range = int(max_el.y - min_el.y);
    vector<vector<point>> buckets(num_b);
    for (int i = 0; i < arr.size(); i++) {
        int index = int(arr[i].y * num_b / range);
        buckets[index].push_back(arr[i]);
    }
    for (int i = 0; i < num_b; i++)
        sort(buckets[i].begin(), buckets[i].end());
    vector<point> res;
    for (int i = 0; i < num_b; i++)
        for (int j = 0; j < buckets[i].size(); j++)
            res.push_back(buckets[i][j]);
    return res;
}

vector<point> kirp(vector<point> input) {
    cout << "Cayle-Kirpatrik\n";
    input = bucket_sort(input);
    vector<point> al;
    vector<point> ar;
    for (int i = 0; i < input.size(); i++) {
        al.push_back(input[i]);
        while (i + 1 < input.size() && input[i].y == input[i + 1].y)
            i++;
        ar.push_back(input[i]);
    }

    for (int i = al.size() - 2; i > 0; i--) {
        while (S(al[i + 1], al[i], al[i - 1]) < 0 && i != al.size() - 1)
            al.erase(al.begin() + i);
    }

    for (int i = ar.size() - 2; i > 0; i--) {
        while (S(ar[i + 1], ar[i], ar[i - 1]) > 0 && i != ar.size() - 1)
            ar.erase(ar.begin() + i );
    }


    for (int i = ar.size() - 1; i >= 0; i--)
        al.push_back(ar[i]);
    al.push_back(al[0]);
    return al;
}


double S(point a, point b, point c){
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}


vector<point> graham(vector<point> input) {
    cout << "Graham\n";
    vector<point> res;
    sort(input.begin(), input.end());
    point p = input[input.size() - 1];
    sort(input.begin(), input.end(), [p](const point &a, const point &b){ return S(p, a, b) > 0;});
    res.push_back(p);
    for (size_t i = 0; i < input.size(); i++) {
        while (res.size() >= 2 && S(res[res.size() - 2], res[res.size() - 1], input[i]) < 0)
            res.pop_back();
        res.push_back(input[i]);
    }

    return res;
}

vector<point> an_j(vector<point> input) {
    cout << "Andrew-Jarvis\n";
    sort(input.begin(), input.end(), [](const point &a, const point &b){ return a.x == b.x ? a.y > b.y : a.x < b.x;});
    point p1 = input[0];
    point p2 = input[input.size() - 1];
    vector<point> up;
    vector<point> upper;
    vector<point> down;
    vector<point> lower;
    for (auto i : input) {
        if (S(p1, p2, i) <= 0)
            upper.push_back(i);
        if (S(p1, p2, i) >= 0)
            lower.push_back(i);
    }
    up.push_back(p1);
    for (int i = 0; i < upper.size(); i++) {
        point a = up[up.size() - 1];
        point b = upper[i];
        bool flag = true;
        for (int j = 0; j < upper.size() && flag ; j++) {
           flag = S(a, b, upper[j]) >= 0;
        }
        if (flag)
            up.push_back(b);
    }

    down.push_back(p2);
    for (int i = 0; i < lower.size(); i++) {
        point a = down[down.size() - 1];
        point b = lower[i];
        bool flag = true;
        for (int j = 0; j < lower.size() && flag ; j++) {
            flag = S(a, b, lower[j]) <= 0;
        }
        if (flag)
            down.push_back(b);
    }
    down.erase(down.begin());
    for (int i = down.size() - 1; i >= 0; i--)
        up.push_back(down[i]);
    return up;
}

vector<point> quick_hull(vector<point> input) {
    cout << "Recursive quick\n";
    sort(input.begin(), input.end(), [](const point &a, const point &b){ return a.x == b.x ? a.y > b.y : a.x < b.x;});
    point p1 = input[0];
    point p2 = input[input.size() - 1];
    vector<point> res;
    res.push_back(p1);
    res.push_back(p2);
    vector<point> upper;
    vector<point> lower;
    for (auto i : input) {
        if (S(p1, i, p2) >= 0)
            upper.push_back(i);
        if (S(p1, i, p2) <= 0)
            lower.push_back(i);
    }

    find_hull(upper, p1, p2, res);
    find_hull(lower, p2, p1, res);

    res.push_back(res[0]);
    return res;
}

void find_hull(vector<point> &input, point a, point b, vector<point> &res) {
    if (input.empty())
        return;
    int ind = 0;
    for (int i = 1; i < input.size(); i++) {
        if ( abs(S(a, input[i], b)) > abs(S(a, input[ind], b)))
            ind = i;
    }
    point c = input[ind];
    insert(res, a, b, c);
    vector<point> s1;
    vector<point> s2;
    for (auto i : input) {
        if (S(a, i, c) > 0)
            s1.push_back(i);
        if (S(c, i, b) > 0)
            s2.push_back(i);
    }
    find_hull(s1, a, c, res);
    find_hull(s2, c, b, res);
}

void insert(vector<point> &res, point a, point b, point c) {
    int i;
    for (i = 0; i < res.size(); i++){
        if (a == res[i])
            break;
    }
    res.insert(res.begin() + i + 1, c);
}
