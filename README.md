# streamer_analysis
Utility for comparing observed solar streamer latitude against models

![observed-streamer](http://i.imgur.com/IWMXTFb.png)
![simulated-streamer](http://i.imgur.com/q28UuSS.png)

## Compilation
Make sure that the following libraries and packages are installed on your machine:

    boost '>=1.64'
    opencv '>=3.0'
    cmake '>=3.8'
    
Compile as you would with any other CMake project:

    # navigate to the project folder first
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

## Running
The program requires a directory containing image files as its first argument, 
and an output file path as its second argument:

    $ ./streamer_analysis
    USAGE: stereo-reader data_dir csv_output_file
    
The program will provide an interface to click streamers, thereby tracing a line from the center 
to their tip, and then record these angles in the output file. The controls are as follows:
- Click to record a streamer angle (this will turn the line from blue to rosa)
- Rosa lines will be recorded in the output file
- Hit spacebar at any time to continue to the next image
- The program will automatically terminate when the last image is reached
    
## Project Structure
- `data` contains sample images. Consult README.md in subdirectory
- `src` contains *streamer_analysis* source code
- `scripts` contains utility scripts for interpreting the data outputted by *streamer_analysis*
