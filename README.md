# mumt306project
**Algorithmic music generation project, uploaded after completion**
[also hosted here](http://cs.mcgill.ca/~vsaund/mumt306/project.html)

Program to produce a song using some set-up structures as well as user input. It uses the Rtmidi library and a midi-csv interfacing program. 

**Details: VERSION 6 (final version)**
* Doesn't use RtMidi, but creates an equivalent output to the RtMidi program in version4 (previous version) in the form of a playable midi file.
* Uses midicsv to output values to a midifile. Has a web component allowing the user to view the levels of certain tracks at the same time as the piece is played.
* Does this without letting the threads mess up data by saving all the data into separate files and concatenating into one CSV file at the end. The threads are still necessary here because multiple threads reference the chord used by the factor=1 thread during runtime.
* I chose this set-up for creating the MIDI file because it is more readable and was less confusing (not necessarily easier) to code; instead of just numbers, the midicsv program needs certain names for things (such as note on) and it's easier to see what's going on when the file is created and read.
*  The general concept and musical output are as with VERSION 4.

**Chords for bass:**

The base key note number is kept as a global variable. In my setup I was using an A, note number 57. However some of the chords used 56, and since I kept the chord note differences as unsigned ints I subtracted 12 from my base key note and added values between 11 and 22, as shown below. So to be clear, these are values to add to a fixed note to get a chord.

**Ideas for how to improve/extend the project:**
*  Assign output values useful for display.
*  HTML5 canvas display of levels for particular voices.

**Challenges experienced:**
*  I originally wanted to have more interconnection between the threads, but this caused mis-alignment in the timing. I still want to experiment to see if I can keep one thread as a timing thread which cues the iterations of other threads, but in the interest of time I wrote this simpler version first.
*  The C++11 thread library was unfortunately not working on the OSX computers, and so I set up the Boost library which is actually included in C++11. On the Trottier Ubuntu machines I have the same program set up using C++11. This was particularly interesting to me since I have only used threads before in C; C++ makes their implementation much simpler.
*  I found that the more pleasant I made the music, the less I used elements of "algorithmic" composition. Thus I removed some of the more hard-coded parts and allowed them to vary randomly within certain distributions. While this is more interesting to code, it doesn't always sound as good. It is a lot more difficult than I thought to set up an appealing composition, particularly since MIDI instruments don't transition very smoothly between pitches, and their attacks are built-in.
*  I don't have permissions to setup the Trottier computers so that I have a lot of control over processes; therefore the fluidsynth interactions with the MIDI produced sometimes cause errors, since the audio process is sometimes swapped out of RAM. I can't do anything to prevent this, unfortunately, except by minimizing the number of other things running simultaneously.
*  I wasted a huge amount of time trying to get the tracks of the MIDI file to behave correctly; I used file type 1 but it wasn't working. The problem seemed to be with the "tempo" change values since any other MIDI files I looked at used them a lot, but actually the issue was that some audio players apparently don't include all the MIDI instruments. However, as a consequence of this I understand the MIDI format really well, and I wrote a version of the program for MIDI file type 0. It coordinated timing elements at the end, sorted them, and outputted the piece in a single track. This was an interesting process since there aren't many good examples of this kind of manual manipulation of a MIDI file online; everyone else seems to use higher-level software or just analyze files instead of writing them from scratch. It was really fascinating learning to do this just from processing other MIDI files into CSVs.
*  Unfortunately my original plan, which involved having a user display of the different tracks playing, isn't feasible with the system I have available; the CS computers don't give me enough permissions to play audio how I want, and if I simply attach the file online for download, it won't synch well with the visuals if the user is required to play it separately. I might still experiment with this in the future since the algorithmic part of the composition is much more interesting if a user can see it in a simpler way than by reading the code.
