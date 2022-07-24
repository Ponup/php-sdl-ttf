# SDL_ttf PHP extension

[SDL_ttf](https://github.com/libsdl-org/SDL_ttf) for PHP allows you to use TrueType fonts to render text in SDL applications. It requires [SDL PHP](https://github.com/ponup/php-sdl) extension.

## Building

```bash
phpize
./configure --enable-sdl_ttf
make
sudo make install
```

Run tests with installed PHP (avoids skipped tests):

```
php run-tests.php --show-diff -q
```

## Requirements

Require PHP 8+ and SDL PHP extension

```
pecl install sdl-devel
```
