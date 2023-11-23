//
// Created by admin on 23/10/2023.
//

#ifndef PELAGEIA_IMMERSIVE_VECTOR2D_H
#define PELAGEIA_IMMERSIVE_VECTOR2D_H

class Vector2D
{
public:
    float X;
    float Y;

    Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

    // Addition
    inline Vector2D operator+(const Vector2D& vector) const { return Vector2D(X + vector.X, Y + vector.Y); }
    inline Vector2D operator+(const float scalar) const { return Vector2D(X + scalar, Y + scalar); }

    // Difference
    inline Vector2D operator-(const Vector2D& vector) const { return Vector2D(X - vector.X, Y - vector.Y); }
    inline Vector2D operator-(const float scalar) const { return Vector2D(X - scalar, Y - scalar); }

    // Multiplication
    inline Vector2D operator*(const Vector2D& vector) const { return Vector2D(X * vector.X, Y * vector.Y); }
    inline Vector2D operator*(const float scalar) const { return Vector2D(X * scalar, Y * scalar); }

    // Division
    inline Vector2D operator/(const Vector2D& vector) const { return Vector2D(X / vector.X, Y / vector.Y); }
    inline Vector2D operator/(const float scalar) const { return Vector2D(X / scalar, Y / scalar); }

private:
};

#endif  // PELAGEIA_IMMERSIVE_VECTOR2D_H
