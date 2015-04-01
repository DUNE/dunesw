//--------------------------------------------------------------------
//
// SplitterAnalyzer to test SplitterInput source
//
//--------------------------------------------------------------------

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"

// lardata
#include "RawData/RawDigit.h"

// C++
#include <iostream>

namespace fhicl { class ParameterSet; }

namespace arttest {

  using rawDigits_t = std::vector<raw::RawDigit>;

  class SplitterAnalyzer : public art::EDAnalyzer {
  public:

    explicit SplitterAnalyzer( fhicl::ParameterSet const& pset) :
      art::EDAnalyzer(pset),
      inputTag_("SplitterInput:TPC")
    {}

    virtual ~SplitterAnalyzer(){}

    virtual void analyze( art::Event const & e  ) override { 

      auto rawDigitH = e.getValidHandle<rawDigits_t>( inputTag_ );
      std::cout << "analyzing event: " << e.id() << " : " << rawDigitH->size() << " digits present" << std::endl;
      std::cout << "====" << std::endl;

    }

  private:
    art::InputTag inputTag_;

  };  // SplitterAnalyzer

}

DEFINE_ART_MODULE(arttest::SplitterAnalyzer)
