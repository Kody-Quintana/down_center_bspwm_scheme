#include <X11/Xlib.h>
#include <boost/process.hpp>
#include <boost/process/io.hpp>
#include <boost/process/pipe.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

using boost::process::child;
using boost::process::ipstream;
using boost::process::std_out;
using std::cout;
using std::endl;
using std::getline;
using std::hex;
using std::string;
using std::stringstream;


void vlc_fullscreen_fix(string instance, string wid){
    if (instance == "vlc"){
        ipstream pipe_stream;
        child c("xtitle " + wid, std_out > pipe_stream);
        string xtitle;

        c.wait();
        if (c.exit_code() != 0){
            return;
        }

        getline(pipe_stream, xtitle);
        if (xtitle == "vlc"){
            cout << "layer=above border=off" << endl;
            exit(0);
        }
    }
}


void auto_scheme(){
    Display* display = XOpenDisplay(NULL);
    Screen*  screen = DefaultScreenOfDisplay(display);
    XWindowAttributes focused_auto_window;
    unsigned int focused_auto_window_id;

    // Get focused.automatic window id:
    {
        ipstream pipe_stream;
        child c("bspc query -N -n focused.automatic", std_out > pipe_stream);
        string output_line;
        stringstream focused_auto_window_id_stringstream;

        c.wait();
        // Above command will return non-zero in instances where there isn't a window, like an empty workspace
        // This is fine, just exit here
        if (c.exit_code() != 0){
            exit(0);
        }

        // Shuffle around output line to get it as an int
        getline(pipe_stream, output_line);
        focused_auto_window_id_stringstream << hex << output_line;
        focused_auto_window_id_stringstream >> focused_auto_window_id;
    }

    XGetWindowAttributes(display, focused_auto_window_id, &focused_auto_window);

    // If width is much larger than height open a window to the side
    if (focused_auto_window.width * 0.67 > focused_auto_window.height){

        // Open new windows toward center of screen
        if (focused_auto_window.width / 2 + focused_auto_window.x < screen->width / 2){ // if left:
            cout << "split_dir=east focus=on" << endl;
        } else { // if right:
            cout << "split_dir=west focus=on" << endl;
        }
    } else { // If height is must larger than width open a new window below instead
        cout << "split_dir=south focus=on" << endl;
    }
}


int main(int argc, char** argv){
    if (argc < 3){ exit(-1); }
    std::vector<std::string> all_args;
    all_args.assign(argv + 1, argv + argc);

    vlc_fullscreen_fix(all_args[2], all_args[0]);

    auto_scheme();

    return 0;
}
