/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani, Jonas Latt
 *  Address: EPFL-STI-LIN Station 9, 1015 Lausanne
 *  E-mail: orestis.malaspinas@epfl.ch
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

#ifndef FORCED_SHAN_CHEN_COUPLING_POST_PROCESSOR_3D_H
#define FORCED_SHAN_CHEN_COUPLING_POST_PROCESSOR_3D_H

#include "core/spatiallyExtendedObject3D.h"
#include "core/postProcessing.h"
#include "core/blockLattice3D.h"


namespace olb {

/**
* Multiphysics class for coupling between different lattices.
*/

// =========================================================================//
// ===========Shan Chen coupling without wall interaction===================//
// =========================================================================//

template<typename T, template<typename U> class Lattice>
class ForcedShanChenCouplingPostProcessor3D : public LocalPostProcessor3D<T,Lattice> {
public:
  ForcedShanChenCouplingPostProcessor3D (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_, T G_, std::vector<T> rho0_,
    std::vector<SpatiallyExtendedObject3D*> partners_);
  virtual int extent() const { return 1; }
  virtual int extent(int whichDirection) const { return 1; }
  virtual void process(BlockLattice3D<T,Lattice>& blockLattice);
  virtual void processSubDomain(BlockLattice3D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
private:
  int x0, x1, y0, y1, z0, z1;
  T G;
  std::vector<T> rho0;
  std::vector<SpatiallyExtendedObject3D*> partners;
};

template<typename T, template<typename U> class Lattice>
class ForcedShanChenCouplingGenerator3D : public LatticeCouplingGenerator3D<T,Lattice> {
public:
  ForcedShanChenCouplingGenerator3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_, T G_, std::vector<T> rho0_);
  virtual PostProcessor3D<T,Lattice>* generate(std::vector<SpatiallyExtendedObject3D*> partners) const;
  virtual LatticeCouplingGenerator3D<T,Lattice>* clone() const;
private:
  T G;
  std::vector<T> rho0;
};

}

#endif
