#include <Submarine/Weighing.h>
#include <Submarine/Submarine.h>

using nlohmann::json;

Weighing::Weighing()
{
	update_resolution = 1;
}

void Weighing::HandleCommand(const nlohmann::json &j)
{
}

json Weighing::ToJson() const
{
	json j;
	
	j["reference_mass"] = submarine->GetReferenceMass();
	j["reference_net_mass"] = submarine->GetReferenceNetMass();
	j["current_mass"] = submarine->GetMass();
	j["current_net_mass"] = submarine->GetMass() - submarine->GetBallast().GetMass();
	j["mass_centering"] = submarine->GetMassCentering();
	
	return j;
}
