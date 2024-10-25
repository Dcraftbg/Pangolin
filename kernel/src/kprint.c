#include <kprint.h>
#include <serial.h>
void kprint_va(const char* fmt, va_list args) {
     char c;
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
     }
}
