#ifndef MW_INITMIXER_H
#define MW_INITMIXER_H

#include <SDL_mixer.h>

namespace mw {

	class InitMixer {
	protected:
		InitMixer();
		~InitMixer();

		InitMixer(const InitMixer&) = delete;
		InitMixer& operator=(const InitMixer&) = delete;

	private:
		static int nbrOfInstances;
	};

} // Namespace mw.

#endif // MW_INITMIXER_H
