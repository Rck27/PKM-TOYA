#define BOARDTYPE 3 // 1 for number, 2 for alphabet, 3 for shape puzzle

bool debug = true;//////////////DEBUG FOR DISABLE THE GAME, ONLY  CHECKING THE BASIC FUNCTION OF THE BOARD
#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
// #include "myFont.h"




#define SHORTDELAY 500
#define LONGDELAY 1000

//MOSI: 35
//MISO: 37
//SCK: 36
//SS: 34


#define CLK_PIN   36
#define DATA_PIN  35
#define CS_PIN    34

// MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


#define ROWS  4 //four rows
#define  COLS  4 //four columnsv
const byte NUM_LEDS = 16;
const byte LED_PIN = 4;
int position, winCount;
unsigned long lastMillis, currentMillis;
char randomAlphabet, pressedKey;
int mode, score;
char t[100];

/////////////////////variables for the game
  static char sequence[5]; // Array to hold the sequence
  static int currentLevel = 1; // Current level (starts at 1)
  static int inputIndex = 0; // Track the current input position
  static bool gameStarted = false;
  static unsigned long lastTime = 0; // To manage non-blocking delays
  static int sequenceIndex = 0; // Index for showing the sequence
  static int wrongCount = 0;  static bool changed = true;

  // const char* indonesianWords[] = {"ABDI","ABEN","ABID","ABOI","ABON","ACIK","ADEH","ADEM","ADIB","ADIK","ADIL","ADON","AFEK","AGEN","AGIH","AGIL","AGIO","AGON","AHLI","AJEK","AKEO","AKIL","AKLI","ALEM","ALIF","ALIH","ALIK","ALIM","ALIN","ALIP","ALOI","ALON","AMBI","AMEN","AMIL","AMIN","AMKO","AMOI","AMPE","AMPO","ANEH","ANIL","ANOM","APEK","APEL","APIK","APOK","BACO","BADE","BADI","BAGI","BAID","BAIK","BAIN","BAJI","BAKH","BAKI","BAKO","BANG","BANI","BANK","BEDA","BEDO","BEGA","BEGO","BEHA","BEKA","BELA","BELI","BELO","BEMO","BENA","BENI","BEOL","BIAH","BIAK","BIDA","BIDO","BIJA","BILA","BINA","BLEK","BLOG","BLOK","BODI","BOGA","BOGI","BOLA","BONG","CABE","CABO","CAEM","CAHI","CAKI","CAKO","CALO","CANG","CAPE","CEKI","CELA","CELI","CEMA","CENA","CENG","CEPO","CIAK","CIAP","CIKA","CINA","CING","COAK","COBA","COLI","DAGE","DAGI","DAHI","DAIF","DAIM","DAKI","DAME","DAMI","DANG","DEMI","DEMO","DENA","DEPA","DEPO","DIAM","DIAN","DILA","DINA","DOBI","DONG","DONI","EBAM","EBAN","EDAN","EGAH","EGOL","EJAN","EKAD","EKON","ELAK","ELAN","ELOK","ELON","EMOH","EMOL","EMPO","ENAK","ENAM","ENAP","ENOM","EPAK","EPIK","EPOK","FAIL","FANI","FEKO","FILM","FILO","FLOP","FOLI","GACO","GADO","GAEK","GAIB","GAIL","GAIN","GAJI","GALI","GANI","GAOK","GEDI","GELA","GELI","GELO","GEMA","GEMI","GENA","GIAL","GIAM","GILA","GOAK","GOBA","GODA","GOEL","GOLF","GONI","HAID","HAIK","HAIL","HAJI","HALO","HANG","HELA","HELM","HENG","HIFA","HINA","HOBI","HOKI","HOLI","IBAN","IDAH","IDAM","IDAP","IDEM","IDEP","IFAH","IGAL","IGLO","IJAB","IJON","IKAB","IKAL","IKAN","IKON","ILAH","ILAK","IMAK","IMAN","IMLA","INAP","INCA","INFO","INGA","IPON","JADI","JAGO","JAHE","JAIL","JALI","JANI","JEDA","JELA","JELI","JENG","JEPA","JIKA","JILA","JOKI","JOLI","KACI","KACO","KADE","KADI","KADO","KAFE","KAFI","KAIL","KAIN","KAJI","KALI","KALO","KAMI","KAMP","KANE","KANG","KANO","KAON","KAPI","KEBO","KECI","KEDI","KEJI","KELI","KELP","KEMI","KENA","KENG","KIAH","KIAL","KIAM","KIAN","KIAP","KILA","KILN","KILO","KIMA","KIMO","KINA","KIPA","KLAN","KLEM","KLEN","KLEP","KLIN","KLIP","KLON","KLOP","KNOP","KOCI","KODA","KODE","KODI","KOIL","KOIN","KOJA","KOLA","KOLI","KOMA","KOPI","LACI","LADI","LAGI","LAGO","LAIF","LAIK","LAIN","LAKI","LANG","LAPO","LEAK","LECI","LECO","LEFA","LEGA","LEGI","LEGO","LEJA","LEKA","LEMA","LEMO","LENA","LENG","LEPA","LIAN","LIFO","LIGA","LIMA","LING","LOAK","LOBA","LOBI","LOHA","LOJI","LOKA","LOKI","LONG","MACE","MADI","MADO","MAGI","MAIN","MAKI","MALE","MANG","MANI","MBAH","MBAK","MBOK","MEGA","MEJA","MEKO","MENA","MENI","MIAK","MIAP","MIKA","MINA","MIOP","MODE","MOGA","MOKA","MOKE","MOLA","MOLE","MONG","NABI","NADI","NAFI","NAHI","NAIB","NAIF","NAIK","NAIM","NALI","NEKA","NEKO","NICA","NILA","NODA","NOEM","NOJA","OCEH","OGAH","OGAM","OGEL","OJEG","OJEK","OLAH","OLAK","OLEH","OLEK","OLIA","OMEL","ONAK","ONCE","OPAK","OPAL","OPEN","PACE","PADI","PAGI","PAIL","PALE","PALI","PECI","PEDA","PEGO","PEKA","PELO","PENA","PENI","PEOK","PIAH","PIAK","PIAL","PICA","PICO","PIKA","PIKE","PION","PLAN","PLOI","POAL","POCI","POIN","POLA","POMA","PONI"
  // };

/////


Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);



#if BOARDTYPE == 1
const char* indonesianWords[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
const int availableLength = sizeof(indonesianWords);
// const char* indonesianWords[] = {"1", "2", "3"};
const char* keys[COLS][ROWS]= {
  {"0", "1", "2", "3"},
  {"4", "5", "6", "7"},
  {"8", "9", "x", "-"},
  {"n", "/", "+", "n"},
  {"n", "n", "n", "n"},
  {"n", "n", "n", "n"},
  {"n", "n", "n", "n"},

};

#elif BOARDTYPE == 2

const char* indonesianWords[] = {
"ABDI","ABDU","ABEN","ABET","ABID","ABIS","ABOI","ABON","ABUH","ABUK","ABUL","ABUR","ABUS","ACIK","ACUH","ACUM","ADEH","ADEM","ADIB","ADIK","ADIL","ADON","ADUH","ADUK","ADUN","AFEK","AGEN","AGIH","AGIL","AGIO","AGON","AGUK","AGUL","AGUN","AGUS","AGUT","AHLI","AJEK","AJIR","AJRE","AJUK","AJUN","AJUR","AKEO","AKIL","AKLI","AKOR","AKSI","AKUN","AKUR","AKUT","ALEM","ALIF","ALIH","ALIK","ALIM","ALIN","ALIP","ALIR","ALIS","ALIT","ALKU","ALOI","ALON","ALOT","ALTO","ALUM","ALUN","ALUP","ALUR","AMBI","AMEN","AMIL","AMIN","AMIR","AMIS","AMIT","AMKO","AMOI","AMOR","AMPE","AMPO","AMPU","AMUH","AMUK","ANEH","ANIL","ANIS","ANJU","ANOM","ANTE","ANTI","ANUS","ANUT","APEK","APEL","APES","APIK","APIT","APOK","APUH","ARDI","AREK","AREN","ARES","ARIF","ARIH","ARIK","ARIL","ARIP","ARIS","ARIT","ARKU","ARON","ARTI","ARUK","ARUN","ARUS","ASET","ASID","ASIH","ASIL","ASIN","ASLI","ASOI","ASOR","ASRI","ASUH","ATOK","ATOL","ATOM","ATOP","ATOS","ATUR","ATUS","AUNG","AUTO","AVEN","AWET","AWIN","AWUR","AWUT","AYEM","AYID","AYIT","AYOM","AYUK","AYUM","AYUN","AYUT","BADE","BADI","BAGI","BAHU","BAID","BAIK","BAIN","BAIS","BAIT","BAJI","BAJU","BAKH","BAKI","BAKO","BAKU","BALU","BANG","BANI","BANK","BARI","BARU","BASI","BATI","BATU","BAUD","BAUK","BAUN","BAUR","BAUT","BAYI","BAYU","BEDA","BEDO","BEGA","BEGU","BEKA","BEKU","BELA","BELI","BELO","BELU","BEMO","BENA","BENI","BEOL","BERA","BERI","BERU","BESI","BETA","BETI","BIAH","BIAK","BIAR","BIAS","BIAT","BIAU","BICU","BIDA","BIDO","BIJA","BIKU","BILA","BINA","BIRO","BIRU","BISA","BISU","BIUS","BIUT","BLEK","BLOG","BLOK","BLUS","BODI","BOGA","BOGI","BOIS","BOKS","BOKU","BOLA","BOLU","BONG","BORA","BOTA","BOYA","BREM","BREN","BROM","BROS","BRUK","BUAH","BUAI","BUAK","BUAL","BUAR","BUAS","BUAT","BUDE","BUDI","BUIH","BUIL","BUKA","BULE","BUMI","BUNA","BUNG","BUNI","BURA","BUSA","BUSI","BUTA","BUYA","CABE","CABO","CAEM","CAGU","CAHI","CAIR","CAIS","CAKI","CAKO","CALO","CANG","CAOS","CAPE","CARI","CATU","CAUL","CAWI","CEKI","CEKU","CELA","CELI","CEMA","CENA","CENG","CEPO","CEPU","CERI","CETI","CIAK","CIAP","CIAR","CIKA","CIKU","CING","CITA","CIUM","CIUT","COAK","COBA","CUAI","CUAK","CUAL","CUAR","CUAT","CUEK","CUIK","CUIL","CUIT","CUKA","CUKI","CULA","CULI","CUMA","CUNG","CURA","CURI","CUTI","DAGE","DAGI","DAGU","DAHI","DAIF","DAIM","DAKI","DAKU","DALU","DAME","DAMI","DANG","DARI","DARO","DASI","DATI","DATU","DAUK","DAUN","DAUR","DAYU","DEBU","DEKU","DELU","DEMI","DEMO","DENA","DEPA","DEPO","DERA","DERU","DESA","DEWA","DEWI","DIAM","DIAN","DIAR","DIAS","DIAT","DIES","DIET","DILA","DINA","DITO","DOBI","DOKU","DONG","DONI","DOSA","DRAF","DRAI","DRAM","DRAT","DREL","DRIF","DRIL","DRIP","DROP","DRUM","DUAI","DUEL","DUET","DUGA","DUHA","DUHE","DUIT","DUKA","DULA","DULI","DUMI","DUNG","DUPA","DURA","DURI","DUTA","DZAL","EBAM","EBAN","EBRO","EDAN","EDAR","EDIT","EGAH","EGAT","EGOL","EGOS","EJAN","EKAD","EKON","EKOR","ELAK","ELAN","ELOK","ELON","ELUS","EMAS","EMAT","EMIR","EMIS","EMOH","EMOL","EMPO","EMPU","EMUT","ENAK","ENAM","ENAP","ENAS","ENAU","ENOM","EPAK","EPIK","EPOK","EPOS","ERAK","ERAM","ERAT","ERIK","EROT","ERTI","ESAI","ESAK","ESOK","ESOT","ETIK","ETIL","ETIS","ETOS","ETSA","FAIL","FAKS","FANI","FASE","FEKO","FERI","FIAT","FILM","FILO","FIRN","FLAT","FLIS","FLOP","FOLI","FOYA","FRIB","FRON","FUAD","FULI","FUSI","GACO","GADO","GAEK","GAET","GAIB","GAIL","GAIN","GAIT","GAJI","GALI","GANI","GAOK","GARI","GARU","GAUK","GAUL","GAUN","GAUT","GEBU","GEDI","GELA","GELI","GELO","GEMA","GEMI","GENA","GERA","GERO","GERU","GESA","GETA","GETU","GIAL","GIAM","GIAT","GILA","GIPS","GIRO","GITA","GIUK","GIUR","GOAK","GOBA","GODA","GOEL","GOLF","GONI","GORI","GRAD","GRAF","GRAM","GRES","GRIA","GRIP","GROS","GRUP","GUAL","GUAM","GUAR","GUCI","GUDE","GUDI","GUIT","GULA","GULI","GUMA","GUNA","GURI","GUSI","HAID","HAIK","HAIL","HAJI","HALO","HANG","HARI","HART","HARU","HATI","HAUD","HAUL","HAUR","HAUS","HAYO","HELA","HELM","HENG","HERO","HIAS","HIDU","HIFA","HINA","HOBI","HOKI","HOLI","HORE","HUDA","HUJI","HUMA","HUNI","IBAN","IBNU","IBRA","IBUL","IBUN","IBUS","IDAH","IDAM","IDAP","IDAS","IDEM","IDEP","IFAH","IGAL","IGAU","IGLO","IJAB","IJAS","IJON","IJUK","IKAB","IKAL","IKAN","IKAT","IKON","IKUH","IKUT","ILAH","ILAK","ILAR","ILAS","ILAT","ILER","ILES","ILMU","IMAK","IMAN","IMLA","IMUN","INAP","INAS","INCA","INCU","INDU","INFO","INGA","IOTA","IPAR","IPON","IPUH","IPUK","IQRA","IRAM","IRAS","IRUS","ISAK","ISAP","ISRA","ISYA","ISYU","ITEM","IWAD","IZAH","JADI","JAGO","JAHE","JAIL","JAIS","JAIZ","JALI","JALU","JAMU","JANI","JAPU","JARI","JARO","JATI","JAUH","JAWI","JEDA","JELA","JELI","JELU","JEMU","JENG","JENU","JEPA","JERA","JERI","JERO","JIKA","JILA","JITU","JIWA","JOKI","JOLI","JORI","JOTA","JUAK","JUAL","JUAN","JUAR","JUDI","JUDO","JUEK","JUGA","JUHI","JUIH","JULI","JULO","JUNG","JUNI","JURA","JURI","JUTA","JUTE","KACI","KACO","KACU","KADE","KADI","KADO","KAFE","KAFI","KAIL","KAIN","KAIS","KAIT","KAJI","KALI","KALO","KAMI","KAMP","KAMU","KANE","KANG","KANO","KANS","KAON","KAOS","KAPI","KAPU","KARI","KARU","KASI","KATE","KATI","KAUL","KAUM","KAUS","KAUT","KAWI","KAYU","KEBO","KECI","KECU","KEDI","KEJI","KEJU","KELI","KELP","KELU","KEMI","KEMU","KENA","KENG","KERA","KERI","KERO","KERS","KESI","KETA","KETI","KETU","KHAS","KHAT","KIAH","KIAL","KIAM","KIAN","KIAP","KIAR","KIAS","KIAT","KICU","KILA","KILN","KILO","KIMA","KIMO","KINA","KIOS","KIPA","KIPU","KIRA","KIRU","KISA","KITA","KITS","KLAN","KLEM","KLEN","KLEP","KLIN","KLIP","KLIR","KLON","KLOP","KLOR","KLUB","KNOP","KNOT","KOAR","KOCI","KODA","KODE","KODI","KOIL","KOIN","KOIT","KOJA","KOLA","KOLI","KOLT","KOMA","KOPI","KOTA","KRAI","KRAM","KREM","KRIM","KRIO","KROL","KROM","KUAH","KUAI","KUAP","KUAR","KUAS","KUAT","KUDA","KUDI","KUIH","KUIL","KUIN","KUIR","KUIS","KUIT","KULI","KULT","KUNG","KUNO","KUPA","KUPE","KUPI","KURA","KURS","KUSA","KUTA","KUTI","KUYA","LABU","LACI","LADI","LADU","LAGI","LAGO","LAGU","LAIF","LAIK","LAIN","LAIS","LAJU","LAKI","LAKU","LANG","LAOS","LAPO","LARI","LARS","LARU","LASI","LASO","LAUH","LAUK","LAUN","LAUR","LAUT","LAWE","LAWI","LAYU","LEAK","LECI","LECO","LEFA","LEGA","LEGI","LEGO","LEGU","LEJA","LEKA","LEKU","LEMA","LEMO","LENA","LENG","LENS","LEOT","LEPA","LEPU","LESA","LESI","LESU","LETA","LEWA","LEWU","LIAN","LIAR","LIAS","LIAT","LIAU","LIFO","LIFT","LIGA","LIKU","LIMA","LING","LINU","LIPU","LIRA","LISU","LIUK","LIUR","LIUT","LIWA","LOAK","LOBA","LOBI","LOHA","LOJI","LOKA","LOKI","LONG","LORI","LOSE","LOTA","LOYA","LUAH","LUAK","LUAP","LUAR","LUAS","LUAT","LUES","LUIH","LUIK","LUKA","LUKS","LUNG","LUPA","LUPI","LUSA","LUTI","MACE","MADI","MADO","MADU","MAGI","MAIN","MAIR","MAJU","MAKI","MALE","MALT","MALU","MANG","MANI","MARE","MARI","MARK","MARO","MARS","MARU","MATE","MATI","MATU","MAUT","MAUZ","MAZI","MBAH","MBAK","MBOK","MEDU","MEGA","MEJA","MEKO","MENA","MENI","MENS","MENU","MERI","MERU","MESA","META","MIAK","MIAP","MIJU","MIKA","MILU","MINA","MIOP","MISA","MITE","MODE","MOGA","MOKA","MOKE","MOLA","MOLE","MONG","MORF","MORI","MOSI","MOTA","MUAI","MUAK","MUAL","MUAS","MUAT","MUDA","MUIH","MUKA","MULA","MUNG","MUNO","MUON","MURA","MURI","MUTE","NABI","NABU","NADI","NAFI","NAHI","NAHU","NAIB","NAIF","NAIK","NAIM","NALI","NASI","NAZI","NEKA","NEKO","NESA","NETO","NIAT","NICA","NILA","NIRA","NODA","NOEM","NOJA","NOTA","NOVA","NURI","NUSA","NYAI","NYAK","NYIT","NYUT","OASE","OBAR","OBAT","OCEH","OGAH","OGAM","OGEL","OJEG","OJEK","OKER","OLAH","OLAK","OLEH","OLEK","OLES","OLET","OLIA","OMEL","OMPU","ONAK","ONAR","ONCE","OPAK","OPAL","OPAS","OPEN","OPER","OPSI","OPUS","ORAK","ORAL","ORDE","ORDI","OREN","ORET","OTAK","OTAR","OTEK","OVAL","OVEN","OVER","OVUM","OYAK","OYEK","PACE","PACU","PADI","PADU","PAES","PAGI","PAGU","PAIL","PAIR","PAIS","PAKU","PALE","PALI","PALU","PARE","PARI","PARO","PARS","PARU","PASI","PASU","PATI","PAUH","PAUK","PAUL","PAUN","PAUS","PAUT","PAYU","PECI","PEDA","PEGO","PEKA","PEKU","PELO","PELS","PENA","PENI","PEOK","PEOT","PERA","PERI","PERS","PESA","PESI","PETA","PETI","PIAH","PIAK","PIAL","PIAS","PIAT","PICA","PICO","PICU","PIKA","PIKE","PILU","PION","PITA","PIUH","PIUT","PIZA","PLAN","PLOI","PLOT","PLUG","PLUS","POAL","POCI","POIN","POLA","POMA","PONI","PONS","PORA","PORI","POSE","PRAH","PREI","PRES","PRIA","PRIS","PRIT","PROF","PUAH","PUAK","PUAL","PUAN","PUAS","PUDI","PUIH","PUJA","PUJI","PUKI","PULA","PUMA","PUNG","PUNK","PURA","PURE","PURI","PUSA","PUSO","PUTI","QARI","RABI","RABU","RADI","RADU","RAFE","RAFI","RAGI","RAGU","RAHU","RAIB","RAIH","RAIS","RAMI","RAMU","RANG","RANI","RAPI","RAPU","RASE","RASI","RATU","RAUM","RAUN","RAUP","RAUT","RAWI","RAYU","REAK","REAL","REBA","REBU","RECA","REDA","REGI","REGU","REJA","REKA","RELA","RELI","REMA","REMI","RENA","RENG","REOG","REOL","REOT","RESA","RESI","RESU","RETA","RIAH","RIAK","RIAL","RIAM","RIAN","RIAP","RIAS","RIBA","RIBU","RICA","RIDA","RIDU","RIMA","RIME","RING","RIOL","RISA","RIUH","RIUK","RODA","RODI","ROGA","ROKI","ROMA","RONA","RONG","ROTI","ROWA","RUAH","RUAI","RUAK","RUAM","RUAP","RUAS","RUAT","RUDI","RUGI","RUIT","RUJI","RUKO","RUMI","RUOK","RUPA","RUSA","RUTE","SABI","SABO","SADO","SADU","SAFI","SAGU","SAHI","SAIF","SAIR","SAJI","SAKE","SAKI","SAKU","SALE","SALI","SAMI","SANG","SANI","SANO","SAPI","SAPU","SARI","SARU","SATE","SATO","SATU","SAUH","SAUK","SAUM","SAUR","SAUT","SAWI","SAWO","SAYU","SEBA","SEBU","SEDU","SEGA","SEGI","SEIA","SEIN","SEKA","SEKH","SEKO","SELA","SELO","SEMA","SEMI","SEMU","SENA","SENG","SENI","SENU","SEOK","SEPI","SERA","SERI","SERO","SERU","SETA","SETI","SETU","SEWA","SEWU","SIAH","SIAK","SIAL","SIAM","SIAN","SIAP","SIAR","SIAT","SIAU","SICE","SIDA","SIKA","SIKU","SILA","SILO","SILT","SILU","SING","SINU","SIPU","SIRA","SIRU","SITA","SITU","SIUH","SIUK","SIUL","SIUR","SIUT","SKIP","SKOP","SKOR","SLAH","SLIP","SLOF","SNOB","SOAK","SOAL","SOBA","SODA","SOFA","SOGA","SOJA","SOKA","SOMA","SOPI","SORE","SORI","SOUN","SPAN","SPIL","SREG","STAF","STAN","STEK","STEN","STEP","STIK","STOK","STOL","STOP","SUAH","SUAI","SUAK","SUAM","SUAP","SUAR","SUAT","SUCI","SUDA","SUDI","SUFI","SUGI","SUIT","SUJI","SUKA","SUKE","SUKI","SULA","SULI","SUMO","SUNI","SUPA","SURA","SURI","SWAK","SYAH","SYAK","SYAL","SYAM","SYAR","SYIN","SYOK","SYUR","TABE","TABO","TABU","TACI","TADI","TAGO","TAHI","TAHU","TAIB","TAIS","TAJI","TAJU","TAKI","TALI","TALK","TALU","TAMU","TANG","TANI","TANK","TAPI","TARI","TAUL","TAUN","TAUR","TEAN","TEBU","TEGA","TEJA","TEJI","TEKA","TEKI","TEKO","TEKS","TELA","TEMA","TEMU","TENG","TEPA","TEPI","TEPO","TEPU","TERA","TERI","TERM","TEZI","TIAM","TIAN","TIAP","TIBA","TIFA","TIGA","TIKA","TIKE","TING","TIPE","TIPU","TIRU","TISU","TIUP","TOAS","TOGA","TOGE","TOKE","TONA","TONG","TOPI","TOYA","TRAP","TRAS","TREK","TREM","TREN","TRES","TRIK","TRIL","TRIM","TRIO","TRIP","TROI","TROS","TRUF","TRUK","TSAR","TUAH","TUAI","TUAK","TUAL","TUAM","TUAN","TUAP","TUAR","TUAS","TUBA","TUBE","TUBI","TUFA","TUGI","TUIL","TUJI","TULA","TULE","TUMA","TUNA","TUNG","TURA","TURI","UANG","UBAH","UBAN","UBAR","UBAT","UBEK","UBEL","UBER","UBET","UBIN","UBIT","UCAP","UCEK","UCIS","UDAK","UDAM","UDAP","UDAR","UDEK","UDET","UDIK","UDIM","UFTI","UGEM","UGER","UJAR","UKAS","UKIR","ULAH","ULAK","ULAM","ULAN","ULAR","ULAS","ULAT","ULEK","ULEM","ULEN","ULES","ULET","ULIK","ULIN","ULIR","ULIT","ULNA","ULOS","UMAK","UMAN","UMAT","UMBI","UMBO","UNAM","UNDA","UNDI","UNIK","UNIT","UNTA","UNTI","UPAH","UPAK","UPAM","UPAN","UPAR","UPAS","UPET","UPIH","UPIK","UPIL","URAH","URAI","URAK","URAP","URAS","URAT","UREA","URIK","URIP","URIS","URIT","URNA","USAH","USAI","USAK","USAM","USAP","USAR","USAT","USIA","USIK","USIL","USIR","UTAS","UTIH","UTIK","UWAR","VENA","VETO","VIDE","VILA","VIOL","VISA","VLEK","VOAL","VOLI","VOLT","VRAH","WADI","WAGE","WAGU","WAID","WALI","WALS","WANG","WANI","WARI","WARU","WASI","WATU","WEDA","WESI","WIKU","WING","WIRA","WIRU","WISA","WONG","WOSI","YAIS","YANG","YARD","YAUM""YOGA","YOGI","YOLK","YUDA","YUDO","YUPA","YURA","YUTE","ZAIM","ZAIR","ZEBU","ZENI","ZERO","ZETA","ZINA","ZINK","ZION","ZONA","ZONE"
};// dont forget to add the different Word for the different board type
const char keys[COLS][ROWS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
  {'Q', 'R', 'S', 'T'},
  {'U', 'V', 'W', 'X'},
  {'n', 'Y', 'Z', 'n'},
};


#elif BOARDTYPE == 3
const char* indonesianWords[] = {"ABDI","ABEN","ABID","ABOI","ABON","ACIK","ADEH","ADEM","ADIB","ADIK","ADIL","ADON","AFEK","AGEN","AGIH","AGIL","AGIO","AGON","AHLI","AJEK","AKEO","AKIL","AKLI","ALEM","ALIF","ALIH","ALIK","ALIM","ALIN","ALIP","ALOI","ALON","AMBI","AMEN","AMIL","AMIN","AMKO","AMOI","AMPE","AMPO","ANEH","ANIL","ANOM","APEK","APEL","APIK","APOK","BACO","BADE","BADI","BAGI","BAID","BAIK","BAIN","BAJI","BAKH","BAKI","BAKO","BANG","BANI","BANK","BEDA","BEDO","BEGA","BEGO","BEHA","BEKA","BELA","BELI","BELO","BEMO","BENA","BENI","BEOL","BIAH","BIAK","BIDA","BIDO","BIJA","BILA","BINA","BLEK","BLOG","BLOK","BODI","BOGA","BOGI","BOLA","BONG","CABE","CABO","CAEM","CAHI","CAKI","CAKO","CALO","CANG","CAPE","CEKI","CELA","CELI","CEMA","CENA","CENG","CEPO","CIAK","CIAP","CIKA","CINA","CING","COAK","COBA","COLI","DAGE","DAGI","DAHI","DAIF","DAIM","DAKI","DAME","DAMI","DANG","DEMI","DEMO","DENA","DEPA","DEPO","DIAM","DIAN","DILA","DINA","DOBI","DONG","DONI","EBAM","EBAN","EDAN","EGAH","EGOL","EJAN","EKAD","EKON","ELAK","ELAN","ELOK","ELON","EMOH","EMOL","EMPO","ENAK","ENAM","ENAP","ENOM","EPAK","EPIK","EPOK","FAIL","FANI","FEKO","FILM","FILO","FLOP","FOLI","GACO","GADO","GAEK","GAIB","GAIL","GAIN","GAJI","GALI","GANI","GAOK","GEDI","GELA","GELI","GELO","GEMA","GEMI","GENA","GIAL","GIAM","GILA","GOAK","GOBA","GODA","GOEL","GOLF","GONI","HAID","HAIK","HAIL","HAJI","HALO","HANG","HELA","HELM","HENG","HIFA","HINA","HOBI","HOKI","HOLI","IBAN","IDAH","IDAM","IDAP","IDEM","IDEP","IFAH","IGAL","IGLO","IJAB","IJON","IKAB","IKAL","IKAN","IKON","ILAH","ILAK","IMAK","IMAN","IMLA","INAP","INCA","INFO","INGA","IPON","JADI","JAGO","JAHE","JAIL","JALI","JANI","JEDA","JELA","JELI","JENG","JEPA","JIKA","JILA","JOKI","JOLI","KACI","KACO","KADE","KADI","KADO","KAFE","KAFI","KAIL","KAIN","KAJI","KALI","KALO","KAMI","KAMP","KANE","KANG","KANO","KAON","KAPI","KEBO","KECI","KEDI","KEJI","KELI","KELP","KEMI","KENA","KENG","KIAH","KIAL","KIAM","KIAN","KIAP","KILA","KILN","KILO","KIMA","KIMO","KINA","KIPA","KLAN","KLEM","KLEN","KLEP","KLIN","KLIP","KLON","KLOP","KNOP","KOCI","KODA","KODE","KODI","KOIL","KOIN","KOJA","KOLA","KOLI","KOMA","KOPI","LACI","LADI","LAGI","LAGO","LAIF","LAIK","LAIN","LAKI","LANG","LAPO","LEAK","LECI","LECO","LEFA","LEGA","LEGI","LEGO","LEJA","LEKA","LEMA","LEMO","LENA","LENG","LEPA","LIAN","LIFO","LIGA","LIMA","LING","LOAK","LOBA","LOBI","LOHA","LOJI","LOKA","LOKI","LONG","MACE","MADI","MADO","MAGI","MAIN","MAKI","MALE","MANG","MANI","MBAH","MBAK","MBOK","MEGA","MEJA","MEKO","MENA","MENI","MIAK","MIAP","MIKA","MINA","MIOP","MODE","MOGA","MOKA","MOKE","MOLA","MOLE","MONG","NABI","NADI","NAFI","NAHI","NAIB","NAIF","NAIK","NAIM","NALI","NEKA","NEKO","NICA","NILA","NODA","NOEM","NOJA","OCEH","OGAH","OGAM","OGEL","OJEG","OJEK","OLAH","OLAK","OLEH","OLEK","OLIA","OMEL","ONAK","ONCE","OPAK","OPAL","OPEN","PACE","PADI","PAGI","PAIL","PALE","PALI","PECI","PEDA","PEGO","PEKA","PELO","PENA","PENI","PEOK","PIAH","PIAK","PIAL","PICA","PICO","PIKA","PIKE","PION","PLAN","PLOI","POAL","POCI","POIN","POLA","POMA","PONI"
  };
// char* keys[COLS][ROWS] =  //probably error with the char*
// {
//   {"PERSEGI", "PERSEGI PANJANG", "LINGKARAN", "TRAPESIUM"},
//   {"SEGITIGA", "SEGI ENAM", "SEGITIGA SAMAKAKI", "SEGI LIMA"},
//   {"JAJAR GENJANG", "LAYANG LAYANG", "1/2 LINGKARAN", "3/4 LINGKARAN"},
//   {"SEGI BANYAK", "BINTANG", "SEGITIGA SEMBARANG", "SEGI DELAPAN"},
//   {"n", "n", "n", "n"},
//   {"n", "n", "n", "n"},
//   {"n", "n", "n", "n"},
// };
const char keys[COLS][ROWS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
};
#endif



// char keys[ROWS][COLS] = {
//   {'A', 'B', 'C', 'D'},
//   {'E', 'F', 'G', 'H'},
//   {'I', 'J', 'K', 'L'},
//   {'M', 'N', 'O', 'P'},
// };


int state[ROWS*COLS] = {0}; // Initialize all to 0

///ESP32 S2
int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 ,10, 11};
byte colPins[COLS] = {6, 2, 1, 9}; //connect to the column pinouts of the kpd
byte rowPins[ROWS] = {11, 7, 5, 3}; //connect to the row pinouts of the kpd
#define MODE_BUTTON_PIN 10
#define RESET_BUTTON_PIN 13
#define START_PAUSE_BUTTON_PIN 14



//ESP32 S3
//#define MODE_BUTTON_PIN 1
//#define RESET_BUTTON_PIN 2
//#define START_PAUSE_BUTTON_PIN 42
//byte colPins[COLS] = {17, 16, 15, 7};
//byte rowPins[ROWS] = {46, 3, 8, 18};



Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Function to get the index of the key in the keys array
int getKeyIndex(char key){
  int res;
  for(int r = 0; r < ROWS; r++){
    for(int c = 0; c < COLS; c++){
      if(keys[c][r] == key) {
        res = c * COLS + r;
        Serial.printf("Index %c Found at row %d col %d %d\n", key,r, c , res);
        return res; // Calculate the index
      }
    }
  }
  return -1; // Return -1 if the key is not found
}

void setLED(int index, int r, int g, int b) {
    if (index >= 0 && index < NUM_LEDS) {
        Serial.printf("index %d is turned on with rgb %d %d %d \n", index, r, g, b);
        // Define the new mapping for the snake pattern
        // int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 , 10, 11, 15, 14, 13, 12};
        int mappedIndex = snakeIndices[index];
        pixel.setPixelColor(mappedIndex, pixel.Color(r, g, b));
        pixel.show();
    }
}

void flashLED(int r, int g, int b){
          for (int i = 0; i < NUM_LEDS; i++) {
          setLED(i, r, g, b);
          delay(100);
        }
        delay(SHORTDELAY);
        for(int i = NUM_LEDS; i >=0; i--){
          setLED(i, 0, 0 , 0);{
            delay(100);
    }
  }
}

#if BOARDTYPE == 3
char* getText(char input){
  char* f;
  switch(input){
    case 'A': f = "PERSEGI"; break;
    case 'B': f = "PERSEGI PANJANG"; break;
    case 'C': f = "LINGKARAN"; break;
    case 'D': f = "TRAPESIUM"; break;
    case 'E': f = "SEGITIGA"; break;
    case 'F': f = "SEGI ENAM"; break;
    case 'G': f = "SEGITIGA SAMA KAKI"; break;
    case 'H': f = "SEGI LIMA"; break;
    case 'I': f = "JAJAR GENJANG"; break;
    case 'J': f = "LAYANG LAYANG"; break;
    case 'K': f = "1/2 LINGKARAN"; break;
    case 'L': f = "3/4 LINGKARAN"; break;
    case 'M': f = "SEGI BANYAK"; break;
    case 'N': f = "BINTANG"; break;
    case 'O': f = "SEGITIGA SEMBARANG"; break;
    case 'P': f = "SEGI DELAPAN"; break;
    defaulf : f = "";break;
  }
  Serial.printf("input %c is equal to %c \n", input, f);
  return f;
}
#endif
void upScreenLED(char input, char target, bool isCorrect){
  String text = isCorrect ? "Correct," : "Wrong,";
  char sign = isCorrect ? '^' : '*';
  Serial.printf("%s your input is %c\n",text, input);
  #if BOARDTYPE == 3
  char* p = getText(input);
  P.displayText(p, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
  while (!P.displayAnimate()) { /* do animation empty loop */ };
  P.print(sign);
  // sprintf(t, "%c %c", p, sign);
  #else
  sprintf(t, "%c %c", input, sign);
    P.displayText(t, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);

  #endif
  // P.print(t);
    while (!P.displayAnimate()) { /* do animation empty loop */ };
  Serial.println(t);
  if(isCorrect){
  setLED(getKeyIndex(input), 0, 45, 0);
  Serial.printf("%c key input is correct \n", input);
  } // Green LED for correct input
  else {
    Serial.printf("%c key input is wrong \n", input);
    setLED(getKeyIndex(input), 45, 0, 0);
    setLED(getKeyIndex(target), 0, 45, 0);
    }
  delay(SHORTDELAY);
  flashLED( 0, 0, 0);
}
#if BOARDTYPE != 3
void simonSaysGame(char input) {
  Serial.printf("game triggered with %c as input\n", input);
  if (!gameStarted) {
    // Initialize the game
    Serial.println("Simon Says: Watch the sequence and repeat it.");
    P.print("Amati, Tirukan");
    delay(SHORTDELAY);
    P.print("");

    flashLED(0,0,0); //turn all led off to make sure clean start
    // Generate a unique random sequence of characters from Indonesian words
    int randomIndex = random(0, 100);
    Serial.printf("random number is %d \n", randomIndex);
    for (int i = 0; i < 4; i++) {
      sequence[i] = indonesianWords[randomIndex][i];
      Serial.printf("Generated character %c for position %d \n", sequence[i], i);
      // Immediately display the sequence character on the LED
      int ledIndex = getKeyIndex(sequence[i]);
      // P.print();
      char* p = getText(sequence[i]);
      P.displayText(p, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
      while (!P.displayAnimate()) { /* do animation empty loop */ };
      if (ledIndex != -1) {
        setLED(ledIndex, 0, 0, 45); // Blue LED
        delay(SHORTDELAY); // Display each character for half a second
        setLED(ledIndex, 0, 0, 0); // Turn off the LED
        delay(SHORTDELAY); // Short pause between characters
      }
    }
    flashLED(0, 45, 0); // Flash green to indicate the game has started
    gameStarted = true;
    inputIndex = 0;
    lastTime = millis();
    Serial.println("Game Has Started");
    P.print("");
  }

  if (input != NO_KEY) { // Only process if a valid key is pressed
    setLED(getKeyIndex(sequence[inputIndex]), 0, 0, 50);
    Serial.printf("game is triggered (2) input is %c\n", input);
    changed = true;
    if (input == sequence[inputIndex]) {
      // Correct input
      Serial.printf("input %c is correct, index led is %d \n", input, inputIndex);
      upScreenLED(input,sequence[inputIndex], true);
      inputIndex++;
      setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);

      if (inputIndex >= 4) {
        // Completed the current level
        currentLevel++;
        inputIndex = 0;
        Serial.println("Congratulations! You completed the Simon Says game!");
        P.displayText("Selamat:D", PA_RIGHT, 150, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        for (int i = 0; i < NUM_LEDS; i++) {
          setLED(i, random(0, 45), random(0, 45), random(0,45)); // Celebrate with yellow LED flash
          delay(100);
          // Reset the game
        }
        gameStarted = false;
        simonSaysGame(NO_KEY); // Call again to show the sequence for the next level

      }
    } else {
      // Incorrect input
      setLED(getKeyIndex(input), 55, 0, 0);
      upScreenLED(input,sequence[inputIndex], false);
      wrongCount+=1;
      Serial.printf("%c input is wrong, correct input is %c \n", input, sequence[inputIndex]);
      if(wrongCount >= 3){  
        // Reset the game
        currentLevel = 1;
        gameStarted = false;
        for (int i = 0; i < NUM_LEDS; i++) setLED(i, 45, 0, 0);
          simonSaysGame(NO_KEY); // Call again to show the sequence for the next level

        }
      // setLED(getKeyIndex(sequence[inputIndex++]), 55, 16, 90);


    }
    P.print("");
  }
  else{
    Serial.println("game triggered with no input");
    setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);
  
}}
#endif
// void startCheck(){
//   Serial.println("Test check");
//   P.print("Test Started");
//   for(int i =  0; i < 16; i ++){
//     setLED(i, 0, 0, 45);
//     delay
//   }
// }

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  randomSeed(analogRead(11));
  randomAlphabet = 'A' + random(16); // Set initial random alphabet
  P.begin();
  P.setInvert(false);
  // P.setFont(myFont);
  for(int i = 0; i <MAX_DEVICES; i++){
    P.setZoneEffect(i, true, PA_FLIP_UD);
    P.setZoneEffect(i, true, PA_FLIP_LR);
    }

  P.setTextAlignment(PA_CENTER);
  P.setCharSpacing(1);
  P.setIntensity(1);
  // P.print("TES");
  P.displayText("FUNTOYA", PA_RIGHT, 150, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while(!P.displayAnimate()){}
  // delay(SHORTDELAY);
  P.print("");
  #if BOARDTYPE != 3
  simonSaysGame(NO_KEY);
  #endif
}

// bool changed = 0;
void keypadRoutine() {
  if (kpd.getKeys()) {
    for (int i = 0; i < ROWS * COLS; i++) {
      if (kpd.key[i].stateChanged) {
        Serial.printf("Key at index %c is changing\n", keys[i]);
        position = getKeyIndex(kpd.key[i].kchar); // Get the index of the key
        if (position != -1) {
          if (kpd.key[i].kstate == 1) { // Key is pressed
            state[position] = 1; // Update state to indicate the key is pressed
            setLED(getKeyIndex(kpd.key[i].kchar), 0, 50, 0); 
            Serial.printf("Button %c at index %d is ON\n", kpd.key[i].kchar, position);
            P.displayText(getText(kpd.key[i].kchar), PA_LEFT, 150, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
            while(!P.displayAnimate()){}
          } else if (kpd.key[i].kstate == 3) { // Key is released
            state[position] = 0; // Update state to indicate the key is released
            Serial.printf("Button %c at index %d is OFF\n", kpd.key[i].kchar, position);
          }
        }
      }
    }
  }
}


void loop() {
  for (int i = 0; i < ROWS * COLS; i++) {
    if (state[i]==1) {
      setLED(i, 0, 50, 0); // Turn on the LED if state is 1
      // state[i] = 0;
    } else {
      setLED(i, 0, 0, 0); // Turn off the LED if state is 0
    }
  }
  keypadRoutine();
}