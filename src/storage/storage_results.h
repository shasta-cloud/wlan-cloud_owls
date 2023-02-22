//
// Created by stephane bourque on 2021-11-02.
//

#ifndef OWLS_STORAGE_RESULTS_H
#define OWLS_STORAGE_RESULTS_H

#include "RESTObjects/RESTAPI_OWLSobjects.h"
#include "framework/orm.h"

namespace OpenWifi {
	typedef Poco::Tuple<std::string, std::string, std::string, uint64_t, uint64_t, uint64_t,
						uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, std::string>
		SimulationResultsDBRecordType;

	class SimulationResultsDB
		: public ORM::DB<SimulationResultsDBRecordType, OWLSObjects::SimulationStatus> {
	  public:
		SimulationResultsDB(OpenWifi::DBType T, Poco::Data::SessionPool &P, Poco::Logger &L);
		virtual ~SimulationResultsDB(){};

	  private:
	};

} // namespace OpenWifi

#endif // OWLS_STORAGE_RESULTS_H
