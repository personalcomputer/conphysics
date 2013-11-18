#include <cmath>
#include <iostream>

#include "GridModel.h"

const double gravitationalConstant = 9.81;

const int iterations = 1;

std::vector<std::vector<Cell>> GridModel::emptyCells;

GridModel::GridModel(const glm::ivec2 dimensions):
  dimensions(dimensions)
{
  Cell emptyCell;
  std::vector<Cell> cellColumn;
  cellColumn.assign(dimensions.y, emptyCell);
  emptyCells.assign(dimensions.x, cellColumn);

  cells = emptyCells;
}

void GridModel::notifyCellStatusChanged(const glm::ivec2 cellLoc, const Cell& cell)
{
  for(auto listener: listeners)
  {
    listener->cellStatusChanged(cellLoc, cell);
  }
}

std::array<std::array<double, 3>, 3> GridModel::massRedistribute(const glm::dvec2& deltaLoc) //returns array w/ % distribution. boost::multi_array syntax is a joke.
{
  std::array<std::array<double, 3>, 3> neighbors;// = new double[3][3];

  //Ok, the more rigorous framing is that all this is is brownian motion + deltaLoc.
  //PDF is defined based on the delta time (to provide dispersion) and the already calculated delta movement.
  //Find the volume of the area under the PDF for each nearby cell, done.
  //Note, this isn't what the code below does, the code below doesn't calculate dispersion except for "dispersion" incurred by quanitzation error

  //Code below works on the idea that the area of a square offset from the old cell according the deltaLoc that intersects with the given cell is the new mass for that cell.

  //memset(neighbors, 0, 33);
  std::array<double, 3> blankRow;
  blankRow.fill(0);
  neighbors.fill(blankRow);

  neighbors[1][1] = (1-glm::abs(deltaLoc.y))*(1-glm::abs(deltaLoc.x)); //"idle mass"

  if(deltaLoc.y > 0 && deltaLoc.x > 0)
    neighbors[2][0] = glm::abs(deltaLoc.x)*glm::abs(deltaLoc.y);
  if(deltaLoc.y > 0 && deltaLoc.x < 0)
    neighbors[0][0] = glm::abs(deltaLoc.x)*glm::abs(deltaLoc.y);
  if(deltaLoc.y < 0 && deltaLoc.x > 0)
    neighbors[2][2] = glm::abs(deltaLoc.x)*glm::abs(deltaLoc.y);
  if(deltaLoc.y < 0 && deltaLoc.x < 0)
    neighbors[0][2] = glm::abs(deltaLoc.x)*glm::abs(deltaLoc.y);

  if(deltaLoc.x > 0)
    neighbors[2][1] = (1-glm::abs(deltaLoc.y))*glm::abs(deltaLoc.x);
  if(deltaLoc.x < 0)
    neighbors[0][1] = (1-glm::abs(deltaLoc.y))*glm::abs(deltaLoc.x);

  if(deltaLoc.y > 0)
    neighbors[1][2] = (1-glm::abs(deltaLoc.x))*glm::abs(deltaLoc.y);
  if(deltaLoc.y < 0)
    neighbors[1][0] = (1-glm::abs(deltaLoc.x))*glm::abs(deltaLoc.y);

  return neighbors;
}

void GridModel::update(double deltaTime)
{
  for(int iteration = 0; iteration < iterations; iteration++)
  {
    auto oldCells = cells;
    cells = emptyCells;

    glm::ivec2 cellLoc;
    for(cellLoc.x = 0; cellLoc.x < dimensions.x; cellLoc.x++)
    {
      for(cellLoc.y = 0; cellLoc.y < dimensions.y; cellLoc.y++)
      {
        std::map<species_t, SpeciesCell>& cellSpecies = oldCells[cellLoc.x][cellLoc.y].species;
        for(std::map<species_t, SpeciesCell>::iterator speciesCellPair = cellSpecies.begin(); speciesCellPair != cellSpecies.end(); ++speciesCellPair)
        {
          SpeciesCell speciesCell = speciesCellPair->second;
          species_t speciesType = speciesCellPair->first;

          if(iteration == 0) //Apply forces
          {
            if(speciesCell.mass != 0)
            {
              glm::dvec2 netForce(0, 0);
              netForce.y += -(gravitationalConstant*speciesCell.mass);

              //Missing: core pressure code
              //Missing: attraction code

              glm::dvec2 acceleration = netForce/speciesCell.mass;
              speciesCell.velocity += acceleration*deltaTime;

              //Re-distribute mass according to velocity
              glm::dvec2 deltaLoc = speciesCell.velocity*deltaTime;
              deltaLoc.x = glm::clamp(deltaLoc.x, -1.0, 1.0);
              deltaLoc.y = glm::clamp(deltaLoc.y, -1.0, 1.0);

              //std::cout << deltaLoc.y << std::endl;

              double totalMass = speciesCell.mass;
              speciesCell.mass = 0; //Is set again by massRedistribute below.

              std::array<std::array<double, 3>, 3> neighborNewMass = massRedistribute(deltaLoc);
              glm::ivec2 neighborIterator;
              for(neighborIterator.x = 0; neighborIterator.x < 3; neighborIterator.x++)
              {
                for(neighborIterator.y = 0; neighborIterator.y < 3; neighborIterator.y++)
                {
                  glm::ivec2 neighborRelative = neighborIterator;
                  neighborRelative.x = neighborRelative.x-1;
                  neighborRelative.y = neighborRelative.y-1;
                  glm::ivec2 neighborLoc = cellLoc+neighborRelative;
                  if(neighborLoc.x < 0 || neighborLoc.y < 0 || neighborLoc.x >= dimensions.x || neighborLoc.y >= dimensions.y)
                    continue;

                  double newMass = totalMass*neighborNewMass[neighborIterator.x][neighborIterator.y];

                  SpeciesCell neighborAdditional = speciesCell;
                  neighborAdditional.mass = totalMass*neighborNewMass[neighborIterator.x][neighborIterator.y];

                  injectSpecies(neighborLoc, speciesType, neighborAdditional);
                }
              }
              //Missing: diffusion code (minor importance)
            }
          }
        }
      }
    }
  }

  glm::ivec2 cellLoc;
  for(cellLoc.x = 0; cellLoc.x < dimensions.x; cellLoc.x++)
  {
    for(cellLoc.y = 0; cellLoc.y < dimensions.y; cellLoc.y++)
    {
      notifyCellStatusChanged(cellLoc, getCell(cells, cellLoc));
    }
  }
}

Cell& GridModel::getCell(std::vector<std::vector<Cell>>& cellCollection, const glm::ivec2 cellLoc)
{
  return cellCollection[cellLoc.x][cellLoc.y];
}

void GridModel::injectSpecies(const glm::ivec2 cellLoc, species_t species, const SpeciesCell& cellAdditional)
{
  if(cellAdditional.mass == 0)
    return;

  SpeciesCell& cell = getCell(cells, cellLoc).species[species];

  double newVsOldRatio = cellAdditional.mass/(cellAdditional.mass+cell.mass);

  cell.mass += cellAdditional.mass;
  cell.velocity += newVsOldRatio*cellAdditional.velocity;
}

void GridModel::injectSpecies(const glm::ivec2 cellLoc, species_t species, double mass)
{
  SpeciesCell cellAdditional;
  cellAdditional.mass = mass;
  injectSpecies(cellLoc, species, cellAdditional);
}

void GridModel::addListener(GridModelListener* listener)
{
  listeners.insert(listener);
}

void GridModel::removeListener(GridModelListener* listener)
{
  listeners.erase(listener);
}

GridModel::~GridModel()
{
}