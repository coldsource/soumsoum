#include <Force/ArchimedesPrinciple.h>

ArchimedesPrinciple::ArchimedesPrinciple(const Volume &v, const Fluid &f)
{
	z = f.GetDensity()*v.GetImmersedVolume()*9.80665;
}
