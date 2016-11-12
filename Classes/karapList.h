#pragma once

#include "karap.h"

#define MAKE_CLASS(form) class form : public Karap { \
						 public: \
							form(); \
						 }


//éŒ¾
MAKE_CLASS(Nomal);
MAKE_CLASS(Mafia);
