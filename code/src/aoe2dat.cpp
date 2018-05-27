#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "genie/dat/DatFile.h"
using namespace std;

#define RES_FOOD 0
#define RES_WOOD 1
#define RES_STONE 2
#define RES_GOLD 3
#define ATK_PIERCE 3
#define ATK_MELEE 4
#define ARM_PIERCE 3
#define ARM_MELEE 4

int main() {
	ofstream myfile;
	myfile.open("units.json");

	cout << "Loading ./empires2_x2_p1.dat..." << endl;

	genie::DatFile *df = new genie::DatFile();
	df->setGameVersion(genie::GV_Cysion);
	df->load("empires2_x2_p1.dat");

	cout << "Extracting json data..." << endl;

	typedef genie::ResourceUsage<int16_t, int16_t, int16_t> ResourceStorage;
	typedef genie::ResourceUsage<int16_t, int16_t, int8_t> ResearchResourceCost;

	std::set<std::uint32_t> used;

	myfile << "{\"units_buildings\":" << endl;

	for (genie::Civ civ : df->Civs) {
		if (civ.Name != "Gaia") {
			continue;
		}
		myfile << "{" << endl;
		long unitsize = civ.Units.size();
		long unitctr = 0;
		for (genie::Unit unit : civ.Units) {
			unitctr++;
			if (used.find(unit.BaseID) != used.end()) {
				continue;
			} else {
				used.insert(unit.BaseID);
			}
			myfile << "\t\"" << unit.BaseID << "\" : {" << endl;
			myfile << "\t\t\"cost\": {" << endl;
			uint16_t wood = 0;
			uint16_t food = 0;
			uint16_t gold = 0;
			uint16_t stone = 0;
			for (ResourceStorage resourceStorage : unit.Creatable.ResourceCosts) {
				switch (resourceStorage.Type) {
				case RES_WOOD:
					wood = resourceStorage.Amount;
					break;
				case RES_FOOD:
					food = resourceStorage.Amount;
					break;
				case RES_GOLD:
					gold = resourceStorage.Amount;
					break;
				case RES_STONE:
					stone = resourceStorage.Amount;
					break;
				}
			}
			myfile << "\t\t\t\"wood\": " << wood << "," << endl;
			myfile << "\t\t\t\"food\": " << food << "," << endl;
			myfile << "\t\t\t\"gold\": " << gold << "," << endl;
			myfile << "\t\t\t\"stone\": " << stone << "" << endl;
			myfile << "\t\t}," << endl;
			myfile << "\t\t\"attack\":" << unit.Type50.DisplayedAttack << ","
					<< endl;
			myfile << "\t\t\"melee_armor\":" << unit.Type50.DisplayedMeleeArmour
					<< "," << endl;
			uint16_t pierce_armor = 0;
			for (genie::unit::AttackOrArmor armor : unit.Type50.Armours) {
				if (armor.Class == ARM_PIERCE) {
					pierce_armor = armor.Amount;
				}
			}
			myfile << "\t\t\"pierce_armor\":" << pierce_armor << "," << endl;
			myfile << "\t\t\"base_id\":" << unit.BaseID << "," << endl;
			myfile << "\t\t\"help_converter\":" << unit.LanguageDLLHelp - 79000
					<< "," << endl;
			myfile << "\t\t\"language_file_help\":" << unit.LanguageDLLHelp
					<< "," << endl;
			myfile << "\t\t\"name\":\"" << unit.Name << "\"," << endl;
			myfile << "\t\t\"hit_points\":" << unit.HitPoints << "," << endl;
			myfile << "\t\t\"line_of_sight\":" << unit.LineOfSight << ","
					<< endl;
			myfile << "\t\t\"garrison_capacity\":"
					<< (int16_t) unit.GarrisonCapacity << endl;
			myfile << "\t}";
			if (unitctr < unitsize) {
				myfile << ",";
			}
			myfile << endl;
		}
		myfile << "}," << endl;
	}

	myfile << "\"techs\":" << endl;
	myfile << "{" << endl;

	long techsize = df->Techs.size();
	long techctr = 0;
	for (genie::Tech tech : df->Techs) {
		myfile << "\t\"" << techctr << "\" : {" << endl;
		myfile << "\t\t\"cost\": {" << endl;
		uint16_t wood = 0;
		uint16_t food = 0;
		uint16_t gold = 0;
		uint16_t stone = 0;
		for (ResearchResourceCost resourceStorage : tech.ResourceCosts) {
			switch (resourceStorage.Type) {
			case RES_WOOD:
				wood = resourceStorage.Amount;
				break;
			case RES_FOOD:
				food = resourceStorage.Amount;
				break;
			case RES_GOLD:
				gold = resourceStorage.Amount;
				break;
			case RES_STONE:
				stone = resourceStorage.Amount;
				break;
			}
		}
		myfile << "\t\t\t\"wood\": " << wood << "," << endl;
		myfile << "\t\t\t\"food\": " << food << "," << endl;
		myfile << "\t\t\t\"gold\": " << gold << "," << endl;
		myfile << "\t\t\t\"stone\": " << stone << "" << endl;
		myfile << "\t\t}," << endl;
		myfile << "\t\t\"help_converter\":" << tech.LanguageDLLHelp - 79000
				<< "," << endl;
		myfile << "\t\t\"language_file_help\":" << tech.LanguageDLLHelp << ","
				<< endl;
		myfile << "\t\t\"name\":" << "\"" << tech.Name << "\"" << endl;
		myfile << "\t}";
		if (++techctr < techsize) {
			myfile << ",";
		}
		myfile << endl;
	}

	myfile << "}" << endl;
	myfile << "}" << endl;
	myfile.close();

	cout << "Done." << endl;

	return 0;
}
