#ifndef CONVERT_H
#define CONVERT_H

#ifdef __cplusplus
extern "C" {
#endif 
    
    #include "cell.h"
    #include "file.h"

    const char* bold = "<b>";
    const char* boldend = "</b>";

    const char* html = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<title>testing</title>\n\t<meta charset=\"uft-8\">\n</head>\n<body>\n<p>\n";
    
    const char* htmend = "</p>\n</body>\n</html>\n";

    // we can bitwise AND these with the upper byte. Should be endianness-agnostic?
    typedef enum {
        TEXT_BOLD = 8,
        TEXT_ITALICS = 4,
        TEXT_UNDERLINE = 2
    } Attrib;

    void to_html( cell* c, bfmlFile* f, char* fname );
    // as for text size, we will have to get those bits into their own variable and just convert to decimal to insert into our HTML file

    // colour should be VERY doable 

    /* 
     * Need to make functions that check bit values of cell and can return a state
     * Needs to compare to state of previous char 
     * make necessary changes
     * need to define what different states do
     * template of wrapping stuff in paragraphs
     * We're doing that tomorrow tho ( the 22nd )
     */

#ifdef __cplusplus
}
#endif 

#endif 