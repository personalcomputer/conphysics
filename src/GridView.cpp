#include "GridView.h"

const double maxMass = 60.0;

const glm::vec3 green(0.0, 1.0, 0.0);

GridView::GridView(GLFWPixelDisplay* const pixelDisplay):
  pixelDisplay(pixelDisplay)
{

}

GridView::~GridView()
{
}

void GridView::cellStatusChanged(const glm::ivec2 cellLoc, const Cell& cell)
{
  //Fix coordinates for render
  glm::ivec2 renderLoc = cellLoc;
  //renderLoc.y = pixelDisplay->getResolution().y-renderLoc.y;

  //Calculate color
  double totalMass = 0;
  for(auto speciesCellPair: cell.species)
  {
    SpeciesCell speciesCell = speciesCellPair.second;
    //species_t speciesType = speciesCellPair.first;

    totalMass += speciesCell.mass;
  }

  glm::vec3 color = glm::vec3(1.0,1.0,1.0)*float(totalMass/maxMass);

  if(totalMass >= maxMass)
    color = glm::vec3(1.0,1.0,1.0);

  //Send to display
  pixelDisplay->setPixel(renderLoc, color);
}