#include <Force/ArchimedesPrinciple.h>

ArchimedesPrinciple::ArchimedesPrinciple(const Volume &v, const Fluid &f, double depth)
{
	z = f.GetDensity()*v.GetImmersedVolume(depth)*9.80665;
}
