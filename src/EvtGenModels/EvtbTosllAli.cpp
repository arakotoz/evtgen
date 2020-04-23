
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

#include "EvtGenModels/EvtbTosllAli.hh"

#include "EvtGenBase/EvtGenKine.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtReport.hh"

#include "EvtGenModels/EvtbTosllAliFF.hh"
#include "EvtGenModels/EvtbTosllAmp.hh"
#include "EvtGenModels/EvtbTosllScalarAmp.hh"
#include "EvtGenModels/EvtbTosllVectorAmp.hh"

#include <stdlib.h>
#include <string>
using std::endl;

std::string EvtbTosllAli::getName()
{
    return "BTOSLLALI";
}

EvtDecayBase* EvtbTosllAli::clone()
{
    return new EvtbTosllAli;
}

void EvtbTosllAli::decay( EvtParticle* p )
{
    setWeight( p->initializePhaseSpace( getNDaug(), getDaugs(), false,
                                        _poleSize, 1, 2 ) );

    _calcamp->CalcAmp( p, _amp2, _aliffmodel.get() );
}

void EvtbTosllAli::initProbMax()
{
    EvtId parnum, mesnum, l1num, l2num;

    parnum = getParentId();
    mesnum = getDaug( 0 );
    l1num = getDaug( 1 );
    l2num = getDaug( 2 );

    //This routine sets the _poleSize.
    double mymaxprob = _calcamp->CalcMaxProb( parnum, mesnum, l1num, l2num,
                                              _aliffmodel.get(), _poleSize );

    setProbMax( mymaxprob );
}

void EvtbTosllAli::init()
{
    checkNArg( 0 );
    checkNDaug( 3 );

    //We expect the parent to be a scalar
    //and the daughters to be X lepton+ lepton-

    checkSpinParent( EvtSpinType::SCALAR );

    EvtSpinType::spintype mesontype = EvtPDL::getSpinType( getDaug( 0 ) );

    if ( !( mesontype == EvtSpinType::VECTOR ||
            mesontype == EvtSpinType::SCALAR ) ) {
        EvtGenReport( EVTGEN_ERROR, "EvtGen" )
            << "EvtbTosllAli generator expected "
            << " a SCALAR or VECTOR 1st daughter, found:"
            << EvtPDL::name( getDaug( 0 ) ).c_str() << endl;
        EvtGenReport( EVTGEN_ERROR, "EvtGen" )
            << "Will terminate execution!" << endl;
        ::abort();
    }

    checkSpinDaughter( 1, EvtSpinType::DIRAC );
    checkSpinDaughter( 2, EvtSpinType::DIRAC );

    _aliffmodel = std::make_unique<EvtbTosllAliFF>();
    if ( mesontype == EvtSpinType::SCALAR ) {
        _calcamp = std::make_unique<EvtbTosllScalarAmp>();
    }
    if ( mesontype == EvtSpinType::VECTOR ) {
        _calcamp = std::make_unique<EvtbTosllVectorAmp>();
    }
}
