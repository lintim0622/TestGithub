#include "calculate.h"
#include <iostream>

void Calculate::particle_info(Mesh& msh, Material& elastic, const float t) {
    int Np = msh.get_tot_ptc_num();
    for (int i = 0; i < Np; i++) {
        Particle* ip = msh.get_particle(i);
        ip->set_mass((float)(ip->get_rho() * ip->get_Volume() / Np));

        if (t == 0.0f) {
            float* st = elastic.get_D().dot(ip->get_strain());
            ip->set_stress(st);

            Tensor sst = ip->get_stress() / ip->get_rho();
            ip->set_specific_stress(&sst);

            Vector2D mp = ip->get_vp() * ip->get_mass();
            ip->set_momentum(&mp);
        }
    }
}