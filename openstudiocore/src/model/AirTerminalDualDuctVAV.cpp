/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "AirTerminalDualDuctVAV.hpp"
#include "AirTerminalDualDuctVAV_Impl.hpp"
#include "AirLoopHVAC.hpp"
#include "AirLoopHVAC_Impl.hpp"
#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "Model.hpp"
#include "Model_Impl.hpp"
#include "Node.hpp"
#include "Node_Impl.hpp"
#include "DesignSpecificationOutdoorAir.hpp"
#include "DesignSpecificationOutdoorAir_Impl.hpp"
#include "ScheduleTypeLimits.hpp"
#include "ScheduleTypeRegistry.hpp"
#include <utilities/idd/OS_AirTerminal_DualDuct_VAV_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include "../utilities/units/Unit.hpp"
#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

namespace detail {

  AirTerminalDualDuctVAV_Impl::AirTerminalDualDuctVAV_Impl(const IdfObject& idfObject,
                                                           Model_Impl* model,
                                                           bool keepHandle)
    : Mixer_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == AirTerminalDualDuctVAV::iddObjectType());
  }

  AirTerminalDualDuctVAV_Impl::AirTerminalDualDuctVAV_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                           Model_Impl* model,
                                                           bool keepHandle)
    : Mixer_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == AirTerminalDualDuctVAV::iddObjectType());
  }

  AirTerminalDualDuctVAV_Impl::AirTerminalDualDuctVAV_Impl(const AirTerminalDualDuctVAV_Impl& other,
                                                           Model_Impl* model,
                                                           bool keepHandle)
    : Mixer_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& AirTerminalDualDuctVAV_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType AirTerminalDualDuctVAV_Impl::iddObjectType() const {
    return AirTerminalDualDuctVAV::iddObjectType();
  }

  std::vector<ScheduleTypeKey> AirTerminalDualDuctVAV_Impl::getScheduleTypeKeys(const Schedule& schedule) const
  {
    std::vector<ScheduleTypeKey> result;
    UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
    UnsignedVector::const_iterator b(fieldIndices.begin()), e(fieldIndices.end());
    if (std::find(b,e,OS_AirTerminal_DualDuct_VAVFields::AvailabilitySchedule) != e)
    {
      result.push_back(ScheduleTypeKey("AirTerminalDualDuctVAV","Availability Schedule"));
    }
    return result;
  }

  boost::optional<Schedule> AirTerminalDualDuctVAV_Impl::availabilitySchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_AirTerminal_DualDuct_VAVFields::AvailabilitySchedule);
  }

  boost::optional<double> AirTerminalDualDuctVAV_Impl::maximumDamperAirFlowRate() const {
    return getDouble(OS_AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate,true);
  }

  bool AirTerminalDualDuctVAV_Impl::isMaximumDamperAirFlowRateAutosized() const {
    bool result = false;
    boost::optional<std::string> value = getString(OS_AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, true);
    if (value) {
      result = openstudio::istringEqual(value.get(), "autosize");
    }
    return result;
  }

  double AirTerminalDualDuctVAV_Impl::zoneMinimumAirFlowFraction() const {
    boost::optional<double> value = getDouble(OS_AirTerminal_DualDuct_VAVFields::ZoneMinimumAirFlowFraction,true);
    OS_ASSERT(value);
    return value.get();
  }

  boost::optional<DesignSpecificationOutdoorAir> AirTerminalDualDuctVAV_Impl::designSpecificationOutdoorAirObject() const {
    return getObject<ModelObject>().getModelObjectTarget<DesignSpecificationOutdoorAir>(OS_AirTerminal_DualDuct_VAVFields::DesignSpecificationOutdoorAirObject);
  }

  bool AirTerminalDualDuctVAV_Impl::setAvailabilitySchedule(Schedule& schedule) {
    bool result = setSchedule(OS_AirTerminal_DualDuct_VAVFields::AvailabilitySchedule,
                              "AirTerminalDualDuctVAV",
                              "Availability Schedule",
                              schedule);
    return result;
  }

  void AirTerminalDualDuctVAV_Impl::resetAvailabilitySchedule() {
    bool result = setString(OS_AirTerminal_DualDuct_VAVFields::AvailabilitySchedule, "");
    OS_ASSERT(result);
  }

  bool AirTerminalDualDuctVAV_Impl::setMaximumDamperAirFlowRate(boost::optional<double> maximumDamperAirFlowRate) {
    bool result(false);
    if (maximumDamperAirFlowRate) {
      result = setDouble(OS_AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, maximumDamperAirFlowRate.get());
    }
    return result;
  }

  void AirTerminalDualDuctVAV_Impl::autosizeMaximumDamperAirFlowRate() {
    bool result = setString(OS_AirTerminal_DualDuct_VAVFields::MaximumDamperAirFlowRate, "autosize");
    OS_ASSERT(result);
  }

  bool AirTerminalDualDuctVAV_Impl::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
    bool result = setDouble(OS_AirTerminal_DualDuct_VAVFields::ZoneMinimumAirFlowFraction, zoneMinimumAirFlowFraction);
    return result;
  }

  bool AirTerminalDualDuctVAV_Impl::setDesignSpecificationOutdoorAirObject(const boost::optional<DesignSpecificationOutdoorAir>& designSpecificationOutdoorAir) {
    bool result(false);
    if (designSpecificationOutdoorAir) {
      result = setPointer(OS_AirTerminal_DualDuct_VAVFields::DesignSpecificationOutdoorAirObject, designSpecificationOutdoorAir.get().handle());
    }
    else {
      resetDesignSpecificationOutdoorAirObject();
      result = true;
    }
    return result;
  }

  void AirTerminalDualDuctVAV_Impl::resetDesignSpecificationOutdoorAirObject() {
    bool result = setString(OS_AirTerminal_DualDuct_VAVFields::DesignSpecificationOutdoorAirObject, "");
    OS_ASSERT(result);
  }

  unsigned AirTerminalDualDuctVAV_Impl::outletPort() const {
    return OS_AirTerminal_DualDuct_VAVFields::AirOutletNode;
  }

  unsigned AirTerminalDualDuctVAV_Impl::inletPort(unsigned branchIndex) const {
    if( branchIndex == 0 ) {
      return OS_AirTerminal_DualDuct_VAVFields::HotAirInletNode;
    } else if( branchIndex == 1 ) {
      return OS_AirTerminal_DualDuct_VAVFields::ColdAirInletNode;
    } else {
      LOG(Warn, "Calling inletPort with branchIndex greater than 1 for " << briefDescription() << " is not valid.");
      LOG(Warn, briefDescription() << " has only two branches.");
      return std::numeric_limits<unsigned>::max();
    }
  }

  unsigned AirTerminalDualDuctVAV_Impl::nextInletPort() const {
    LOG(Warn, "nextInletPort is not supported for " << briefDescription() << " .");
    LOG(Warn, "Ports cannot be added or removed for " << briefDescription() << " .");
    return std::numeric_limits<unsigned>::max();
  }

  unsigned AirTerminalDualDuctVAV_Impl::newInletPortAfterBranch(unsigned branchIndex) {
    LOG(Warn, "newInletPortAfterBranch is not supported for " << briefDescription() << " .");
    LOG(Warn, "Ports cannot be added or removed for " << briefDescription() << " .");
    return std::numeric_limits<unsigned>::max();
  }

  void AirTerminalDualDuctVAV_Impl::removePortForBranch(unsigned branchIndex) {
    LOG(Warn, "removePortForBranch is not supported for " << briefDescription() << " .");
    LOG(Warn, "Ports cannot be added or removed for " << briefDescription() << " .");
  }

  boost::optional<Node> AirTerminalDualDuctVAV_Impl::hotAirInletNode() const {
    boost::optional<Node> node;
    if( auto mo = inletModelObject(0) ) {
      node = mo->optionalCast<Node>();
      OS_ASSERT(node);
    }
    return node;
  }

  boost::optional<Node> AirTerminalDualDuctVAV_Impl::coldAirInletNode() const {
    boost::optional<Node> node;
    if( auto mo = inletModelObject(1) ) {
      node = mo->optionalCast<Node>();
      OS_ASSERT(node);
    }
    return node;
  }

  std::vector<IdfObject> AirTerminalDualDuctVAV_Impl::remove() {
    auto modelObject = getObject<AirTerminalDualDuctVAV>();
    AirLoopHVAC_Impl::removeDualDuctTerminalFromAirLoopHVAC(modelObject,inletPort(0),inletPort(1),outletPort());
    return Mixer_Impl::remove();
  }

  bool AirTerminalDualDuctVAV_Impl::addToNode(Node & node)
  {
    auto mo = getObject<AirTerminalDualDuctVAV>();
    return AirLoopHVAC_Impl::addDualDuctTerminalToNode(mo,inletPort(0),inletPort(1),outletPort(),node);
  }

  ModelObject AirTerminalDualDuctVAV_Impl::clone(Model model) const
  {
    auto t_clone = Mixer_Impl::clone(model).cast<AirTerminalDualDuctVAV>();

    t_clone.setString(OS_AirTerminal_DualDuct_VAVFields::HotAirInletNode,"");
    t_clone.setString(OS_AirTerminal_DualDuct_VAVFields::ColdAirInletNode,"");
    t_clone.setString(OS_AirTerminal_DualDuct_VAVFields::AirOutletNode,"");

    return t_clone;
  }

} // detail

AirTerminalDualDuctVAV::AirTerminalDualDuctVAV(const Model& model)
  : Mixer(AirTerminalDualDuctVAV::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::AirTerminalDualDuctVAV_Impl>());

  autosizeMaximumDamperAirFlowRate();
  setZoneMinimumAirFlowFraction(0.3);
}

IddObjectType AirTerminalDualDuctVAV::iddObjectType() {
  return IddObjectType(IddObjectType::OS_AirTerminal_DualDuct_VAV);
}

boost::optional<Schedule> AirTerminalDualDuctVAV::availabilitySchedule() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->availabilitySchedule();
}

boost::optional<double> AirTerminalDualDuctVAV::maximumDamperAirFlowRate() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->maximumDamperAirFlowRate();
}

bool AirTerminalDualDuctVAV::isMaximumDamperAirFlowRateAutosized() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->isMaximumDamperAirFlowRateAutosized();
}

double AirTerminalDualDuctVAV::zoneMinimumAirFlowFraction() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->zoneMinimumAirFlowFraction();
}

boost::optional<DesignSpecificationOutdoorAir> AirTerminalDualDuctVAV::designSpecificationOutdoorAirObject() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->designSpecificationOutdoorAirObject();
}

bool AirTerminalDualDuctVAV::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setAvailabilitySchedule(schedule);
}

void AirTerminalDualDuctVAV::resetAvailabilitySchedule() {
  getImpl<detail::AirTerminalDualDuctVAV_Impl>()->resetAvailabilitySchedule();
}

bool AirTerminalDualDuctVAV::setMaximumDamperAirFlowRate(double maximumDamperAirFlowRate) {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setMaximumDamperAirFlowRate(maximumDamperAirFlowRate);
}

void AirTerminalDualDuctVAV::autosizeMaximumDamperAirFlowRate() {
  getImpl<detail::AirTerminalDualDuctVAV_Impl>()->autosizeMaximumDamperAirFlowRate();
}

bool AirTerminalDualDuctVAV::setZoneMinimumAirFlowFraction(double zoneMinimumAirFlowFraction) {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setZoneMinimumAirFlowFraction(zoneMinimumAirFlowFraction);
}

bool AirTerminalDualDuctVAV::setDesignSpecificationOutdoorAirObject(const DesignSpecificationOutdoorAir& designSpecificationOutdoorAir) {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->setDesignSpecificationOutdoorAirObject(designSpecificationOutdoorAir);
}

boost::optional<Node> AirTerminalDualDuctVAV::hotAirInletNode() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->hotAirInletNode();
}

boost::optional<Node> AirTerminalDualDuctVAV::coldAirInletNode() const {
  return getImpl<detail::AirTerminalDualDuctVAV_Impl>()->coldAirInletNode();
}

void AirTerminalDualDuctVAV::resetDesignSpecificationOutdoorAirObject() {
  getImpl<detail::AirTerminalDualDuctVAV_Impl>()->resetDesignSpecificationOutdoorAirObject();
}

/// @cond
AirTerminalDualDuctVAV::AirTerminalDualDuctVAV(std::shared_ptr<detail::AirTerminalDualDuctVAV_Impl> impl)
  : Mixer(impl)
{}
/// @endcond

} // model
} // openstudio

