/*
 * Hypothesis.h
 *
 *  Created on: 24 Oct 2015
 *      Author: hieu
 */
#pragma once

#include <iostream>
#include <cstddef>
#include "legacy/FFState.h"
#include "Scores.h"

namespace Moses2
{

class ManagerBase;
class Scores;

class HypothesisBase
{
public:
  virtual ~HypothesisBase()
  {
  }

  inline ManagerBase &GetManager() const
  {
    return *m_mgr;
  }

  const Scores &GetScores() const
  {
    return *m_scores;
  }

  const FFState *GetState(size_t ind) const
  {
    return m_ffStates[ind];
  }

  virtual size_t hash() const;
  virtual size_t hash(size_t seed) const;
  virtual bool operator==(const HypothesisBase &other) const;

  virtual SCORE GetFutureScore() const = 0;
  virtual void EvaluateWhenApplied() = 0;

protected:
  ManagerBase *m_mgr;
  Scores *m_scores;
  FFState **m_ffStates;

  HypothesisBase(MemPool &pool, const System &system);
};

////////////////////////////////////////////////////////////////////////////////////
class HypothesisFutureScoreOrderer
{
public:
  bool operator()(const HypothesisBase* a, const HypothesisBase* b) const
  {
    return a->GetFutureScore() > b->GetFutureScore();
  }
};

}
