#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__

#include "Singleton.h"
#include "Types.h"

class CWindow;

enum Actions
{
	Exit,
	Forward,
	Left,
	Right,
	Backward,
	MouseX,
	MouseY
};

class CInputManager : public Singleton< CInputManager >
{
    public:
        CInputManager();
        virtual ~CInputManager();
		void Init( CWindow* aWindow );
		bool DoAction( Actions aAction );
		bool DoAction(Actions aAction, float& aAmount);
		void ProcessInputs();

    private:
		CWindow* mWindow;
};

#endif
