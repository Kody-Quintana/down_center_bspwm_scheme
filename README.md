# [↳ ↲] - BSPWM external rule auto scheme
#### opens new windows down or toward center of screen

##### Install:
```Bash
git clone https://github.com/Kody-Quintana/down_center_bspwm_scheme "$HOME/.config/bspwm/down_center_bspwm_scheme" &&\
cd "$HOME/.config/bspwm/down_center_bspwm_scheme" &&\
cmake . &&\
make &&\
printf "bspc config external_rules_command \"\$HOME/.config/bspwm/down_center_bspwm_scheme/down_center_scheme\"" >> "$HOME/.config/bspwm/bspwmrc"
```

Includes VLC fullscreen fix taken from:
https://github.com/baskerville/bspwm/issues/1021#issuecomment-563469039
