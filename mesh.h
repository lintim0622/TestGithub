#ifndef MESH_H_
#define MESH_H_

#include "mpmvector.h"

class Material {
private:
    float rho, K, G;
    float E; // Young
    float v; // poisson

    float E1;
    float E2;
    Matrix D;

public:
    Material(float rho, float K, float G);
    ~Material();
    void verify_time_step(float& Unit_Grid, float& dt);
    float get_rho() const { return rho; }
    float get_E() const { return E; }
    Matrix& get_D() { return D; }
};

class Node {
private:
    int nid = 0;
    float mass = 0.0f;
    Vector2D* position = nullptr;
    Vector2D* velocity = nullptr;
    Vector2D* momentum = nullptr;
    Vector2D* acceleration = nullptr;
    Vector2D* f_int = nullptr;
    Vector2D* f_ext = nullptr;
    Vector2D* f_bc = nullptr;
    Vector2D* f_c = nullptr;
    Vector2D* normal = nullptr;

public:
    Node();
    ~Node();

    void set_nid(int id) { this->nid = id; }
    void set_xn(float position[]) { this->position->set_component(position); }

    int get_nid() const { return this->nid; }
    float get_mass() const { return this->mass; }
    Vector2D& get_vn() const { return *(this->velocity); }
    Vector2D& get_xn() const { return *(this->position); }
    Vector2D& get_pn() const { return *(this->momentum); }
    Vector2D& get_an() const { return *(this->acceleration); }
    Vector2D& get_f_int() const { return *(this->f_int); }
    Vector2D& get_f_ext() const { return *(this->f_ext); }
    Vector2D& get_f_bc() const { return *(this->f_bc); }
    Vector2D& get_f_c() const { return *(this->f_c); }
    Vector2D& get_nc() const { return *(this->normal); }
};

class Element;
class Particle {
private:
    float rho = 0.0f, E = 0.0f;
    int pid = 0;
    float mass = 0.0f;
    float Volume = 0.0f;

protected:
    Vector2D* position = nullptr;
    Vector2D* velocity = nullptr;
    Vector2D* momentum = nullptr;
    Vector2D* body_force = nullptr;

    Tensor* strain = nullptr;
    Tensor* stress = nullptr;
    Tensor* specific_stress = nullptr;
    Tensor* strain_increment = nullptr;

    float Ni[4] = { 0 };
    float dNi[4][2] = { 0 };

    Element* element = nullptr;

public:
    Particle();
    ~Particle();

    void set_material(Material& material) { rho = material.get_rho(); E = material.get_E(); }
    void set_position(const float position[]) { this->position->set_component(position); }
    void set_pid(int id) { pid = id; }
    void set_mass(float mp) { mass = mp; }
    void set_Volume(float vol) { Volume = vol; }
    void set_velocity(float* velocity) { this->velocity->set_component(velocity); }
    void set_momentum(Vector2D* v) { this->momentum->set_component(*v); }
    void set_bodyForce(float* bf) { this->body_force->set_component(bf); }
    void set_strain(float* ep) { this->strain->set_component(ep); }
    void set_stress(float* sp) { this->stress->set_component(sp); }
    void set_specific_stress(Tensor *ssp) { this->specific_stress->set_component(*ssp); }
    void set_element(Element *e) { this->element = e; }

    float get_rho() const { return rho; }
    float get_E() const { return E; }
    int get_pid() const { return pid; }
    float get_mass() const { return mass; }
    float get_Volume() const { return Volume; }

    Vector2D& get_xp() const { return *(this->position); }
    Vector2D& get_vp() const { return *(this->velocity); }
    Vector2D& get_pp() const { return *(this->momentum); }
    Vector2D& get_bp() const { return *(this->body_force); }

    Tensor& get_strain() const { return *(this->strain); }
    Tensor& get_stress() const { return *(this->stress); }
    Tensor& get_specific_stress() const { return *(this->specific_stress); }
    Tensor& get_strain_increment() const { return *(this->strain_increment); }

    Element& get_element() const { return *(this->element); }

    float* get_N() { return this->Ni; }
    float* get_dN() { return &(this->dNi[0][0]); }
};

class Element {
private:
    int eid = 0;
    float L[2];
    
protected:
    Node* n1 = nullptr;
    Node* n2 = nullptr;
    Node* n3 = nullptr;
    Node* n4 = nullptr;
    Particle* particles = nullptr;

public:
    Element();
    ~Element();

    void set_eid(int id) { this->eid = id; }
    void set_n1(Node* n) { this->n1 = n; }
    void set_n2(Node* n) { this->n2 = n; }
    void set_n3(Node* n) { this->n3 = n; }
    void set_n4(Node* n) { this->n4 = n; }
    void set_elemSize(float Unit_Grid) { L[0] = L[1] = Unit_Grid; }
    void set_particles(Particle* p) { this->particles = p; }
    void set_particle(Particle& p, int i) { this->particles[i] = p; }

    int get_eid() { return eid; }
    Node* get_n1() { return n1; }
    Node* get_n2() { return n2; }
    Node* get_n3() { return n3; }
    Node* get_n4() { return n4; }

    Particle* get_particles() { return this->particles; }
    Particle& get_particle(int i) { return this->particles[i]; }
};

class Mesh {
private:
    int dim = 0;
    int tot_elem_num = 0;
    int tot_node_num = 0;
    int tot_ptc_num = 0;

protected:
    Material* elastic = nullptr;
    Element* elements = nullptr;
    Node* nodes = nullptr;
    Particle* particles = nullptr, * temp_part = nullptr;

public:
    Mesh(int dim, float* xp, float* xn, int nelem, float Unit_Grid,
        int tot_elem_num, int tot_node_num, int tot_ptc_num, Material& elastic);
    ~Mesh();
    void imposeMPM_IC(float* vpo, float* epo, float* bpo);
    void show_node();

    int get_tot_ptc_num() const { return tot_ptc_num; }
    Particle* get_particle(int i) { return &(particles[i]); }
};


#endif
/*


class BC(object):
    def __init__(self, form, p1, p2):
        this->form = form
        # this->Unit_Grid = Unit_Grid
        this->p1 = p1
        this->p2 = p2
        this->vbc = np.array([0.0, 0.0])
        this->mu = 0.0

        dy = this->p2[1]-this->p1[1]
        dx = this->p2[0]-this->p1[0]
        if this->p2[0]-this->p1[0] != 0:
            this->theta = np.arctan(dy/dx)
            if (dx < 0) and (dy > 0):
                this->theta = np.pi+this->theta
            if (dx < 0) and (dy < 0):
                this->theta = np.pi+this->theta
            if (dx > 0) and (dy < 0):
                this->theta = 2.0*np.pi+this->theta
            if (dx < 0) and (dy == 0):
                this->theta = np.pi
        if this->p2[0]-this->p1[0] == 0:
            if dy > 0:
                this->theta = np.pi/2.0
            else:
                this->theta = 3.0*np.pi/2.0

    def set_normal(self, nbc):
        this->nbc = nbc

    def set_friction_coefficient(self, mu):
        this->mu = mu

    def set_function(self, *arg):
        f = lambda x : arg[0]*x*x+arg[1]*x+arg[1]
        return f

    def f(self, x):
        return 0.0

    def df(self, x):
        return 0.0

    def ddf(self, x):
        return 0.0

    def re_transform_matrix(self, xo):
        x = (xo[0]-this->p1[0])*np.cos(this->theta)+(xo[1]-this->p1[1])*np.sin(this->theta)
        y = -(xo[0]-this->p1[0])*np.sin(this->theta)+(xo[1]-this->p1[1])*np.cos(this->theta)
        return (x, y)

    def transform_matrix(self, xl):
        x = (xl[0])*np.cos(this->theta)-(xl[1])*np.sin(this->theta)
        y = (xl[0])*np.sin(this->theta)+(xl[1])*np.cos(this->theta)
        return (x+this->p1[0], y+this->p1[1])

    def newton_method(self, x_ik):
        tol = 1e-10
        xi = x_ik[0]
        yi = x_ik[1]
        x = xi
        y = round(this->f(x), 10)

        num = 0
        while (True):
            Tt = np.array([1, this->df(x)])

            if ((yi-y) == 0.0):
                n = np.array([this->nbc[0], this->nbc[1]])
                if (x < xi):
                    n *= (-1.0)
                A, dA, B, dB = 0.0, 0.0, 0.0, 0.0
            else:
                n = np.array([xi-x, yi-y])/np.sqrt((xi-x)*(xi-x)+(yi-y)*(yi-y))
                A = 1/np.sqrt((xi-x)*(xi-x)+(yi-y)*(yi-y))
                dA = -0.5*pow((xi-x)*(xi-x)+(yi-y)*(yi-y), -1.5)*(-2.0*(xi-x)-2.0*(yi-y)*this->df((x)))
                B = Tt[0]*(xi-x)+Tt[1]*(yi-y)
                dB = -Tt[0]+this->ddf(x)*(yi-y)+Tt[1]*(-this->df(x))

            N = Tt.dot(n)
            dN = dA*B+A*dB

            if (dN == 0.0):
                x -= 0.0
            else:
                x -= N/dN

            y = round(this->f(x), 10)
            if (abs(N) <= tol):
                return x, y

            if (num > 100):
                return x, y
            num += 1
*/