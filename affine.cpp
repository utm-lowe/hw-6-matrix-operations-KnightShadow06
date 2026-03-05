/**
 * @file affine.cpp
 * @author Bob Lowe
 * @brief Perform affine transformations on 2D points.
 * @version 0.1
 * 
 * @copyright Copyright (c) 2024
 * 
 */

 //Functions from CoPilot, but I have used them to learn and take notes.

#include "matrix.h"
#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

// Transformation Matrix Creation Functions

/**
 * @brief Create a 3x3 identity matrix.
 * 
 * @return Matrix 
 */
Matrix transIdent();

/**
 * @brief Rotate about an angle in degrees
 * 
 * @param angle 
 * @return Matrix 
 */
Matrix transRotate(double angle);


/**
 * @brief Scale by factors sx and sy
 * 
 * @param sx 
 * @param sy 
 * @return Matrix 
 */
Matrix transScale(double sx, double sy);

/**
 * @brief Translate by tx and ty
 * 
 * @param tx 
 * @param ty 
 * @return Matrix 
 */
Matrix translate(double tx, double ty);

/**
 * @brief Prompt the user for transformations, return the resultant matrix.
 * 
 * @return Matrix 
 */
Matrix transformMenu();

/**
 * @brief Get the 3 element column vector affine point from the user.
 * 
 * @return Matrix 
 */
Matrix getPoint();

int main() 
{
    Matrix transform = transformMenu();

    // Display the transformation matrix
    //cout << "Transformation Matrix: " << endl;
    cout << transform << endl;
    cout << transform << endl;
    cout << endl;

    // transform points
    while (cin >> ws && !cin.eof()) {
        Matrix point = getPoint();
        point = transform * point;

        // If we have a new point, display it.
        if(cin) {
            cout << "Transformed Point: (" 
                 << point.at(0,0) << ", " << point.at(1,0) << ")" << endl;
        }
    }
}


// build an identity matrix
Matrix transIdent()
{
    Matrix id(3, 3);
    id.at(0, 0) = 1; id.at(0, 1) = 0; id.at(0, 2) = 0;
    id.at(1, 0) = 0; id.at(1, 1) = 1; id.at(1, 2) = 0;
    id.at(2, 0) = 0; id.at(2, 1) = 0; id.at(2, 2) = 1;
    return id;
}


// build a rotation matrix
Matrix transRotate(double angle)
{
    const double PI = 3.14159265358979323846;
    double rad = angle * PI / 180.0;
    Matrix rot(3, 3);
    rot.at(0, 0) = cos(rad); rot.at(0, 1) = -sin(rad); rot.at(0, 2) = 0;
    rot.at(1, 0) = sin(rad); rot.at(1, 1) = cos(rad); rot.at(1, 2) = 0;
    rot.at(2, 0) = 0; rot.at(2, 1) = 0; rot.at(2, 2) = 1;
    return rot;
}

// build a scaling matrix
Matrix transScale(double sx, double sy) 
{
    Matrix scale(3, 3);
    scale.at(0, 0) = sx; scale.at(0, 1) = 0; scale.at(0, 2) = 0;
    scale.at(1, 0) = 0; scale.at(1, 1) = sy; scale.at(1, 2) = 0;
    scale.at(2, 0) = 0; scale.at(2, 1) = 0; scale.at(2, 2) = 1;
    return scale;
}

// build a translation matrix
Matrix translate(double tx, double ty) 
{
    Matrix trans(3, 3);
    trans.at(0, 0) = 1; trans.at(0, 1) = 0; trans.at(0, 2) = tx;
    trans.at(1, 0) = 0; trans.at(1, 1) = 1; trans.at(1, 2) = ty;
    trans.at(2, 0) = 0; trans.at(2, 1) = 0; trans.at(2, 2) = 1;
    return trans;
}

// do the transformation menu
Matrix transformMenu()
{
    Matrix result = transIdent();
    double x,y,angle;
    char choice;

    do {
        // get the choice
        cin >> choice;
        choice = toupper(choice);

        switch(choice) {
            case 'T':
                cin >> x >> y;
                result = translate(x, y) * result;
                break;
            case 'R':
                cin >> angle;
                result = transRotate(angle) * result;
                break;
            case 'S':
                cin >> x >> y;
                result = transScale(x, y) * result;
                break;
            case 'D':
                break;
        }

    }while(choice != 'D');

    return result;
}


// get the point from the user 
Matrix getPoint() 
{
    double x, y;
    cin >> x >> y;
    Matrix point(3, 1);
    point.at(0, 0) = x;
    point.at(1, 0) = y;
    point.at(2, 0) = 1;
    return point;
}