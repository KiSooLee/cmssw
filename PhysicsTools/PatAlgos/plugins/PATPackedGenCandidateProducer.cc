#include <string>


#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Common/interface/Association.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "TrackingTools/IPTools/interface/IPTools.h" 
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalTrajectoryExtrapolatorToLine.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalImpactPointExtrapolator.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Matrix/Vector.h"
#include <string>


namespace pat {
    class PATPackedGenCandidateProducer : public edm::EDProducer {
        public:
            explicit PATPackedGenCandidateProducer(const edm::ParameterSet&);
            ~PATPackedGenCandidateProducer();

            virtual void produce(edm::Event&, const edm::EventSetup&);

        private:
            edm::EDGetTokenT<reco::GenParticleCollection>    Cands_;
            edm::EDGetTokenT<reco::VertexCollection>         PVs_;
            double maxEta_;
    };
}

pat::PATPackedGenCandidateProducer::PATPackedGenCandidateProducer(const edm::ParameterSet& iConfig) :
  Cands_(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("inputCollection"))),
  PVs_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("inputVertices"))),
  maxEta_(iConfig.getParameter<double>("maxEta"))
{
  produces< std::vector<pat::PackedGenParticle> > ();
}

pat::PATPackedGenCandidateProducer::~PATPackedGenCandidateProducer() {}

void pat::PATPackedGenCandidateProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {


    edm::Handle<reco::GenParticleCollection> cands;
    iEvent.getByToken( Cands_, cands );
    std::vector<reco::Candidate>::const_iterator cand;

    edm::Handle<reco::VertexCollection> PVs;
    iEvent.getByToken( PVs_, PVs );
    reco::VertexRef PV(PVs.id());
    math::XYZPoint  PVpos;
    if (!PVs->empty()) {
        PV = reco::VertexRef(PVs, 0);
        PVpos = PV->position();
    }

    std::auto_ptr< std::vector<pat::PackedGenParticle> > outPtrP( new std::vector<pat::PackedGenParticle> );


    for(unsigned int ic=0, nc = cands->size(); ic < nc; ++ic) {
        const reco::GenParticle &cand=(*cands)[ic];
	if(cand.status() ==1 && std::abs(cand.eta() < maxEta_))
        {
	        outPtrP->push_back( pat::PackedGenParticle(cand));
	}	
    }


    iEvent.put( outPtrP );


}


using pat::PATPackedGenCandidateProducer;
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(PATPackedGenCandidateProducer);
