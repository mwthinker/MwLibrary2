#ifndef MW_INITTTF_H
#define MW_INITTTF_H

namespace mw {

	class InitTtf {
	protected:
		InitTtf();
		~InitTtf();

		InitTtf(const InitTtf&) = delete;
		InitTtf& operator=(const InitTtf&) = delete;

	private:
		static int nbrOfInstances_;
	};

} // Namespace mw.

#endif // MW_INITTTF_H
