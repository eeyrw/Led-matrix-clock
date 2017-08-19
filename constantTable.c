__code unsigned char SelectTable[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF};
__code unsigned char NumberStr[60][2]={
    " 0"," 1"," 2"," 3"," 4"," 5",
    " 6"," 7"," 8"," 9","10","11",
    "12","13","14","15","16","17",
    "18","19","20","21","22","23",
    "24","25","26","27","28","29",
    "30","31","32","33","34","35",
    "36","37","38","39","40","41",
    "42","43","44","45","46","47",
    "48","49","50","51","52","53",
    "54","55","56","57","58","59"};

__code unsigned char NumberStr2[100][2]={
    "00","01","02","03","04","05",
    "06","07","08","09","10","11",
    "12","13","14","15","16","17",
    "18","19","20","21","22","23",
    "24","25","26","27","28","29",
    "30","31","32","33","34","35",
    "36","37","38","39","40","41",
    "42","43","44","45","46","47",
    "48","49","50","51","52","53",
    "54","55","56","57","58","59",
    "60","61","62","63","64","65",
    "66","67","68","69","70","71",
    "72","73","74","75","76","77",
    "78","79","80","81","82","83",
    "84","85","86","87","88","89",
    "90","91","92","93","94","95",
    "96","97","98","99"};														   
__code unsigned char WeekStr[8][5]={"Sun-7","Mon-1","Tue-2","Wed-3","Thu-4","Fri-5","Sat-6","Sun-7"};
//code unsigned char SelectTable[]={0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x80};

__code unsigned char Font[]={
    0x00,0x00,0x00,0x00,0x00,0x00,0x00, // sp
    0x20,0x20,0x20,0x20,0x00,0x20,0x00, // ! 
    0x50,0x50,0x50,0x00,0x00,0x00,0x00, // " 
    0x50,0x50,0xF8,0x50,0xF8,0x50,0x50, // # 
    0x20,0xF0,0x28,0x70,0xA0,0x78,0x20, // $ 
    0x00,0xC0,0xC8,0x10,0x20,0x40,0x98, // % 
    0x30,0x48,0x28,0x10,0xA8,0x48,0xB0, // & 
    0x30,0x20,0x10,0x00,0x00,0x00,0x00, // ' 
    0x40,0x20,0x10,0x10,0x10,0x20,0x40, // ( 
    0x10,0x20,0x40,0x40,0x40,0x20,0x10, // ) 
    0x00,0x20,0xA8,0x70,0xA8,0x20,0x00, // * 
    0x00,0x20,0x20,0xF8,0x20,0x20,0x00, // + 
    0x00,0x00,0x00,0x00,0x60,0x40,0x20, // , 
    0x00,0x00,0x00,0xF8,0x00,0x00,0x00, // - 
    0x00,0x00,0x00,0x00,0x00,0x30,0x30, // . 
    0x00,0x80,0x40,0x20,0x10,0x08,0x00, // / 
    0x70,0x88,0xC8,0xA8,0x98,0x88,0x70, // 0 
    0x20,0x30,0x20,0x20,0x20,0x20,0x70, // 1 
    0x70,0x88,0x80,0x40,0x20,0x10,0xF8, // 2 
    0xF8,0x40,0x20,0x40,0x80,0x88,0x70, // 3 
    0x40,0x60,0x50,0x48,0xF8,0x40,0x40, // 4 
    0xF8,0x08,0x78,0x80,0x80,0x88,0x70, // 5 
    0x60,0x10,0x08,0x78,0x88,0x88,0x70, // 6 
    0xF8,0x80,0x40,0x20,0x10,0x10,0x10, // 7 
    0x70,0x88,0x88,0x70,0x88,0x88,0x70, // 8 
    0x70,0x88,0x88,0xF0,0x80,0x40,0x30, // 9 
    0x00,0x30,0x30,0x00,0x30,0x30,0x00, // : 
    0x00,0x30,0x30,0x00,0x30,0x20,0x10, // ; 
    0x40,0x20,0x10,0x08,0x10,0x20,0x40, // < 
    0x00,0x00,0xF8,0x00,0xF8,0x00,0x00, // = 
    0x10,0x20,0x40,0x80,0x40,0x20,0x10, // > 
    0x70,0x88,0x80,0x40,0x20,0x00,0x20, // ? 
    0x70,0x88,0x80,0xB0,0xE8,0x88,0x70, // @ 
    0x70,0x88,0x88,0x88,0xF8,0x88,0x88, // A 
    0x78,0x88,0x88,0x78,0x88,0x88,0x78, // B 
    0x70,0x88,0x08,0x08,0x08,0x88,0x70, // C 
    0x38,0x48,0x88,0x88,0x88,0x48,0x38, // D 
    0xF8,0x08,0x08,0x78,0x08,0x08,0xF8, // E 
    0xF8,0x08,0x08,0x78,0x08,0x08,0x08, // F 
    0x70,0x88,0x08,0xE8,0x88,0x88,0xF0, // G 
    0x88,0x88,0x88,0xF8,0x88,0x88,0x88, // H 
    0x70,0x20,0x20,0x20,0x20,0x20,0x70, // I 
    0xE0,0x40,0x40,0x40,0x40,0x48,0x30, // J 
    0x88,0x48,0x28,0x18,0x28,0x48,0x88, // K 
    0x08,0x08,0x08,0x08,0x08,0x08,0xF8, // L 
    0x88,0xD8,0xA8,0xA8,0x88,0x88,0x88, // M 
    0x88,0x88,0x98,0xA8,0xC8,0x88,0x88, // N 
    0x70,0x88,0x88,0x88,0x88,0x88,0x70, // O 
    0x78,0x88,0x88,0x78,0x08,0x08,0x08, // P 
    0x70,0x88,0x88,0x88,0xA8,0x48,0xB0, // Q 
    0x78,0x88,0x88,0x78,0x28,0x48,0x88, // R 
    0xF0,0x08,0x08,0x70,0x80,0x80,0x78, // S 
    0xF8,0x20,0x20,0x20,0x20,0x20,0x20, // T 
    0x88,0x88,0x88,0x88,0x88,0x88,0x70, // U 
    0x88,0x88,0x88,0x88,0x88,0x50,0x20, // V 
    0x88,0x88,0x88,0xA8,0xA8,0xA8,0x50, // W 
    0x88,0x88,0x50,0x20,0x50,0x88,0x88, // X 
    0x88,0x88,0x88,0x50,0x20,0x20,0x20, // Y 
    0xF8,0x80,0x40,0x20,0x10,0x08,0xF8, // Z 
    0x70,0x10,0x10,0x10,0x10,0x10,0x70, // [ 
    0xA8,0x50,0xA8,0x50,0xA8,0x50,0xA8, // 55
    0x70,0x40,0x40,0x40,0x40,0x40,0x70, // ] 
    0x20,0x50,0x88,0x00,0x00,0x00,0x00, // ^ 
    0x00,0x00,0x00,0x00,0x00,0x00,0xF8, // _ 
    0x10,0x20,0x40,0x00,0x00,0x00,0x00, // ' 
    0x00,0x00,0x70,0x80,0xF0,0x88,0xF0, // a 
    0x08,0x08,0x68,0x98,0x88,0x88,0x78, // b 
    0x00,0x00,0x70,0x08,0x08,0x88,0x70, // c 
    0x80,0x80,0xB0,0xC8,0x88,0x88,0xF0, // d 
    0x00,0x00,0x70,0x88,0xF8,0x08,0x70, // e 
    0x60,0x90,0x10,0x38,0x10,0x10,0x10, // f 
    0x00,0xF0,0x88,0x88,0xF0,0x80,0x70, // g 
    0x08,0x08,0x68,0x98,0x88,0x88,0x88, // h 
    0x20,0x00,0x30,0x20,0x20,0x20,0x70, // i 
    0x40,0x00,0x60,0x40,0x40,0x48,0x30, // j 
    0x08,0x08,0x48,0x28,0x18,0x28,0x48, // k 
    0x30,0x20,0x20,0x20,0x20,0x20,0x70, // l 
    0x00,0x00,0x58,0xA8,0xA8,0x88,0x88, // m 
    0x00,0x00,0x68,0x98,0x88,0x88,0x88, // n 
    0x00,0x00,0x70,0x88,0x88,0x88,0x70, // o 
    0x00,0x00,0x78,0x88,0x78,0x08,0x08, // p 
    0x00,0x00,0xB0,0xC8,0xF0,0x80,0x80, // q 
    0x00,0x00,0x68,0x98,0x08,0x08,0x08, // r 
    0x00,0x00,0x70,0x08,0x70,0x80,0x78, // s 
    0x10,0x10,0x38,0x10,0x10,0x90,0x60, // t 
    0x00,0x00,0x88,0x88,0x88,0xC8,0xB0, // u 
    0x00,0x00,0x88,0x88,0x88,0x50,0x20, // v 
    0x00,0x00,0x88,0x88,0xA8,0xA8,0x50, // w 
    0x00,0x00,0x88,0x50,0x20,0x50,0x88, // x 
    0x00,0x00,0x88,0x88,0xF0,0x80,0x70, // y 
    0x00,0x00,0xF8,0x40,0x20,0x10,0xF8  // z
};