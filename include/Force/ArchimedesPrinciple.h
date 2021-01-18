#ifndef _ARCHIMEDESPRINCIPLE_H_
#define _ARCHIMEDESPRINCIPLE_H_

#include <Vector/Vector3D.h>
#include <Fluid/Volume.h>
#include <Fluid/Fluid.h>

class ArchimedesPrinciple: public Vector3D
{
public:
	ArchimedesPrinciple(const Volume &v, const Fluid &f);
};

#endif
