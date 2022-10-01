#ifndef CALCULATE_H_
#define CALCULATE_H_

#include "mesh.h"

class Calculate {
public:
    void particle_info(Mesh& msh, Material& elastic, const float t);
};

#endif // !CALCULATE_H_


/*
class Calculate(object):

    @staticmethod
    def particle_info(msh, elastic, t):
        Np = msh.tot_ptc_num # len(msh.particles)
        for ip in msh.particles:
            ip.mass = ip.rho*ip.Volume/Np

            if (t == 0.0):
                ip.stress = (elastic.D).dot(ip.strain)
                ip.specific_stress = ip.stress/ip.rho

            ip.momentum[0] = ip.mass*ip.velocity[0]
            ip.momentum[1] = ip.mass*ip.velocity[1]
*/
