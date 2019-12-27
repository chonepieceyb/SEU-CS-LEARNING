#define ATTRIBUTE_MEMBER_FUNC(argType, arg)\
	public:\
	void set_##arg(const argType& v) {\
	arg = v;\
	}\
	 argType get_##arg()const {\
	return  arg;\
	}
#define ATTRIBUTE_READ_ONLY(argType, arg)\
	public:\
	  argType get_##arg()const {\
		return  arg;\
		}
#define ATTRIBUTE_WRITE(argType, arg)\
	public:\
	void set_##arg(const argType& v) {\
	arg = v;\
	}
#define ATTRIBUTE_READ_MODIFIED(argType, arg)\
	public:\
	argType get_##arg() {\
		return &arg;\
		}