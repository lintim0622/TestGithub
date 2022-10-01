// #pragma once
#ifndef MPMVECTOR_H_
#define MPMVECTOR_H_

class Vector2D {
private:
    float x, y;

public:
    Vector2D() { this->x = 0.0f; this->y = 0.0f; }
    Vector2D(float x, float y);
    Vector2D(const float array[]);
    Vector2D(const Vector2D& vec);
    ~Vector2D();

    void set_component(const float array[]);
    void set_component(const Vector2D& vec);
    float get_component(int index) const;

    float operator[](int index) const;
    /*Vector2D& operator=(const Vector2D& vec);
    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D operator+(const Vector2D& vec);*/
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D operator*(const float val);

    float get_x();
    float get_y();
    void show() const;
};

class Tensor {
private:
    float x, y, z;

public:
    Tensor() { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; }
    Tensor(float x, float y, float z);
    ~Tensor();

    void set_component(float array[]);
    void set_component(const Tensor& sv);
    float get_component(int index) const;

    float operator[](int index) const;
    /*Tensor& operator=(const Tensor& svec);
    Tensor& operator+=(const Tensor& svec);
    Tensor& operator*=(const Tensor& svec);
    Tensor& operator-=(const Tensor& svec);*/
    Tensor operator/(const float val);

    void show() const;
};

class Matrix {
private:
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;

public:
    Matrix() { m11 = m12 = m13 = m21 = m22 = m23 = m31 = m32 = m33 = 0.0f; }
    ~Matrix() {}

    void set_m11(float x11) { m11 = x11; }
    void set_m12(float x12) { m12 = x12; }
    void set_m13(float x13) { m13 = x13; }
    void set_m21(float x21) { m21 = x21; }
    void set_m22(float x22) { m22 = x22; }
    void set_m23(float x23) { m23 = x23; }
    void set_m31(float x31) { m31 = x31; }
    void set_m32(float x32) { m32 = x32; }
    void set_m33(float x33) { m33 = x33; }

    float get_component(int index) const;
    float operator[](int index) const;

    float get_m11() const { return m11; }

    float* dot(Tensor& vec);
};

#endif

