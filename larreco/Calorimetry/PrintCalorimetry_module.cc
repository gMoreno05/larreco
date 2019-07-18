////////////////////////////////////////////////////////////////////////
// Class:       PrintCalorimetry
// Module Type: analyzer
// File:        PrintCalorimetry_module.cc
//
// Generated at Wed Oct 29 10:26:38 2014 by Wesley Ketchum using artmod
// from cetpkgsupport v1_07_01.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "fhiclcpp/ParameterSet.h"

#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/AnalysisBase/Calorimetry.h"

namespace calo{
  class PrintCalorimetry;
}

class calo::PrintCalorimetry : public art::EDAnalyzer {
public:
  explicit PrintCalorimetry(fhicl::ParameterSet const & p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  PrintCalorimetry(PrintCalorimetry const &) = delete;
  PrintCalorimetry(PrintCalorimetry &&) = delete;
  PrintCalorimetry & operator = (PrintCalorimetry const &) = delete;
  PrintCalorimetry & operator = (PrintCalorimetry &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;

  // Selected optional functions.
  void reconfigure(fhicl::ParameterSet const & p) ;

private:

  std::string              fTrackModuleLabel;
  std::vector<std::string> fCaloModuleLabels;

};


calo::PrintCalorimetry::PrintCalorimetry(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p),
  fTrackModuleLabel(p.get<std::string>("TrackModuleLabel")),
  fCaloModuleLabels(p.get< std::vector<std::string> >("CaloModuleLabels"))
{}

void calo::PrintCalorimetry::analyze(art::Event const & e)
{
  art::Handle< std::vector<recob::Track> > trackHandle;
  e.getByLabel(fTrackModuleLabel,trackHandle);

  std::vector< art::FindManyP<anab::Calorimetry> > caloAssnVector;//(fCaloModuleLabels.size());

  for(size_t i_cm=0; i_cm<fCaloModuleLabels.size(); i_cm++)
    caloAssnVector.emplace_back(trackHandle,e,fCaloModuleLabels[i_cm]);

  for(size_t i_trk=0; i_trk<trackHandle->size(); i_trk++){
    std::cout << "(Run,Event,Track) = (" << e.run() << "," << e.event() << "," << i_trk << ")" << std::endl;
    std::cout << "-------------------" << std::endl;

    for(size_t i_cm=0; i_cm<caloAssnVector.size(); i_cm++){
      std::cout << "Calorimetry module " << i_cm << std::endl;
      for(auto const& caloptr : caloAssnVector[i_cm].at(i_trk))
	std::cout << *caloptr << std::endl;
    }

  }

}

void calo::PrintCalorimetry::reconfigure(fhicl::ParameterSet const & p)
{
  fTrackModuleLabel = p.get<std::string>("TrackModuleLabel");
  fCaloModuleLabels = p.get< std::vector<std::string> >("CaloModuleLabels");
}

DEFINE_ART_MODULE(calo::PrintCalorimetry)
