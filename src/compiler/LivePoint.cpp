#include "compiler/LivePoint.h"
#include "compiler/Variable.h"

namespace LL2W {
	bool LivePoint::isLiveIn(const VariablePtr &variable) const {
		if (liveIn.contains(variable)) {
			return true;
		}

		for (const VariablePtr &live_in: liveIn) {
			if (live_in->id == variable->id) {
				return true;
			}
		}

		return false;
	}

	bool LivePoint::isLiveOut(const VariablePtr &variable) const {
		if (liveOut.contains(variable)) {
			return true;
		}

		for (const VariablePtr &live_out: liveOut) {
			if (live_out->id == variable->id) {
				return true;
			}
		}

		return false;
	}

	bool LivePoint::isLive(const VariablePtr &variable) const {
		return liveIn.contains(variable) || liveOut.contains(variable);
	}

	void LivePoint::clearLive() {
		liveIn.clear();
		liveOut.clear();
		allLive.clear();
	}

	void LivePoint::eraseLive(const VariablePtr &variable) {
		if (0 < liveIn.erase(variable) + liveOut.erase(variable)) {
			allLive.erase(variable);
		}
	}

	bool LivePoint::insertLiveIn(VariablePtr variable) {
		if (liveIn.emplace(variable).second) {
			allLive.emplace(std::move(variable));
			return true;
		}

		return false;
	}

	bool LivePoint::insertLiveOut(VariablePtr variable) {
		if (liveOut.emplace(variable).second) {
			allLive.emplace(std::move(variable));
			return true;
		}

		return false;
	}
}
