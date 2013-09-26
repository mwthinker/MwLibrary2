#ifndef MW_INITSDL_H
#define MW_INITSDL_H

namespace mw {

	class InitSdl {
	public:
		InitSdl();
		
		InitSdl(const InitSdl&);
		InitSdl& operator=(const InitSdl&);
	
	protected:
		~InitSdl();

	private:
		static int nbrOfInstances_;
	};

} // Namespace mw.

#endif // MW_INITSDL_H
