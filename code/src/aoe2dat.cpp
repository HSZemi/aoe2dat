#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "genie/dat/DatFile.h"
#include <boost/algorithm/string/join.hpp>
using namespace std;

#define RES_FOOD 0
#define RES_WOOD 1
#define RES_STONE 2
#define RES_GOLD 3
#define ATK_PIERCE 3
#define ATK_MELEE 4
#define ARM_PIERCE 3
#define ARM_MELEE 4

// dat
void datfile2json(std::ofstream& out, genie::DatFile* datFile);
void civ2json(std::ofstream& out, genie::Civ civ);
void research2json(std::ofstream& out, genie::Tech tech); // genie::Tech
void unit2json(std::ofstream& out, genie::Unit unit);
void task2json(std::ofstream& out, genie::Task task);
// unit
void attackorarmor2json(std::ofstream& out,
		genie::unit::AttackOrArmor attackOrArmor);
void type502json(std::ofstream& out, genie::unit::Type50 type50);
void projectile2json(std::ofstream& out, genie::unit::Projectile projectile);
void building2json(std::ofstream& out, genie::unit::Building building);
void creatable2json(std::ofstream& out, genie::unit::Creatable creatable);
void bird2json(std::ofstream& out, genie::unit::Bird bird);
void deadfish2json(std::ofstream& out, genie::unit::DeadFish deadFish);
// helper
template<typename T> std::string join2string(std::vector<T> numbers);
typedef genie::ResourceUsage<int16_t, int16_t, int8_t> ResearchResourceCost;
typedef genie::ResourceUsage<int16_t, float, int8_t> ResourceStorage;
typedef genie::ResourceUsage<int16_t, int16_t, int16_t> ResourceCost;

int main() {
	ofstream myfile;
	ofstream jayson;
	myfile.open("units_buildings_techs.json");
	jayson.open("jayson.json");

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

	datfile2json(jayson, df);

	jayson.close();

	cout << "Done." << endl;

	return 0;
}

void datfile2json(std::ofstream& out, genie::DatFile* datFile) {
	out << "{" << endl;
	out << "\"Civs\":[" << endl;
	long civsize = datFile->Civs.size();
	long civcount = 0;
	for (genie::Civ civ : datFile->Civs) {
		civ2json(out, civ);
		if (++civcount < civsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"Techs\":[" << endl;
	long techsize = datFile->Techs.size();
	long techcount = 0;
	for (genie::Tech tech : datFile->Techs) {
		research2json(out, tech);
		if (++techcount < techsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]" << endl;
	out << "}" << endl;
}

void civ2json(std::ofstream& out, genie::Civ civ) {
	out << "{" << endl;
	out << "\"PlayerType\":" << std::to_string(civ.PlayerType) << "," << endl;
	out << "\"Name\":\"" << civ.Name << "\"," << endl;
	out << "\"Name2\":\"" << civ.Name2 << "\"," << endl;
	out << "\"TechTreeID\":" << civ.TechTreeID << "," << endl;
	out << "\"TeamBonusID\":" << civ.TeamBonusID << "," << endl;
	out << "\"Resources\":[" << join2string<float>(civ.Resources) << "],"
			<< endl;
	out << "\"IconSet\":" << std::to_string(civ.IconSet) << "," << endl;
	out << "\"UnitPointers\":[" << join2string<int32_t>(civ.UnitPointers)
			<< "]," << endl;
	out << "\"Units\":[" << endl;
	long unitssize = civ.Units.size();
	long unitscount = 0;
	for (genie::Unit unit : civ.Units) {
		unit2json(out, unit);
		if (++unitscount < unitssize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"UniqueUnitsTechs\":["
			<< join2string<int16_t>(civ.UniqueUnitsTechs) << "]" << endl;
	out << "}";
}

void unit2json(std::ofstream& out, genie::Unit unit) {
	out << "{" << endl;
	out << "\"Type\":" << std::to_string(unit.Type) << "," << endl;
	out << "\"ID\":" << unit.ID << "," << endl;
	out << "\"LanguageDLLName\":" << unit.LanguageDLLName << "," << endl;
	out << "\"LanguageDLLCreation\":" << unit.LanguageDLLCreation << ","
			<< endl;
	out << "\"Class\":" << unit.Class << "," << endl;
	out << "\"StandingGraphic\":[" << unit.StandingGraphic.first << ","
			<< unit.StandingGraphic.second << "]," << endl;
	out << "\"DyingGraphic\":" << unit.DyingGraphic << "," << endl;
	out << "\"UndeadGraphic\":" << unit.UndeadGraphic << "," << endl;
	out << "\"UndeadMode\":" << std::to_string(unit.UndeadMode) << "," << endl;
	out << "\"HitPoints\":" << unit.HitPoints << "," << endl;
	out << "\"LineOfSight\":" << unit.LineOfSight << "," << endl;
	out << "\"GarrisonCapacity\":" << std::to_string(unit.GarrisonCapacity)
			<< "," << endl;
	out << "\"CollisionSize\":" << "{\"x\":" << unit.CollisionSize.x
			<< ",\"y\":" << unit.CollisionSize.y << ",\"z\":"
			<< unit.CollisionSize.z << "}," << endl;
	out << "\"TrainSound\":" << unit.TrainSound << "," << endl;
	out << "\"DamageSound\":" << unit.DamageSound << "," << endl;
	out << "\"DeadUnitID\":" << unit.DeadUnitID << "," << endl;
	out << "\"BloodUnitID\":" << unit.BloodUnitID << "," << endl;
	out << "\"SortNumber\":" << std::to_string(unit.SortNumber) << "," << endl;
	out << "\"CanBeBuiltOn\":" << std::to_string(unit.CanBeBuiltOn) << ","
			<< endl;
	out << "\"IconID\":" << unit.IconID << "," << endl;
	out << "\"HideInEditor\":" << std::to_string(unit.HideInEditor) << ","
			<< endl;
	out << "\"OldPortraitPict\":" << unit.OldPortraitPict << "," << endl;
	out << "\"Enabled\":" << std::to_string(unit.Enabled) << "," << endl;
	out << "\"Disabled\":" << std::to_string(unit.Disabled) << "," << endl;
	out << "\"PlacementSideTerrain\":[" << unit.PlacementSideTerrain.first
			<< "," << unit.PlacementSideTerrain.second << "]," << endl;
	out << "\"PlacementTerrain\":[" << unit.PlacementTerrain.first << ","
			<< unit.PlacementTerrain.second << "]," << endl;
	out << "\"ClearanceSize\":[" << unit.ClearanceSize.first << ","
			<< unit.ClearanceSize.second << "]," << endl;
	out << "\"HillMode\":" << std::to_string(unit.HillMode) << "," << endl;
	out << "\"FogVisibility\":" << std::to_string(unit.FogVisibility) << ","
			<< endl;
	out << "\"TerrainRestriction\":" << unit.TerrainRestriction << "," << endl;
	out << "\"FlyMode\":" << std::to_string(unit.FlyMode) << "," << endl;
	out << "\"ResourceCapacity\":" << unit.ResourceCapacity << "," << endl;
	out << "\"ResourceDecay\":" << unit.ResourceDecay << "," << endl;
	out << "\"BlastDefenseLevel\":" << std::to_string(unit.BlastDefenseLevel)
			<< "," << endl;
	out << "\"CombatLevel\":" << std::to_string(unit.CombatLevel) << ","
			<< endl;
	out << "\"InteractionMode\":" << std::to_string(unit.InteractionMode) << ","
			<< endl;
	out << "\"MinimapMode\":" << std::to_string(unit.MinimapMode) << ","
			<< endl;
	out << "\"InterfaceKind\":" << std::to_string(unit.InterfaceKind) << ","
			<< endl;
	out << "\"MultipleAttributeMode\":" << unit.MultipleAttributeMode << ","
			<< endl;
	out << "\"MinimapColor\":" << std::to_string(unit.MinimapColor) << ","
			<< endl;
	out << "\"LanguageDLLHelp\":" << unit.LanguageDLLHelp << "," << endl;
	out << "\"LanguageDLLHotKeyText\":" << unit.LanguageDLLHotKeyText << ","
			<< endl;
	out << "\"HotKey\":" << unit.HotKey << "," << endl;
	out << "\"Recyclable\":" << std::to_string(unit.Recyclable) << "," << endl;
	out << "\"EnableAutoGather\":" << std::to_string(unit.EnableAutoGather)
			<< "," << endl;
	out << "\"CreateDoppelgangerOnDeath\":"
			<< std::to_string(unit.CreateDoppelgangerOnDeath) << "," << endl;
	out << "\"ResourceGatherGroup\":"
			<< std::to_string(unit.ResourceGatherGroup) << "," << endl;
	out << "\"OcclusionMode\":" << std::to_string(unit.OcclusionMode) << ","
			<< endl;
	out << "\"ObstructionType\":" << std::to_string(unit.ObstructionType) << ","
			<< endl;
	out << "\"ObstructionClass\":" << std::to_string(unit.ObstructionClass)
			<< "," << endl;
	out << "\"Trait\":" << std::to_string(unit.Trait) << "," << endl;
	out << "\"Civilization\":" << std::to_string(unit.Civilization) << ","
			<< endl;
	out << "\"Nothing\":" << unit.Nothing << "," << endl;
	out << "\"SelectionEffect\":" << std::to_string(unit.SelectionEffect) << ","
			<< endl;
	out << "\"EditorSelectionColour\":"
			<< std::to_string(unit.EditorSelectionColour) << "," << endl;
	out << "\"OutlineSize\":" << "{\"x\":" << unit.OutlineSize.x << ",\"y\":"
			<< unit.OutlineSize.y << ",\"z\":" << unit.OutlineSize.z << "},"
			<< endl;
	out << "\"ResourceStorages\":[" << endl;
	long rssize = unit.ResourceStorages.size();
	long rscount = 0;
	for (ResourceStorage rs : unit.ResourceStorages) {
		out << "{\"Type\":" << rs.Type << ",\"Amount\":" << rs.Amount
				<< ",\"Flag\":" << std::to_string(rs.Flag) << "}";
		if (++rscount < rssize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"DamageGraphics\":[" << endl;
	long dgsize = unit.DamageGraphics.size();
	long dgcount = 0;
	for (genie::unit::DamageGraphic dg : unit.DamageGraphics) {
		out << "{" << endl;
		out << "\"GraphicID\":" << dg.GraphicID << "," << endl;
		out << "\"DamagePercent\":" << std::to_string(dg.DamagePercent) << ","
				<< endl;
		out << "\"OldApplyMode\":" << std::to_string(dg.OldApplyMode) << ","
				<< endl;
		out << "\"ApplyMode\":" << std::to_string(dg.ApplyMode) << endl;
		out << "}";
		if (++dgcount < dgsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"SelectionSound\":" << unit.SelectionSound << "," << endl;
	out << "\"DyingSound\":" << unit.DyingSound << "," << endl;
	out << "\"OldAttackReaction\":" << std::to_string(unit.OldAttackReaction)
			<< "," << endl;
	out << "\"ConvertTerrain\":" << std::to_string(unit.ConvertTerrain) << ","
			<< endl;
	out << "\"Name\":\"" << unit.Name << "\"," << endl;
	out << "\"Name2\":\"" << unit.Name2 << "\"," << endl;
	out << "\"Unitline\":" << unit.Unitline << "," << endl;
	out << "\"MinTechLevel\":" << std::to_string(unit.MinTechLevel) << ","
			<< endl;
	out << "\"CopyID\":" << unit.CopyID << "," << endl;
	out << "\"BaseID\":" << unit.BaseID << "," << endl;
	out << "\"TelemetryID\":" << unit.TelemetryID << "," << endl;
	out << "\"Speed\":" << unit.Speed << "," << endl;
	out << "\"DeadFish\":";
	deadfish2json(out, unit.DeadFish);
	out << "," << endl;
	out << "\"Bird\":";
	bird2json(out, unit.Bird);
	out << "," << endl;
	out << "\"Type50\":";
	type502json(out, unit.Type50);
	out << "," << endl;
	out << "\"Projectile\":";
	projectile2json(out, unit.Projectile);
	out << "," << endl;
	out << "\"Creatable\":";
	creatable2json(out, unit.Creatable);
	out << "," << endl;
	out << "\"Building\":";
	building2json(out, unit.Building);
	out << endl;
	out << "}";
}

void deadfish2json(std::ofstream& out, genie::unit::DeadFish deadFish) {
	out << "{" << endl;
	out << "\"WalkingGraphic\":" << deadFish.WalkingGraphic << "," << endl;
	out << "\"RunningGraphic\":" << deadFish.RunningGraphic << "," << endl;
	out << "\"RotationSpeed\":" << deadFish.RotationSpeed << "," << endl;
	out << "\"OldSizeClass\":" << std::to_string(deadFish.OldSizeClass) << ","
			<< endl;
	out << "\"TrackingUnit\":" << deadFish.TrackingUnit << "," << endl;
	out << "\"TrackingUnitMode\":" << std::to_string(deadFish.TrackingUnitMode)
			<< "," << endl;
	out << "\"TrackingUnitDensity\":" << deadFish.TrackingUnitDensity << ","
			<< endl;
	out << "\"OldMoveAlgorithm\":" << std::to_string(deadFish.OldMoveAlgorithm)
			<< "," << endl;
	out << "\"TurnRadius\":" << deadFish.TurnRadius << "," << endl;
	out << "\"TurnRadiusSpeed\":" << deadFish.TurnRadiusSpeed << "," << endl;
	out << "\"MaxYawPerSecondMoving\":" << deadFish.MaxYawPerSecondMoving << ","
			<< endl;
	out << "\"StationaryYawRevolutionTime\":"
			<< deadFish.StationaryYawRevolutionTime << "," << endl;
	out << "\"MaxYawPerSecondStationary\":"
			<< deadFish.MaxYawPerSecondStationary << endl;
	out << "}";
}

void task2json(std::ofstream& out, genie::Task task) {
	out << "{" << endl;
	out << "\"TaskType\":" << task.TaskType << "," << endl;
	out << "\"ID\":" << task.ID << "," << endl;
	out << "\"IsDefault\":" << std::to_string(task.IsDefault) << "," << endl;
	out << "\"ActionType\":" << task.ActionType << "," << endl;
	out << "\"ClassID\":" << task.ClassID << "," << endl;
	out << "\"UnitID\":" << task.UnitID << "," << endl;
	out << "\"TerrainID\":" << task.TerrainID << "," << endl;
	out << "\"ResourceIn\":" << task.ResourceIn << "," << endl;
	out << "\"ResourceMultiplier\":" << task.ResourceMultiplier << "," << endl;
	out << "\"ResourceOut\":" << task.ResourceOut << "," << endl;
	out << "\"UnusedResource\":" << task.UnusedResource << "," << endl;
	out << "\"WorkValue1\":" << task.WorkValue1 << "," << endl;
	out << "\"WorkValue2\":" << task.WorkValue2 << "," << endl;
	out << "\"WorkRange\":" << task.WorkRange << "," << endl;
	out << "\"AutoSearchTargets\":" << std::to_string(task.AutoSearchTargets)
			<< "," << endl;
	out << "\"SearchWaitTime\":" << task.SearchWaitTime << "," << endl;
	out << "\"EnableTargeting\":" << std::to_string(task.EnableTargeting) << ","
			<< endl;
	out << "\"CombatLevelFlag\":" << std::to_string(task.CombatLevelFlag) << ","
			<< endl;
	out << "\"GatherType\":" << task.GatherType << "," << endl;
	out << "\"WorkFlag2\":" << task.WorkFlag2 << "," << endl;
	out << "\"TargetDiplomacy\":" << std::to_string(task.TargetDiplomacy) << ","
			<< endl;
	out << "\"CarryCheck\":" << std::to_string(task.CarryCheck) << "," << endl;
	out << "\"PickForConstruction\":"
			<< std::to_string(task.PickForConstruction) << "," << endl;
	out << "\"MovingGraphicID\":" << task.MovingGraphicID << "," << endl;
	out << "\"ProceedingGraphicID\":" << task.ProceedingGraphicID << ","
			<< endl;
	out << "\"WorkingGraphicID\":" << task.WorkingGraphicID << "," << endl;
	out << "\"CarryingGraphicID\":" << task.CarryingGraphicID << "," << endl;
	out << "\"ResourceGatheringSoundID\":" << task.ResourceGatheringSoundID
			<< "," << endl;
	out << "\"ResourceDepositSoundID\":" << task.ResourceDepositSoundID << endl;
	out << "}";
}

void bird2json(std::ofstream& out, genie::unit::Bird bird) {
	out << "{" << endl;
	out << "\"DefaultTaskID\":" << bird.DefaultTaskID << "," << endl;
	out << "\"SearchRadius\":" << bird.SearchRadius << "," << endl;
	out << "\"WorkRate\":" << bird.WorkRate << "," << endl;
	out << "\"DropSite\":[" << bird.DropSite.first << ","
			<< bird.DropSite.second << "]," << endl;
	out << "\"TaskSwapGroup\":" << std::to_string(bird.TaskSwapGroup) << ","
			<< endl;
	out << "\"AttackSound\":" << bird.AttackSound << "," << endl;
	out << "\"MoveSound\":" << bird.MoveSound << "," << endl;
	out << "\"RunPattern\":" << std::to_string(bird.RunPattern) << "," << endl;
	out << "\"TaskList\":[";
	long tsize = bird.TaskList.size();
	long tcount = 0;
	for (genie::Task task : bird.TaskList) {
		task2json(out, task);
		if (++tcount < tsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]" << endl;
	out << "}";

}

void creatable2json(std::ofstream& out, genie::unit::Creatable creatable) {
	out << "{" << endl;
	out << "\"ResourceCosts\":[" << endl;
	long rcsize = creatable.ResourceCosts.size();
	long rccount = 0;
	for (ResourceCost rc : creatable.ResourceCosts) {
		out << "{\"Type\":" << rc.Type << ",\"Amount\":" << rc.Amount
				<< ",\"Flag\":" << rc.Flag << "}";
		if (++rccount < rcsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"TrainTime\":" << creatable.TrainTime << "," << endl;
	out << "\"TrainLocationID\":" << creatable.TrainLocationID << "," << endl;
	out << "\"ButtonID\":" << std::to_string(creatable.ButtonID) << "," << endl;
	out << "\"RearAttackModifier\":" << creatable.RearAttackModifier << ","
			<< endl;
	out << "\"FlankAttackModifier\":" << creatable.FlankAttackModifier << ","
			<< endl;
	out << "\"CreatableType\":" << std::to_string(creatable.CreatableType)
			<< "," << endl;
	out << "\"HeroMode\":" << std::to_string(creatable.HeroMode) << "," << endl;
	out << "\"GarrisonGraphic\":" << creatable.GarrisonGraphic << "," << endl;
	out << "\"TotalProjectiles\":" << creatable.TotalProjectiles << "," << endl;
	out << "\"MaxTotalProjectiles\":"
			<< std::to_string(creatable.MaxTotalProjectiles) << "," << endl;
	out << "\"ProjectileSpawningArea\":["
			<< join2string<float>(creatable.ProjectileSpawningArea) << "],"
			<< endl;
	out << "\"SecondaryProjectileUnit\":" << creatable.SecondaryProjectileUnit
			<< "," << endl;
	out << "\"SpecialGraphic\":" << creatable.SpecialGraphic << "," << endl;
	out << "\"SpecialAbility\":" << std::to_string(creatable.SpecialAbility)
			<< "," << endl;
	out << "\"DisplayedPierceArmour\":" << creatable.DisplayedPierceArmour
			<< endl;
	out << "}";
}

void building2json(std::ofstream& out, genie::unit::Building building) {
	out << "{" << endl;
	out << "\"ConstructionGraphicID\":" << building.ConstructionGraphicID << ","
			<< endl;
	out << "\"SnowGraphicID\":" << building.SnowGraphicID << "," << endl;
	out << "\"AdjacentMode\":" << std::to_string(building.AdjacentMode) << ","
			<< endl;
	out << "\"GraphicsAngle\":" << building.GraphicsAngle << "," << endl;
	out << "\"DisappearsWhenBuilt\":"
			<< std::to_string(building.DisappearsWhenBuilt) << "," << endl;
	out << "\"StackUnitID\":" << building.StackUnitID << "," << endl;
	out << "\"FoundationTerrainID\":" << building.FoundationTerrainID << ","
			<< endl;
	out << "\"OldOverlayID\":" << building.OldOverlayID << "," << endl;
	out << "\"TechID\":" << building.TechID << "," << endl;
	out << "\"CanBurn\":" << std::to_string(building.CanBurn) << "," << endl;
	out << "\"Annexes\": [" << endl;
	long axsize = building.Annexes.size();
	long axcount = 0;
	for (genie::unit::BuildingAnnex ax : building.Annexes) {
		out << "{\"UnitID\":" << ax.UnitID << ",\"Misplacement\":["
				<< ax.Misplacement.first << "," << ax.Misplacement.second
				<< "]}";
		if (++axcount < axsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"HeadUnit\":" << building.HeadUnit << "," << endl;
	out << "\"TransformUnit\":" << building.TransformUnit << "," << endl;
	out << "\"TransformSound\":" << building.TransformSound << "," << endl;
	out << "\"ConstructionSound\":" << building.ConstructionSound << ","
			<< endl;
	out << "\"GarrisonType\":" << std::to_string(building.GarrisonType) << ","
			<< endl;
	out << "\"GarrisonHealRate\":" << building.GarrisonHealRate << "," << endl;
	out << "\"GarrisonRepairRate\":" << building.GarrisonRepairRate << ","
			<< endl;
	out << "\"PileUnit\":" << building.PileUnit << endl;
	out << "}";
}

void projectile2json(std::ofstream& out, genie::unit::Projectile projectile) {
	out << "{" << endl;
	out << "\"ProjectileType\":" << std::to_string(projectile.ProjectileType)
			<< "," << endl;
	out << "\"SmartMode\":" << std::to_string(projectile.SmartMode) << ","
			<< endl;
	out << "\"HitMode\":" << std::to_string(projectile.HitMode) << "," << endl;
	out << "\"VanishMode\":" << std::to_string(projectile.VanishMode) << ","
			<< endl;
	out << "\"AreaEffectSpecials\":"
			<< std::to_string(projectile.AreaEffectSpecials) << "," << endl;
	out << "\"ProjectileArc\":" << std::to_string(projectile.ProjectileArc)
			<< endl;
	out << "}";
}

void type502json(std::ofstream& out, genie::unit::Type50 type50) {
	out << "{" << endl;
	out << "\"BaseArmor\":" << type50.BaseArmor << "," << endl;
	out << "\"Attacks\":[" << endl;
	long atsize = type50.Attacks.size();
	long atcount = 0;
	for (genie::unit::AttackOrArmor aoa : type50.Attacks) {
		out << "{\"Class\":" << aoa.Class << ",\"Amount\":" << aoa.Amount
				<< "}";
		if (++atcount < atsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"Armours\":[" << endl;
	long armsize = type50.Armours.size();
	long armcount = 0;
	for (genie::unit::AttackOrArmor aoa : type50.Armours) {
		out << "{\"Class\":" << aoa.Class << ",\"Amount\":" << aoa.Amount
				<< "}";
		if (++armcount < armsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"DefenseTerrainBonus\":" << type50.DefenseTerrainBonus << ","
			<< endl;
	out << "\"MaxRange\":" << type50.MaxRange << "," << endl;
	out << "\"BlastWidth\":" << type50.BlastWidth << "," << endl;
	out << "\"ReloadTime\":" << type50.ReloadTime << "," << endl;
	out << "\"ProjectileUnitID\":" << type50.ProjectileUnitID << "," << endl;
	out << "\"AccuracyPercent\":" << type50.AccuracyPercent << "," << endl;
	out << "\"BreakOffCombat\":" << std::to_string(type50.BreakOffCombat) << ","
			<< endl;
	out << "\"FrameDelay\":" << type50.FrameDelay << "," << endl;
	out << "\"GraphicDisplacement\":["
			<< join2string<float>(type50.GraphicDisplacement) << "]," << endl;
	out << "\"BlastAttackLevel\":" << std::to_string(type50.BlastAttackLevel)
			<< "," << endl;
	out << "\"MinRange\":" << type50.MinRange << "," << endl;
	out << "\"AccuracyDispersion\":" << type50.AccuracyDispersion << ","
			<< endl;
	out << "\"AttackGraphic\":" << type50.AttackGraphic << "," << endl;
	out << "\"DisplayedMeleeArmour\":" << type50.DisplayedMeleeArmour << ","
			<< endl;
	out << "\"DisplayedAttack\":" << type50.DisplayedAttack << "," << endl;
	out << "\"DisplayedRange\":" << type50.DisplayedRange << "," << endl;
	out << "\"DisplayedReloadTime\":" << type50.DisplayedReloadTime << endl;
	out << "}";

}

template<typename T>
std::string join2string(std::vector<T> numbers) {
	long nsize = numbers.size();
	long ncount = 0;
	std::string s = "";
	for (T i : numbers) {
		s += std::to_string(i);
		if (++ncount < nsize) {
			s += ",";
		}
	}
	return s;
}

void research2json(std::ofstream& out, genie::Tech tech) {
	out << "{" << endl;
	out << "\"RequiredTechs\":[";
	out << join2string<int16_t>(tech.RequiredTechs);
	out << "]," << endl;
	out << "\"ResourceCosts\":[" << endl;
	long rrcsize = tech.ResourceCosts.size();
	long rrccount = 0;
	for (ResearchResourceCost rrc : tech.ResourceCosts) {
		out << "{\"Type\":" << rrc.Type << ",\"Amount\":" << rrc.Amount
				<< ",\"Flag\":" << std::to_string(rrc.Flag) << "}";
		if (++rrccount < rrcsize) {
			out << ",";
		}
		out << endl;
	}
	out << "]," << endl;
	out << "\"RequiredTechCount\":" << tech.RequiredTechCount << "," << endl;
	out << "\"Civ\":" << tech.Civ << "," << endl;
	out << "\"FullTechMode\":" << tech.FullTechMode << "," << endl;
	out << "\"ResearchLocation\":" << tech.ResearchLocation << "," << endl;
	out << "\"LanguageDLLName\":" << tech.LanguageDLLName << "," << endl;
	out << "\"LanguageDLLDescription\":" << tech.LanguageDLLDescription << ","
			<< endl;
	out << "\"ResearchTime\":" << tech.ResearchTime << "," << endl;
	out << "\"EffectID\":" << tech.EffectID << "," << endl;
	out << "\"Type\":" << tech.Type << "," << endl;
	out << "\"IconID\":" << tech.IconID << "," << endl;
	out << "\"ButtonID\":" << std::to_string(tech.ButtonID) << "," << endl;
	out << "\"LanguageDLLHelp\":" << tech.LanguageDLLHelp << "," << endl;
	out << "\"LanguageDLLTechTree\":" << tech.LanguageDLLTechTree << ","
			<< endl;
	out << "\"HotKey\":" << tech.HotKey << "," << endl;
	out << "\"Name\":\"" << tech.Name << "\"," << endl;
	out << "\"Name2\":\"" << tech.Name2 << "\"" << endl;
	out << "}";
}

