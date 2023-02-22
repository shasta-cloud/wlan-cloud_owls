//
// Created by stephane bourque on 2021-11-03.
//

#pragma once

#include <chrono>
#include <random>

#include "RESTObjects/RESTAPI_OWLSobjects.h"
#include "Simulator.h"
#include "framework/SubSystemServer.h"
#include "nlohmann/json-schema.hpp"

namespace OpenWifi {

	struct SimThread {
		Poco::Thread Thread;
		Simulator Sim;
		SimThread(uint Index, std::string SerialBase, uint NumClients, Poco::Logger &L)
			: Sim(Index, std::move(SerialBase), NumClients, L){};
	};

	class SimulationCoordinator : public SubSystemServer, Poco::Runnable {
	  public:
		static SimulationCoordinator *instance() {
			static auto *instance_ = new SimulationCoordinator;
			return instance_;
		}

		int Start() final;
		void Stop() final;
		void run() final;

		bool StartSim(const std::string &SimId, std::string &Id, std::string &Error,
					  const std::string &Owner);
		bool StopSim(const std::string &Id, std::string &Error);
		bool CancelSim(const std::string &Id, std::string &Error);

		[[nodiscard]] inline const OWLSObjects::SimulationDetails &GetSimulationInfo() {
			return CurrentSim_;
		}

		[[nodiscard]] inline const std::string &GetCasLocation() { return CASLocation_; }
		[[nodiscard]] inline const std::string &GetCertFileName() { return CertFileName_; }
		[[nodiscard]] inline const std::string &GetKeyFileName() { return KeyFileName_; }
		[[nodiscard]] inline const std::string &GetRootCAFileName() { return RootCAFileName_; }
		[[nodiscard]] inline int GetLevel() const { return Level_; }
		[[nodiscard]] const nlohmann::json &GetSimCapabilities() { return DefaultCapabilities_; }
		[[nodiscard]] nlohmann::json GetSimConfiguration(uint64_t uuid);

	  private:
		Poco::Thread Worker_;
		std::atomic_bool Running_ = false;
		std::atomic_bool SimRunning_ = false;
		std::vector<std::unique_ptr<SimThread>> SimThreads_;
		OWLSObjects::SimulationDetails CurrentSim_;
		std::string CASLocation_;
		std::string CertFileName_;
		std::string KeyFileName_;
		std::string RootCAFileName_;
		nlohmann::json DefaultCapabilities_;
		int Level_ = 0;

		SimulationCoordinator() noexcept
			: SubSystemServer("SimulationCoordinator", "SIM-COORDINATOR", "coordinator") {}

		void StartSimulators();
		void StopSimulators();
		void CancelSimulators();
	};

	inline SimulationCoordinator *SimulationCoordinator() {
		return SimulationCoordinator::instance();
	}
} // namespace OpenWifi
