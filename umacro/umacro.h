#ifndef INCLUDED_UMACRO
#define INCLUDED_UMACRO

#define CHECK_SYSCALL(func, rc, ok, on_err, args...) 	\
if ((rc = func(args)) != ok) {	 			\
	if (rc == -1) { 				\
		on_err(errno, #func);			\
	} else {					\
		on_err(rc, #func);			\
	}						\
}					 		\

#endif
