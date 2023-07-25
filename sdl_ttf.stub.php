<?php

/** @generate-class-entries */

final class TTF_Font {}

function TTF_Init(): int {}
function TTF_WasInit(): int {}
function TTF_Quit(): void {}

function TTF_OpenFont(string $name, int $size): TTF_Font {}
function TTF_CloseFont(TTF_Font $font): int {}

function TTF_RenderText_Solid(TTF_Font $font, string $text, SDL_Color $color): ?SDL_Surface {}
function TTF_RenderText_Blended(TTF_Font $font, string $text, SDL_Color $color): SDL_Surface {}
function TTF_RenderText_Shaded(TTF_Font $font, string $text, SDL_Color $color, SDL_Color $backgroundColor): SDL_Surface {}

function TTF_SizeUTF8(TTF_Font $font, string $text, int &$w, int &$h): void {};