/* sdl_ttf extension for PHP */

#ifndef PHP_SDL_TTF_H
#define PHP_SDL_TTF_H

extern zend_module_entry sdl_ttf_module_entry;
#define phpext_sdl_ttf_ptr &sdl_ttf_module_entry

#define PHP_SDL_TTF_VERSION "0.3.0"

#if defined(ZTS) && defined(COMPILE_DL_SDL_TTF)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif /* PHP_SDL_TTF_H */
