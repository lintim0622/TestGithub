#include "mesh.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>

/* ============ Material =========================================================== */

Material::Material(float rho, float K, float G) : rho(rho), K(K), G(G) {
    E = (float) (9.0f * K * G / (3.0f * K + G));
    v = (float) (0.5f * (3.0f * K - 2.0f * G) / (3.0f * K + G)); // poisson

    E1 = E / (1.0f - v * v);
    E2 = v * E / (1.0f - v * v);

    D.set_m11(E1);
    D.set_m12(E2);
    D.set_m13(0.0f);

    D.set_m21(E2);
    D.set_m22(E1);
    D.set_m23(0.0f);

    D.set_m31(0.0f);
    D.set_m32(0.0f);
    D.set_m33(G);
}

Material::~Material() {}

void Material::verify_time_step(float& Unit_Grid, float& dt) {
    // P wave velocity -> vel_p
    float M = (float)(K + 4.0f * G / 3.0f);
    float vel_p = (float)std::sqrt((double)M / rho);
    float dt_critical = (float)(Unit_Grid / (10.0f * vel_p));
    if (dt > dt_critical) {
        printf("dt = %f\n", dt);
        printf("dt_critical = %f\n", dt_critical);
        printf("need reset time step\n");
        std::exit(1);
    }
}

/* ============ Node =========================================================== */

Node::Node() {
    this->position = new Vector2D();
    this->velocity = new Vector2D();
    this->momentum = new Vector2D();
    this->acceleration = new Vector2D();
    this->f_int = new Vector2D();
    this->f_ext = new Vector2D();
    this->f_bc = new Vector2D();
    this->f_c = new Vector2D();
    this->normal = new Vector2D();
}

Node::~Node() {
    delete position;
    delete velocity;
    delete momentum;
    delete acceleration;
    delete f_int;
    delete f_ext;
    delete f_bc;
    delete f_c;
    delete normal;
    position = nullptr;
    velocity = nullptr;
    momentum = nullptr;
    acceleration = nullptr;
    f_int = nullptr;
    f_ext = nullptr;
    f_bc = nullptr;
    f_c = nullptr;
    normal = nullptr;
    printf("nid = %d, Node has been deleted\n", this->nid);
}


/* ============ Particle =========================================================== */

Particle::Particle() {
    this->position = new Vector2D();
    this->velocity = new Vector2D();
    this->momentum = new Vector2D();
    this->body_force = new Vector2D();

    this->strain = new Tensor();
    this->stress = new Tensor();
    this->specific_stress = new Tensor();
    this->strain_increment = new Tensor();
}

Particle::~Particle() {
    delete position;
    delete velocity;
    delete momentum;
    delete body_force;
    delete strain;
    delete stress;
    delete specific_stress;
    delete strain_increment;
    position = nullptr;
    velocity = nullptr;
    momentum = nullptr;
    body_force = nullptr;
    strain = nullptr;
    stress = nullptr;
    specific_stress = nullptr;
    strain_increment = nullptr;
    printf("pid = %d, Particle has been deleted\n", pid);
}

/* ============ Element =========================================================== */

Element::Element() {
    this->L[0] = 0.0f;
    this->L[1] = 0.0f;
}

Element::~Element() {
    printf("eid = %d, Element has been deleted\n", this->eid);
}

/* ============ Mesh =========================================================== */

Mesh::Mesh(int dim, float* xp, float* xn, int nelem, float Unit_Grid,
    int tot_elem_num, int tot_node_num, int tot_ptc_num, Material& elastic) {
    this->dim = dim;
    this->elastic = &elastic;
    this->tot_elem_num = tot_elem_num;
    this->tot_node_num = tot_node_num;
    this->tot_ptc_num = tot_ptc_num;
    this->elements = new Element[tot_elem_num];
    this->nodes = new Node[tot_node_num];
    this->particles = new Particle[tot_ptc_num];

    for (int i = 0; i < tot_node_num; i++) {
        this->nodes[i].set_nid(i);
        this->nodes[i].set_xn(&(xn[i * 2]));
    }

    // put nodes in element
    int i = 0;
    for (int e = 0; e < tot_elem_num; e++) {
        if ((e % nelem) == 0 && (e != 0))
            i++;
        this->elements[e].set_eid(e);
        this->elements[e].set_elemSize(Unit_Grid);
        this->elements[e].set_n1(&(this->nodes[e + i]));
        this->elements[e].set_n2(&(this->nodes[e + 1 + i]));
        this->elements[e].set_n3(&(this->nodes[e + 1 + nelem + i]));
        this->elements[e].set_n4(&(this->nodes[e + 2 + nelem + i]));

        int ptc_in_elem_num = 0;
        for (int p = 0; p < tot_ptc_num; p++) {
            if ((this->elements[e].get_n1()->get_xn().get_x() <= xp[p * 2 + 0]) && (xp[p * 2 + 0] <= this->elements[e].get_n2()->get_xn().get_x()))
                if ((this->elements[e].get_n2()->get_xn().get_y() <= xp[p * 2 + 1]) && (xp[p * 2 + 1] <= this->elements[e].get_n4()->get_xn().get_y()))
                    ptc_in_elem_num++;
        }
        this->elements[e].set_particles(new Particle[ptc_in_elem_num]);
    }

    // put particles in element
    for (int e = 0; e < tot_elem_num; e++) {
        int j = 0;
        for (int p = 0; p < tot_ptc_num; p++) {
            if ((this->elements[e].get_n1()->get_xn().get_x() <= xp[p * 2 + 0]) && (xp[p * 2 + 0] <= this->elements[e].get_n2()->get_xn().get_x())) {
                if ((this->elements[e].get_n2()->get_xn().get_y() <= xp[p * 2 + 1]) && (xp[p * 2 + 1] <= this->elements[e].get_n4()->get_xn().get_y())) {
                    this->particles[p].set_material(elastic);
                    this->particles[p].set_position(&(xp[p * 2]));
                    this->particles[p].set_pid(p);
                    this->particles[p].set_Volume((float).25 * .25 * 1.0);
                    this->elements[e].set_particle(this->particles[p], j);
                    this->elements[e].get_particle(j).set_element(&(this->elements[e]));
                    j++;
                }
            }    
        }
    }
}

Mesh::~Mesh() {
    for (int e = 0; e < tot_elem_num; e++)
        delete elements[e].get_particles();
    delete[] elements;
    delete[] nodes;
    delete[] particles;
    elements = nullptr;
    nodes = nullptr;
    particles = nullptr;
}

void Mesh::imposeMPM_IC(float* vpo, float* epo, float* bpo) {
    for (int i = 0; i < this->tot_ptc_num; i++) {
        this->particles[i].set_velocity(&(vpo[i]));
        this->particles[i].set_strain(&(epo[i]));
        this->particles[i].set_bodyForce(&(bpo[i]));
    }
}

void Mesh::show_node() {
    for (int i = 0; i < tot_node_num; i++) {
        printf("n%d = %d", i, this->nodes[i].get_nid());
        printf("\n");
        this->nodes[i].get_xn().show();
    }
}