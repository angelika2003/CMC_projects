#include <stdio.h>

void normalize_path(char *buf) {
    char *s = buf;

    int i = 0; //old
    int t = 0; //new

    while (s[i] != '\0') {
        i++;
        t++;               //i и t всегда на след после '/'

        if (s[i] == '.') {
            if (s[i + 1] == '/') {
                i ++;
                t--;
                continue;
            } else if (s[i + 1] == '\0') {
                if (t - 1 != 0) {
                    t--;
                    s[t] = '\0';
                } else {
                    s[1] = '\0';
                }
                return;
            } else if (s[i + 1] == '.') {
                if (s[i + 2] == '/') {
                    i += 2;
                    t--;
                    if (t != 0) {
                        t--;
                        while (s[t] != '/') {
                            t--;
                        }
                    }
                    continue;
                } else if (s[i + 2] == '\0') {
                    i++;
                    t--;
                    if (t != 0) {
                        t--;
                        while (s[t] != '/') {
                            t--;
                        }
                    }
                    continue;
                }
            }
        }

        //копирование:
        while (s[i] != '/' && s[i] != '\0') {
            s[t] = s[i];
            i++;
            t++;
        }
        s[t] = s[i];

    }

    if (s[t - 1] == '/'  && (t - 1) != 0) {
        s[t - 1] = '\0';
    }
}


