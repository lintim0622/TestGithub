#include "mpmvector.h"
#include <iostream>

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const float array[]) {
    x = array[0];
    y = array[1];
}

Vector2D::Vector2D(const Vector2D& vec) {
    this->x = vec.x;
    this->y = vec.y;
}

Vector2D::~Vector2D() {}

void Vector2D::set_component(const float array[]) {
    this->x = array[0];
    this->y = array[1];
}

void Vector2D::set_component(const Vector2D& vec) {
    this->x = vec[0];
    this->y = vec[1];
}

float Vector2D::get_component(int index) const {
    float component = 0.0f;
    switch (index) {
    case 0:
        component = this->x;
        break;
    case 1:
        component = this->y;
        break;
    default:
        std::cout << "Error index in Vector2D\n";
        break;
    }
    return component;
}

float Vector2D::operator[](int index) const {
    return this->get_component(index);
}

/*

Vector2D& Vector2D::operator=(const Vector2D& vec) {
    this->x = vec.x;
    this->y = vec.y;
   
   return *this;
}
Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec) {
    Vector2D ans;
    ans.x = this->x + vec.x;
    ans.y = this->y + vec.y;
    return ans;
}
*/

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
}

Vector2D Vector2D::operator*(const float val) {
    return Vector2D(*this) * val;
}

float Vector2D::get_x() {
    return this->x;
}

float Vector2D::get_y() {
    return this->y;
}

void Vector2D::show() const {
    std::cout << "x component : " << this->x << std::endl;
    std::cout << "y component : " << this->y << std::endl;
}

/* ==================================================================== */

Tensor::Tensor(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Tensor::~Tensor() {}

void Tensor::set_component(float array[]) {
    this->x = array[0];
    this->y = array[1];
    this->z = array[2];
}

void Tensor::set_component(const Tensor& sv) {
    this->x = sv[0];
    this->y = sv[1];
    this->z = sv[2];
}

float Tensor::get_component(int index) const {
    float component = 0.0f;
    switch (index) {
    case 0:
        component = this->x;
        break;
    case 1:
        component = this->y;
        break;
    case 2:
        component = this->z;
        break;
    default:
        std::cout << "Error index in Tensor\n";
        break;
    }
    return component;
}

float Tensor::operator[](int index) const {
    return this->get_component(index);
}

/*
Tensor& Tensor::operator+=(const Tensor& svec) {
    this->x += svec.x;
    this->y += svec.y;
    this->z += svec.z;
    return *this;
}

Tensor& Tensor::operator-=(const Tensor& svec) {
    this->x -= svec.x;
    this->y -= svec.y;
    this->z -= svec.z;
    return *this;
}

Tensor& Tensor::operator*=(const Tensor& svec) {
    this->x *= svec.x;
    this->y *= svec.y;
    this->z *= svec.z;
    return *this;
}

Tensor& Tensor::operator=(const Tensor& svec) {
    this->x = svec.x;
    this->y = svec.y;
    this->z = svec.z;
    return *this;
}
*/

Tensor Tensor::operator/(const float val) {
    Tensor ans;
    ans.x = this->x / val;
    ans.y = this->y / val;
    ans.z = this->z / val;
    return ans;
}

void Tensor::show() const {
    std::cout << "x component : " << this->x << std::endl;
    std::cout << "y component : " << this->y << std::endl;
    std::cout << "z component : " << this->z << std::endl;
}

float Matrix::get_component(int index) const {
    float component = 0.0f;
    switch (index) {
    case 0:
        component = this->m11;
        break;
    case 1:
        component = this->m12;
        break;
    case 2:
        component = this->m13;
        break;
    case 3:
        component = this->m21;
        break;
    case 4:
        component = this->m22;
        break;
    case 5:
        component = this->m23;
        break;
    case 6:
        component = this->m31;
        break;
    case 7:
        component = this->m32;
        break;
    case 8:
        component = this->m33;
        break;
    default:
        std::cout << "Error index in Matrix\n";
        break;
    }
    return component;
}

float Matrix::operator[](int index) const {
    return this->get_component(index);
};

float* Matrix::dot(Tensor& vec) {
    float* ans = new float[3];
    ans[0] = m11 * vec[0] + m12 * vec[1] + m13 * vec[2];
    ans[1] = m21 * vec[0] + m22 * vec[1] + m23 * vec[2];
    ans[2] = m31 * vec[0] + m32 * vec[1] + m33 * vec[2];
    return ans;
}