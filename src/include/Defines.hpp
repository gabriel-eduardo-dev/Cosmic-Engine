#include <iostream>

#ifdef __COSMIC_DEBUG 
	#define LOG(msg) std::cout << msg << '\n'
	#define ERROR(msg) std::cout << msg << '\n'
#else 
	#define LOG(msg)
	#define ERROR(msg)
#endif // COSMIC_DEBUG

