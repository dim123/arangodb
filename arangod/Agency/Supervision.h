////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Kaveh Vahedipour
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_CONSENSUS_SUPERVISION_H
#define ARANGOD_CONSENSUS_SUPERVISION_H 1

#include "Basics/Thread.h"
#include "Basics/ConditionVariable.h"

namespace arangodb {
namespace consensus {

class Agent;
class Node;
class Store;

struct check_t {
  bool good;
  std::string name;
  check_t (std::string const& n, bool g) : good(g), name(n) {}
};

class Supervision : public arangodb::Thread {
  
public:
  
  /// @brief Construct sanity checking
  Supervision ();
  
  /// @brief Default dtor
  ~Supervision ();
  
  /// @brief Start thread
  bool start ();

  /// @brief Start thread with access to agent
  bool start (Agent*);

  /// @brief Run woker
  void run() override final;
  
  /// @brief Begin thread shutdown
  void beginShutdown() override final;

  /// @brief Wake up to task
  void wakeUp ();

private:

  /// @Brief Check mahines under path in agency
  std::vector<check_t> check (Node const& node, std::string const& path) const;

  /// @brief Read db
  Store const& store () const;

  /// @brief Perform sanity checking
  bool doChecks(bool);
  
  Agent* _agent; /**< @brief My agent */

  arangodb::basics::ConditionVariable _cv; /**< @brief Control if thread
                                              should run */

  long _frequency;

  
};

}}

#endif
