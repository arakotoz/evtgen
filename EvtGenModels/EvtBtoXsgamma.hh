
/***********************************************************************
* Copyright 1998-2020 CERN for the benefit of the EvtGen authors       *
*                                                                      *
* This file is part of EvtGen.                                         *
*                                                                      *
* EvtGen is free software: you can redistribute it and/or modify       *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation, either version 3 of the License, or    *
* (at your option) any later version.                                  *
*                                                                      *
* EvtGen is distributed in the hope that it will be useful,            *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU General Public License for more details.                         *
*                                                                      *
* You should have received a copy of the GNU General Public License    *
* along with EvtGen.  If not, see <https://www.gnu.org/licenses/>.     *
***********************************************************************/

#ifndef EVTBTOXSGAMMA_HH
#define EVTBTOXSGAMMA_HH

#include "EvtGenBase/EvtDecayIncoherent.hh"

#include "EvtGenModels/EvtBtoXsgammaAbsModel.hh"

#include <memory>

class EvtParticle;

// Class to generate non-resonant two-body b->s,gamma decays.

class EvtBtoXsgamma : public EvtDecayIncoherent {
  public:
    std::string getName() override;

    EvtDecayBase* clone() override;

    void initProbMax() override;

    void init() override;

    void decay( EvtParticle* p ) override;

  private:
    std::unique_ptr<EvtBtoXsgammaAbsModel> _model;
};

#endif
