//
// Hod Amar and Ofek Avergil
//
#include "minCircle.h"
/**
 * Return the distance between 2 points.
 */
float dist(const Point& a, const Point& b) {
    return (float) sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/**
 * Check if the given point inside of the given circle.
 */
bool isInside(const Circle& c, const Point& p) {
    float x = dist(c.center, p);
    return dist(c.center, p) <= c.radius;
}

/**
 * Check for each point in the vector is inside of the given circle.
 */
bool isValidCircle(const Circle& c, vector<Point> points) {
    for (Point p : points) {
        if (!isInside(c, p)) {
            return false;
        }
    }
    return true;
}

/**
 * Build circle from 3 points.
 */
Circle circleFrom3Pnts(Point p1, Point p2, Point p3) {
    // center point
    float bx = p2.x - p1.x;
    float by = p2.y - p1.y;
    float cx = p3.x - p1.x;
    float cy = p3.y - p1.y;
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx * cy - by * cx;

    Point cen((cy * B - by * C) / (2 * D),
              (bx * C - cx * B) / (2 * D));
    cen.x += p1.x;
    cen.y += p1.y;
    return {cen, dist(cen, p1)};
}

/**
 * Build circle from 2 points.
 */
Circle circleFrom2Pnts(Point p1, Point p2) {
    // center point.
    Point c = Point ((float)((p1.x + p2.x) / 2.0), (float)((p1.y + p2.y) / 2.0));
    // radius.
    float r = dist(p1, p2) / 2.0;
    Circle circle(c, r);
    return circle;

    }

/**
 *  Base case of the algorithm.
 */
Circle trivialCircle(vector<Point>& vec) {
    int size = vec.size();
    if (0 == size) {
        return Circle(Point(0, 0), 0);
    }
    if (1 == size) {
        return Circle(vec[0], 0);
    }
    if (2 == size) {
        return circleFrom2Pnts(vec[0], vec[1]);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            Circle c = circleFrom2Pnts(vec[i], vec[j]);
            if (isValidCircle(c, vec))
                return c;
        }
    }

    return circleFrom3Pnts(vec[0], vec[1], vec[2]);
}
/**
 * Welzl's algoritm
 */
    Circle findMinCircleHelp(Point **points, vector<Point> vec, size_t n) {
        // base - there is no points or vec size is 3
        if (n == 0 || vec.size() == 3) {
            return trivialCircle(vec);
        }
        // pick random point from the array
        size_t r = random() % n;
        Point p = Point(points[r]->x, points[r]->y);
        // ignore the random point.
        swap(points[r], points[n - 1]);
        Circle circle = findMinCircleHelp(points, vec, (n - 1));
        // if circle contains p so return c.
        if (isInside(circle, p)) {
            return circle;
        }
        // otherwise c is the bound of circle
        vec.push_back(p);
        // the minimal circle with p.
        return findMinCircleHelp(points, vec, (n - 1));

    }

    Circle findMinCircle(Point **points, size_t size) {
         return findMinCircleHelp(points, {}, size);
    }


