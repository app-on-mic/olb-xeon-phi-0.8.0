/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Jonas Latt
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

#include "boundaryCondition3D.h"
#include "boundaryCondition3D.hh"
#include "momentaOnBoundaries.h"
#include "momentaOnBoundaries.hh"
#include "momentaOnBoundaries3D.h"
#include "momentaOnBoundaries3D.hh"
#include "latticeDescriptors.h"
#include "latticeDescriptors.hh"

namespace olb {

template class
BoundaryConditionInstantiator3D
<
double, descriptors::D3Q19Descriptor,
        RegularizedBoundaryManager3D < double, descriptors::D3Q19Descriptor,
        RLBdynamics<double,descriptors::D3Q19Descriptor> >
        >;

template OnLatticeBoundaryCondition3D<double,descriptors::D3Q19Descriptor>*
createLocalBoundaryCondition3D < double,descriptors::D3Q19Descriptor,
                               RLBdynamics<double,descriptors::D3Q19Descriptor> >
                               (
                                 BlockStructure3D<double,descriptors::D3Q19Descriptor>& block
                               );

template OnLatticeBoundaryCondition3D<double,descriptors::D3Q19Descriptor>*
createLocalBoundaryCondition3D < double,descriptors::D3Q19Descriptor,
                               BGKdynamics<double,descriptors::D3Q19Descriptor> >
                               (
                                 BlockStructure3D<double,descriptors::D3Q19Descriptor>& block
                               );

template class
BoundaryConditionInstantiator3D
<
double, descriptors::D3Q19Descriptor,
        InterpolationBoundaryManager3D < double, descriptors::D3Q19Descriptor,
        BGKdynamics<double,descriptors::D3Q19Descriptor> >
        >;

template OnLatticeBoundaryCondition3D<double,descriptors::D3Q19Descriptor>*
createInterpBoundaryCondition3D < double,descriptors::D3Q19Descriptor,
                                BGKdynamics<double,descriptors::D3Q19Descriptor> >
                                (
                                  BlockStructure3D<double,descriptors::D3Q19Descriptor>& block
                                );
}
