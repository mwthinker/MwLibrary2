#ifndef MW_INITTTF_H
#define MW_INITTTF_H

namespace mw {

	class InitTtf {
	protected:
		InitTtf();
		~InitTtf();

		InitTtf(const InitTtf&);
		InitTtf& operator=(const InitTtf&);

	private:
		static int nbrOfInstances;
	};

} // Namespace mw.

#endif // MW_INITTTF_H
