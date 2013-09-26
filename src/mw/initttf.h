#ifndef MW_INITTTF_H
#define MW_INITTTF_H

namespace mw {

	class InitTtf {
	public:
		InitTtf();

		InitTtf(const InitTtf&);
		InitTtf& operator=(const InitTtf&);
	
	protected:
		~InitTtf();

	private:
		static int nbrOfInstances_;
	};

} // Namespace mw.

#endif // MW_INITTTF_H
