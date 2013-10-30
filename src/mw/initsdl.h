#ifndef MW_INITSDL_H
#define MW_INITSDL_H

namespace mw {

	class InitSdl {
	protected:
		InitSdl();
		~InitSdl();
		
		InitSdl(const InitSdl&) = delete;
		InitSdl& operator=(const InitSdl&) = delete;

	private:
		static int nbrOfInstances_;
	};

} // Namespace mw.

#endif // MW_INITSDL_H
