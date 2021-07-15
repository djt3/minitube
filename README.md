# minitube - a minimsalistic youtube client
Minitube is a TUI (Terminal UI) youtube client, successor to tuitube. Videos are scraped and parsed directly from youtube using libcurlpp, and the interface is presented using a custom tui library.

## Current features
- Plays videos using MPV
- Home page
- Search page

## Dependencies
- MPV
- Curlpp (libcurlpp in the AUR)
- CMake

## Build instructions
`git clone https://github.com/djt3/minitube
cd minitube
cmake .
make`
