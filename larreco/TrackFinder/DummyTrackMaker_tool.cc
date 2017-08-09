#include "DummyTrackMaker.h"
#include "art/Utilities/ToolMacros.h"
#include "canvas/Persistency/Common/PtrVector.h"

bool trkmkr::DummyTrackMaker::makeTrack(const recob::TrackTrajectory& traj, const int tkID, const std::vector<art::Ptr<recob::Hit> >& inHits,
					recob::Track& outTrack, std::vector<art::Ptr<recob::Hit> >& outHits, OptionalOutputs& optionals,
					const art::Event& e) const {
  //
  outTrack = recob::Track(traj, -1, -1, -1, recob::tracking::SMatrixSym55(), recob::tracking::SMatrixSym55(), tkID);
  for (auto h : inHits) outHits.push_back(h);
  return true;
  //
}

DEFINE_ART_CLASS_TOOL(trkmkr::DummyTrackMaker)
