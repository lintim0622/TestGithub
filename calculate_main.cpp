/*#include "mesh.h"
#include "calculate.h"
#include <iostream>

int main() {
    // Grid Size
    float Unit_Grid = 0.25f;

    // dimension
    int dim = 2;

    // set material
    Material elastic(960.0f, 0.003E+9f, 0.0006E+9f);

    // set time
    float dt = 1e-4f;
    float et = 1e-4f;

    // verify time step
    elastic.verify_time_step(Unit_Grid, dt);

    // set particle and element
    float xp[16][2] = { {-4.68750e-01, -1.46875e+00}, {-4.68750e-01, -1.40625e+00},
                       {-4.68750e-01, -1.34375e+00}, {-4.68750e-01, -1.28125e+00},
                       {-4.06250e-01, -1.46875e+00}, {-4.06250e-01, -1.40625e+00},
                       {-4.06250e-01, -1.34375e+00}, {-4.06250e-01, -1.28125e+00},
                       {-3.43750e-01, -1.46875e+00}, {-3.43750e-01, -1.40625e+00},
                       {-3.43750e-01, -1.34375e+00}, {-3.43750e-01, -1.28125e+00},
                       {-2.81250e-01, -1.46875e+00}, {-2.81250e-01, -1.40625e+00},
                       {-2.81250e-01, -1.34375e+00}, {-2.81250e-01, -1.28125e+00} };
    float xn[4][2] = { {-0.5f,   -1.5f},
                      {-0.25f,  -1.5f},
                      {-0.5f,  -1.25f},
                      {-0.25f, -1.25f} };
    int nelem = 1;
    int tot_elem_num = (int)(nelem * nelem);

    int tot_node_num = 4;
    int tot_ptc_num = 16;

    Mesh msh(dim, &(xp[0][0]), &(xn[0][0]), nelem, Unit_Grid, tot_elem_num, tot_node_num, tot_ptc_num, elastic);
    
    // run mpm
    float t = 0.0f;
    Calculate cal;
    while (t <= et) {
        cal.particle_info(msh, elastic, t);
        t += dt;
    }
    std::cout << "Done!\n";
    return 0;
}
*/