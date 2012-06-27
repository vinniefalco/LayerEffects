# TagLib Amalgamation

A distribution of the [TagLib][1] library in amalgamated source code form.

## What's an amalgamation?

An amalgamation is simply a collection of header and source files that have been
concatenated together to form one or more very large files. In this form, they
are easy to add to your existing project as source files (rather than linking
as a library). They are also easier to redistribute if you are making an open
source application and don't want to have any external dependencies.

## What is TagLib?

TagLib is a library for reading and editing the meta-data of several popular
audio formats. Currently it supports both ID3v1 and ID3v2 for MP3 files, Ogg
Vorbis comments and ID3 tags and Vorbis comments in FLAC, MPC, Speex, WavPack
TrueAudio, WAV, AIFF, MP4 and ASF files. 

## How do I use this?

Add TagLibAmalgam.cpp to your existing project, include TagLibAmalgam.h
in the source files where you want to use TagLib, and that's it!

The [TagLib Amalgamation][2] was built using the [Amalgamate Templates][3].

## License

Copyright (c) 2002 Scott Wheeler, Lukas Lalinsky, Ismael Orenstein,
Allan Sandfeld Jensen, Teemu Tervo, Mathias Panzenböck<br>
TagLib is distributed under both the [GNU Lesser General Public License][4]
(LGPL) and the [Mozilla Public License][5] (MPL).

[1]: http://developer.kde.org/~wheeler/taglib.html "TagLib"
[2]: https://github.com/vinniefalco/TagLibAmalgam/ "TagLib Amalgamation"
[3]: https://github.com/vinniefalco/Amalgams/ "Amalgamate Templates"
[4]: http://www.gnu.org/licenses/gpl-2.0.html "GNU GPL v2"
[5]: http://www.mozilla.org/MPL/ "MPL"
