#ifndef TOJSON_TOJSON_H_
#define TOJSON_TOJSON_H_


#include "genie/dat/DatFile.h"

// dat
void datfile2json(std::ofstream& out, genie::DatFile* datFile);
void effect2json(std::ofstream& out, genie::Effect effect);
void effectcommand2json(std::ofstream& out, genie::EffectCommand effectCommand);
void civ2json(std::ofstream& out, genie::Civ civ);
void research2json(std::ofstream& out, genie::Tech tech); // genie::Tech
void unit2json(std::ofstream& out, genie::Unit unit);
void task2json(std::ofstream& out, genie::Task task);
void playercolour2json(std::ofstream& out, genie::PlayerColour pc);
void graphic2json(std::ofstream& out, genie::Graphic graphic);
void graphicdelta2json(std::ofstream& out, genie::GraphicDelta graphicDelta);
void graphicanglesound2json(std::ofstream& out, genie::GraphicAngleSound graphicAngleSound);
void terrainblock2json(std::ofstream& out, genie::TerrainBlock terrainblock);
void terrain2json(std::ofstream& out, genie::Terrain terrain);
void techtree2json(std::ofstream& out, genie::TechTree techtree);
void techtreeage2json(std::ofstream& out, genie::TechTreeAge techtreeage);
void buildingconnection2json(std::ofstream& out,
		genie::BuildingConnection buildingconnection);
void unitconnection2json(std::ofstream& out, genie::UnitConnection techtreeage);
void researchconnection2json(std::ofstream& out,
		genie::ResearchConnection techtreeage);
void common2json(std::ofstream& out, genie::techtree::Common common);
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



#endif /* TOJSON_TOJSON_H_ */
