# DJ Pi

Does your DJ mixer have no built-in effects? Are your blends crying out for a bit of flange? Then there's only one solution: roll your own effects box using a Raspberry Pi and Arduino!

You can follow the development of this project on my [blog](https://www.tmjohnson.co.uk). My aim is to improve my C++ and learn about digital signal processing by creating a set of digital audio effects that I can drop on my adoring audiences.

The main application runs on the Pi and is written in C++ using the [JUCE framework](https://www.juce.com). I'm starting off with the simple-but-classic volume and delay before departing for the DSP uplands of filters, chorus and what not. The Arduino code is mostly just interfacing with the external controls as is written in C to make it more interesting.

All of the Pi code sits in the `Source` directory. The Arduino stuff is in `arduino` (obviously).
