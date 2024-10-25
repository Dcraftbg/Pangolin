#include <kprint.h>
#include <serial.h>
#include <string.h>
void kprint_va(const char* fmt, va_list args) {
     char c;
     char ibuf[20];
     while(*fmt) {
        switch(c=*fmt++) {
        case '%': {
            switch(c=*fmt++) {
            case '%':
                write_serial_char('%');
                break;
            case '\0':
                write_serial_char('%');
                return; 
            case 's':
                write_serial(va_arg(args, const char*));
                break;
            case 'd':
            case 'i':
                ibuf[itoa(ibuf, sizeof(ibuf)-1, va_arg(args, int))] = '\0';
                goto write_ibuf;
            default:
                write_serial("<Unknown fmt `");
                write_serial_char(c);
                write_serial("`>");
            }
        } break;
        default:
            write_serial_char(c);
            break;
        }
        continue;
write_ibuf:
        write_serial(ibuf);
     }
}
