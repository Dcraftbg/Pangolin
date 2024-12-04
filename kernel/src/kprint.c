#include <kprint.h>
#include <serial.h>
#include <string.h>
#include <framebuffer.h>

void write_char(char ch) {
    write_serial_char(ch);
    write_framebuffer_char(ch);
}

void write_text(const char *txt) {
    write_serial(txt);
    write_framebuffer_text(txt);
}

void kprint_va(const char* fmt, va_list args) {
     char c;
     char ibuf[20];
     while(*fmt) {
        switch(c=*fmt++) {
        case '%': {
            switch(c=*fmt++) {
            case '%':
                write_char('%');
                break;
            case '\0':
                write_char('%');
                return; 
            case 's':
                write_text(va_arg(args, const char*));
                break;
            case 'd':
            case 'i':
                ibuf[itoa(ibuf, sizeof(ibuf)-1, va_arg(args, int))] = '\0';
                goto write_ibuf;
            case 'z':
                switch(c=*fmt++) {
                case '\0':
                    return;
                case 'u':
                    ibuf[sztoa(ibuf, sizeof(ibuf)-1, va_arg(args, size_t))] = '\0';
                    goto write_ibuf;
                default:
                    write_text("<Unknown fmt `z");
                    write_char(c);
                    write_text("`>");
                    return;
                }
                break;
            case 'p':
                ibuf[uptrtoha_full(ibuf, sizeof(ibuf)-1, va_arg(args, uintptr_t))] = '\0';
                goto write_ibuf;
            default:
                write_text("<Unknown fmt `");
                write_char(c);
                write_text("`>");
                return;
            }
        } break;
        default:
            write_char(c);
            break;
        }
        continue;
write_ibuf:
        write_text(ibuf);
     }
}
