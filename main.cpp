#include <iostream>
#include <SFML/Graphics.hpp>
#include "func.h"

auto convex_hull = [](vector<point> &points){return kirp(points);};


int main() {
    point p;
    srand(time(nullptr));
    int num = 100;
    vector<sf::CircleShape> Points(num );
    vector<point> points;
    for (int i = 0; i < num; i++){
        p.y =  rand() % int(height);
        p.x =  rand() % int(width);
        points.push_back(p);
        Points[i].setRadius(4);
        Points[i].setPosition(p.x - 4, p.y - 4);
    }

    vector<point> hull =  convex_hull(points);
    vector<sf::CircleShape> draw_hull(hull.size());
    vector<sf::Vertex> bound_box;
    for (int i = 0; i < hull.size(); i++){
        bound_box.emplace_back(sf::Vector2f(hull[i].x, hull[i].y));
        draw_hull[i].setRadius(6);
        draw_hull[i].setFillColor(sf::Color(255, 0 , 0));
        draw_hull[i].setPosition(hull[i].x - 6, hull[i].y - 6);
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "convex hull");
    while (window.isOpen()) {
        sf::Event even{};

        while (window.pollEvent(even)) {
            if (even.type == sf::Event::Closed)
                window.close();

        }
        window.clear(sf::Color(0));
        for (const sf::CircleShape& point : Points) {
            window.draw(point);
        }

        window.draw(&bound_box[0], bound_box.size(), sf::LinesStrip);

        for (const sf::CircleShape& point : draw_hull) {
            window.draw(point);
        }
        window.display();
    }


}