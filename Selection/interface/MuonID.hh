#ifndef MUON_IDS_HH
#define MUON_IDS_HH

#include "BaconAna/DataFormats/interface/TMuon.hh"

bool passMuonLoose(const baconhep::TMuon *muon);
bool passMuonTight(const baconhep::TMuon *muon);

//https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2 
bool passMuonLoose(const baconhep::TMuon *muon)
{

  if(!(muon->typeBits & baconhep::EMuType::kGlobal) && !(muon->typeBits & baconhep::EMuType::kTracker)) return kFALSE;
  if(!(muon->typeBits & baconhep::EMuType::kPFMuon)) return kFALSE;
  
  // PF-isolation with Delta-beta correction
  double iso = muon->chHadIso + TMath::Max(muon->neuHadIso + muon->gammaIso - 0.5*(muon->puIso), double(0));
  if(iso >= 0.25*(muon->pt)) return false;
  
  return true;
}

//https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2 
bool passMuonTight(const baconhep::TMuon *muon)
{

  if(muon->nTkLayers  < 6)            return kFALSE;
  if(muon->nPixHits   < 1)            return kFALSE;
  if(fabs(muon->d0)   > 0.2)          return kFALSE;
  if(fabs(muon->dz)   > 0.5)          return kFALSE;
  if(muon->muNchi2    > 10)           return kFALSE;
  if(muon->nMatchStn  < 2)            return kFALSE;
  if(muon->nValidHits < 1)            return kFALSE;
  if(!(muon->typeBits & baconhep::EMuType::kGlobal)) return kFALSE;
  if(!(muon->typeBits & baconhep::EMuType::kPFMuon)) return kFALSE;
  
  // PF-isolation with Delta-beta correction
  double iso = muon->chHadIso + TMath::Max(muon->neuHadIso + muon->gammaIso - 0.5*(muon->puIso), double(0));
  if(iso >= 0.15*(muon->pt)) return false;
  return true;
}

#endif
