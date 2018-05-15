// ====================================================================== 
// \title  MissingFile.cpp
// \author Rob Bocchino
// \brief  MissingFile implementation
//
// \copyright
// Copyright (C) 2018 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws and
// regulations.  By accepting this document, the user agrees to comply
// with all U.S. export laws and regulations.  User has the
// responsibility to obtain export licenses, or other export authority
// as may be required before exporting such information to foreign
// countries or providing access to foreign persons.
// ====================================================================== 

#include "Svc/CmdSequencer/test/ut/SequenceFiles/AMPCS/AMPCS.hpp"
#include "Svc/CmdSequencer/test/ut/SequenceFiles/MissingFile.hpp"
#include "gtest/gtest.h"

namespace Svc {

  namespace SequenceFiles {

    MissingFile ::
      MissingFile(const Format::t format) :
        File("missing", format)
    {

    }

    void MissingFile ::
      serializeAMPCS(Fw::SerializeBufferBase& buffer)
    {
      // CRC
      AMPCS::CRCs::createFile(buffer, this->getName().toChar());
    }

  }


}

