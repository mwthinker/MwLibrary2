#ifndef MW_EXCEPTION_H
#define MW_EXCEPTION_H

#include <string>

namespace mw {

	struct Exception {
		inline Exception(std::string error_) : error(error_) {
		}

		const std::string error;
	};	

} // Namespace mw.

#endif // MW_EXCEPTION_H
