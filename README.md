# [↳ ↲] - BSPWM external rule auto scheme
#### opens new windows down or toward center of screen based on the ratio of width vs. height of the `focused.automatic` window

##### Install:
```Bash
install_dir="$HOME/.config/bspwm/down_center_bspwm_scheme"
git clone https://github.com/Kody-Quintana/down_center_bspwm_scheme "$install_dir" &&\
cd "$install_dir" && cmake . && make &&\
printf "bspc config external_rules_command \"$install_dir/down_center_scheme\"" >> "$HOME/.config/bspwm/bspwmrc"
```

Includes VLC fullscreen fix taken from:
https://github.com/baskerville/bspwm/issues/1021#issuecomment-563469039

##### Requires:
* [xtitle](https://github.com/baskerville/xtitle)
* [boost.process](https://www.boost.org/doc/libs/1_79_0/doc/html/process.html) - for calling `bspc` and `xtitle`
