/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Mathias J. Krause
 *  E-mail contact: info@openlb.net
 *  The most recent release of OpenLB can be downloaded at
 *  <http://www.openlb.net/>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 */

/** \file
 * Statistics of a geometry represented by a superGeometry3D -- header file.
 */

#ifndef SUPER_GEOMETRY_STATISTICS_3D_H
#define SUPER_GEOMETRY_STATISTICS_3D_H

#include <vector>
#include <map>
#include <string>


//#include "superGeometry3D.h"
#include "io/ostreamManager.h"
#include "functors/analyticalF.h"

//#include "core/dataFields3D.h"

/// All OpenLB code is contained in this namespace.
namespace olb {

/// Reader for Nastran 3D voxel mesh files generated by HyperMesh
/** Doku A cuboid structure is given by a number of cuboids. To represent
 * a connected domain it is required that the distance between two
 * neighbooring cuboids is less than the smallest delta of them.
 *
 * WARNING:
 * At the moment there are only cuboids with a constant delta possible
 * and the distance between two neighbooring cuboids must be delta
 * since an interpolation operator in time and spance is missing in
 * cuboidNeigbourhood and superLattice.
 *
 * This class is not intended to be derived from.
 */

class SuperGeometry3D;

class SuperGeometryStatistics3D {

private:
  /// class specific cout
  mutable OstreamManager clout;

  /// Input file name
  SuperGeometry3D* _superGeometry;

  /// Number of voxels in each direction
  int _nX, _nY, _nZ;

  /// Size of ghost voxel layer
  int _offset;

  /// Spacing
  double _h;

  std::map<unsigned short, int> _material2n;
  std::map<unsigned short, std::vector<int> > _material2min;
  std::map<unsigned short, std::vector<int> > _material2max;

public:
  /// Constructor
  SuperGeometryStatistics3D() : clout(std::cout,"SuperGeometryStatistics3D") { };

  /// Constructor
  SuperGeometryStatistics3D(SuperGeometry3D* superGeometry)
    : clout(std::cout,"SuperGeometryStatistics3D") {
    reInit(superGeometry);
  }
  ;
  /// Destructor
  ~SuperGeometryStatistics3D() {
  }
  ;

  /// reinitializes the SuperGeometryStatistics (without checking the offset!!!!!!!)
  void reInit(SuperGeometry3D* superGeometry);

  void takeStatistics(int iX, int iY, int iZ);

  /// counts the number of voxels for the different boundary conditions (plus the number of inner and outer voxels)
  void countVoxel();

  /// returns normal that points into the fluid for paraxial surfaces
  std::vector<int> computeNormal(int iX, int iY, int iZ);
  std::vector<double> computeNormal (unsigned short material);

  /// returns discrete normal with norm maxNorm that points into the fluid for paraxial surfaces
  /// maxNorm=1.1 implies only normals parallel to the axises
  std::vector<int> computeDiscreteNormal (unsigned short material, double maxNorm = 1.1);

  /// returns the number of voxels for a boundary condition type
  int getNVoxel(int bcType);

  /// returns the number of voxels with material!=0
  int getNVoxel();

  std::vector<int> getMin(unsigned short material);

  std::vector<int> getMax(unsigned short material);

  std::vector<double> getPhysMinC(unsigned short material);
  std::vector<double> getPhysMaxC(unsigned short material);

  std::vector<double> getPhysRadius(unsigned short material);

  std::vector<double> getPhysCenterC(unsigned short material);

  std::vector<int> getNCo(unsigned short material);

  std::vector<int> getType(int iX, int iY, int iZ);

  std::vector<int> checkExtraBoundary(std::vector<int> discreteNormal,
                                      std::vector<int> discreteNormal2);

  void getBoundaryTypes();



  /// replace one material with another
  void regionGrowing(unsigned short material, int seedX, int seedY, int seedZ, int offsetX, int offsetY, int offsetZ, std::map<std::vector<int>, int >& tmp);


 


  /// Returns true if at (iX,iY,iZ) and in a neighbourhood of size (offsetX,offsetY,offsetZ) only voxels with material no material are there 
  bool check(unsigned short material, int iX, int iY, int iZ, unsigned offsetX, unsigned offsetY, unsigned offsetZ);

  bool find(unsigned short material, unsigned offsetX, unsigned offsetY, unsigned offsetZ, int& iX, int& iY, int& iZ);
  /// returns the SuperGeometry coordinates of one point
  /// belonging to a searchArea (given in physical units) that is of material material
   bool find(unsigned short material, AnalyticalF3D<bool,double>& searchArea, int& foundX, int& foundY, int& foundZ);

  SuperGeometry3D* getSuperGeometry();

};

} // namespace olb

#endif
