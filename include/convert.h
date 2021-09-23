#ifndef FILE_H
#define FILE_H

#ifdef __cplusplus
extern "C" {
#endif 
    
    char htmlTemplate[] = 
    "<!DOCTYPE html>"
    "<html lang=\"en\">"
    "<head>"
    "\t<title>testing</title>"
    "\t<meta charset=\"uft-8\">"
    "</head>"
    "<body>"
    "</body>"
    "</html>";

    // we can bitwise OR these with the upper byte. Should be endianness-agnostic?
    typedef enum {
        TEXT_BOLD = 8,
        TEXT_ITALICS = 4,
        TEXT_UNDERLINE = 2
    } Attrib;
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