import FWCore.ParameterSet.Config as cms

from SimGeneral.HepPDTESSource.pythiapdt_cfi import *

# The Geometries
#from FastSimulation.Configuration.Geometries_cff import *

#The Magnetic Field ESProducer's
from FastSimulation.ParticlePropagator.MagneticFieldMapESProducer_cfi import *

# The muon tracker trajectory, to be fit without rechit refit
from RecoMuon.GlobalTrackingTools.GlobalTrajectoryBuilderCommon_cff import GlobalTrajectoryBuilderCommon
GlobalTrajectoryBuilderCommon.TrackerRecHitBuilder = 'WithoutRefit'
GlobalTrajectoryBuilderCommon.TrackTransformer.TrackerRecHitBuilder = 'WithoutRefit'

# ECAL severity
from RecoLocalCalo.EcalRecAlgos.EcalSeverityLevelESProducer_cfi import *

# This flag is to switch between GEN-level and SIM/RECO-level pileup mixing

MixingMode = 'GenMixing' # GEN-level <---- DEFAULT
#MixingMode = 'DigiRecoMixing' # SIM/RECO-level; can be used only if CaloMode==3
