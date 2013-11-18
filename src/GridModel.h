#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <array>
//#include <armadillo>

//using namespace arma;

typedef int species_t;

struct ActiveBond
{
  double massBonded;
};

struct SpeciesCell
{
  public:
  std::map<glm::ivec2, std::map<species_t, ActiveBond>> activeBonds;
  glm::dvec2 velocity;
  double mass;

  inline SpeciesCell(): velocity(0,0), mass(0)  {}
};

struct Cell //I've never seen this done before, but in the interest of self-documentation you can't create ridiculous 5 dimensional matrices. My recent experience in academia & scientific computing may not be a good thing.
{
  std::map<species_t, SpeciesCell> species;
};

class GridModelListener
{
  public:
  virtual void cellStatusChanged(const glm::ivec2 cellLoc, const Cell& cell) =0;
};

class GridModel
{
  private:
  const glm::ivec2 dimensions;

  static std::vector<std::vector<Cell>> emptyCells; //c++ etc
  std::vector<std::vector<Cell>> cells;

  std::set<GridModelListener*> listeners;

  static Cell& getCell(std::vector<std::vector<Cell>>& cellCollection, const glm::ivec2 cellLoc);

  void notifyCellStatusChanged(const glm::ivec2 cellLoc, const Cell& cell);

  public:
  static std::array<std::array<double, 3>, 3>  massRedistribute(const glm::dvec2& deltaLoc);

  public:
  GridModel(const glm::ivec2 dimensions);

  void update(double deltaTime);

  void injectSpecies(const glm::ivec2 cellLoc, species_t species, const SpeciesCell& cellAdditional);
  void injectSpecies(const glm::ivec2 cellLoc, species_t species, double mass);

  void addListener(GridModelListener* listener);
  void removeListener(GridModelListener* listener);

  ~GridModel();
};