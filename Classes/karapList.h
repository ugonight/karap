#pragma once

#include "karap.h"

#define MAKE_CLASS(form) class form : public Karap { \
						 public: \
							form(); \
						 }


//�錾
MAKE_CLASS(Nomal);
MAKE_CLASS(Mafia);
