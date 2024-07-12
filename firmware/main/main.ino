#include <Arduino.h>


#define BOARDTYPE 2 // 1 for number, 2 for alphabet, 3 for shape puzzle
bool REV = 1; // rev 0 for  the non inverted led matrix, rev 1 for the  inverted one , will  alter the led setup below
//pin 10 is used to alter the value, HIGH for 1
bool debug = false;//////////////DEBUG FOR DISABLE THE GAME, ONLY  CHECKING THE BASIC FUNCTION OF THE BOARD
//pin  12 is used to alter the value on boot, HIGH for true
#define ROWS  4 //four rows
#define  COLS  7 //four columnsv



//if the board type is not huruf, that means the cols and rows would be the same, that means these settings didnt change(like the last version)
//there's an additional Word variable that store the String that should be printed on the lcd, other than board 2, the value is different (nuber and shape)\
//thus we made it different, and make the lcd print the correct character accordingly
//but we still need the keys variable to check the generated Word and the inputted Word, int this case we made 1 and 3 the same, doesnt care about the symbol on the angka mode
// and also the indonesianWords variable need to be different, and need to be placed in this line to save space

//////EXPERIMENTAL
//////why dont we just make the rows and column to be 4*7 and the snake indices to be default like the alphabet instead of buzzing around trying to make it different?, so thats what im going to do, so 

//////////////////////another experiment
//why didnt i just make the keys different for the different board? like board 1 keys would contain 123 etc
int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 ,10, 11,15, 14,  13, 12, 16, 17, 18, 19, 23, 22, 21, 20, 24, 25};
byte colPins[COLS] = {6, 2, 1, 9, 38 ,39, 40}; //connect to the column pinouts of the kpd





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
char* keys[COLS][ROWS] =  //probably error with the char*
{
  {"PERSEGI", "PERSEGI PANJANG", "LINGKARAN", "TRAPESIUM"},
  {"SEGITIGA", "SEGI ENAM", "SEGITIGA SAMAKAKI", "SEGI LIMA"},
  {"JAJAR GENJANG", "LAYANG LAYANG", "1/2 LINGKARAN", "3/4 LINGKARAN"},
  {"SEGI BANYAK", "BINTANG", "SEGITIGA SEMBARANG", "SEGI DELAPAN"},
  {"n", "n", "n", "n"},
  {"n", "n", "n", "n"},
  {"n", "n", "n", "n"},
};
#endif


#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DEBUG_PIN 12
#define REV_PIN 10
#define SHORTDELAY 500
#define LONGDELAY 1000
#define MAX_WORDS  100
#define WORD_LENGTH 4
#define CLK_PIN   36
#define DATA_PIN  35
#define CS_PIN    34
#define MAX_KEY COLS * ROWS
#define NUM_LEDS COLS * ROWS
//MOSI: 35
//MISO: 37
//SCK: 36
//SS: 34




byte rowPins[ROWS] = {11, 7, 5, 3}; //connect to the row pinouts of the kpd
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const byte LED_PIN = 4;
int position, winCount;
unsigned long lastMillis, currentMillis;
char pressedKey;
int mode, score;
char t[100];char lastKey;

Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

/////////////////////variables for the game
  static char sequence[6]; // Array to hold the sequence
  static int currentLevel = 1; // Current level (starts at 1)
  static int inputIndex = 0; // Track the current input position
  bool gameStarted = false;
  static unsigned long lastTime = 0; // To manage non-blocking delays
  static int sequenceIndex = 0; // Index for showing the sequence
  static int wrongCount = 0;
  int state[ROWS*COLS] = {0}; // Initialize all to 0
  int randomIndex;
  

/////


int getKeyIndex(char key){// Function to get led index of the key in the keys array
  for(int r = 0; r < ROWS; r++){
    for(int c = 0; c < COLS; c++){
      Serial.println(keys[c][r]);
      if(keys[c][r] == char(key)) {
        return r * COLS + c; // Calculate the index
      }
    }
  }
  return -1; // Return -1 if the key is not found
}

void setLED(int index, int r, int g, int b) {
    if (index >= 0 && index < NUM_LEDS) {
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
#if BOARDTYPE == 1
void generateRandomNumberSequence(char sequence[], int length,char availableChars[], int availableLength) {
    // Create a copy of the available characters array
    char tempArray[availableLength];
    memcpy(tempArray, availableChars, availableLength);

    // Shuffle the tempArray to randomize the characters
    for (int i = 0; i < availableLength; i++) {
        int randomIndex = random(i, availableLength);
        char temp = tempArray[i];
        tempArray[i] = tempArray[randomIndex];
        tempArray[randomIndex] = temp;
    }

    // Select the first 'length' characters from the shuffled array
    for (int i = 0; i < length; i++) {
        sequence[i] = tempArray[i];
    }
}
#endif

void upScreenLED(char input, char target, bool isCorrect){
  P.print("");
  String text = isCorrect ? "Correct," : "Wrong,";
  char sign = isCorrect ? '^' : '*';
  Serial.printf("%s your input is %c\n",text, input);
  // P.setTextEffect(PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
  sprintf(t, "%s %c",input,  sign);
  P.displayText(t, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
  
  while (!P.displayAnimate()) { /* do animation empty loop */ };


  // P.print(t);
  if(isCorrect){setLED(getKeyIndex(input), 0, 45, 0);
  }
  else {
    setLED(getKeyIndex(input), 45, 0, 0);
    setLED(getKeyIndex(target), 0, 45, 0);
    }
}
void simpleGame(char input) {
  static bool changed = true;
  if (!gameStarted) {
    // Initialize the game
    Serial.println("Simon Says: Watch the sequence and repeat it.");
    P.displayText("Amati,Tirukan", PA_LEFT, 100, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
    while (!P.displayAnimate()) { /* do animation empty loop */ };
    // delay(SHORTDELAY);
    P.print("");
    flashLED(0,0,0); //turn all led off to make sure clean start
    // Generate a unique random sequence of characters from Indonesian words
    #if BOARDTYPE == 1
    int randomIndex;
    char tempArray[4];
    memcpy(tempArray, indonesianWords, 4);
    // Shuffle the tempArray to randomize the characters
    for (int i = 0; i < 4; i++) {
        int randomIndex = random(i, 4);
        char temp = tempArray[i];
        tempArray[i] = tempArray[randomIndex];
        tempArray[randomIndex] = temp;
    }
    // Select the first 'length' characters from the shuffled array
    for (int i = 0; i < 4; i++) {
        sequence[i] = tempArray[i];
    }
    
    #elif BOARDTYPE != 1
    randomIndex = random(0, MAX_WORDS);
    Serial.println(randomIndex);
    #endif

    for (int i = 0; i <  WORD_LENGTH ; i++) { //to generate a random sequence
      #if BOARDTYPE != 1
      sequence[i] = indonesianWords[randomIndex][i];
      #endif

      Serial.printf("Generated character %c for position %d\n", sequence[i], i);
      // Immediately display the sequence character on the LED
      int ledIndex = getKeyIndex(sequence[i]);
      #if BOARDTYPE != 3
      P.print(String(sequence));
      #else
        P.displayText(sequence, PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
      #endif
      if (ledIndex != -1) {
        setLED(ledIndex, 0, 0, 45); // Blue LED
        delay(SHORTDELAY); // Display each character for half a second
        setLED(ledIndex, 0, 0, 0); // Turn off the LED
        delay(SHORTDELAY); // Short pause between characters
      }
      P.print("");
    }
    flashLED(0, 45, 0); // Flash green to indicate the game has started
    gameStarted = true;
    inputIndex = 0;
    lastTime = millis();
    setLED(getKeyIndex(sequence[0]), 50, 50, 50);
    P.print("");
  }

  if (input != NO_KEY) { // Only process if a valid key is pressed
    setLED(getKeyIndex(sequence[inputIndex]), 0, 0, 0);
    sprintf(t, "%c is pressed on the game, target is %c", input, sequence[inputIndex]);
    Serial.println(t);
    changed = true;
/////////////////////////////////////////////////////////////////////////////////////////////////////
    if (input == sequence[inputIndex]) {
      // Correct input
      upScreenLED(input,sequence[inputIndex], true);
      inputIndex++;
      setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);

      if (inputIndex >= 4) {
        // Completed the current level
        currentLevel++;
        inputIndex = 0;
        Serial.println("Congratulations! You completed the Simon Says game!");
        P.print(":D");
        for (int i = 0; i < NUM_LEDS; i++) {
          setLED(i, random(0, 45), random(0, 45), random(0,45)); // Celebrate with yellow LED flash
          delay(200);
          // Reset the game
        }
        gameStarted = false;
        simpleGame(NO_KEY); // Call again to show the sequence for the next level

      }
    } else {
      // Incorrect input
      upScreenLED(input,sequence[inputIndex], false);
      sprintf(t, "%c is wrong, target is %c", input, sequence[inputIndex]);
      wrongCount+=1;
      if(wrongCount >= 10){  
        // Reset the game
        currentLevel = 1;
        gameStarted = false;
        for (int i = 0; i < NUM_LEDS; i++) setLED(i, 45, 0, 0);
          simpleGame(NO_KEY); // Call again to show the sequence for the next level

        }
      setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);

    }
    P.print("");
  }
  else{
    setLED(getKeyIndex(sequence[inputIndex]), 55, 16, 90);
  
}}

void startCheck(){
  Serial.println("Test check");
  P.displayText("TES STARTED", PA_LEFT, 80, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
  while (!P.displayAnimate()) { /* do animation empty loop */ };
  P.print("");
  for(int i =  0; i < MAX_KEY; i ++){
    setLED(i, 0, 0, 45);
    // P.displayText(keys[i], PA_CENTER, 100, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
    // P.print(keys[i]);
    delay(SHORTDELAY);
    P.print("");
  }
  flashLED(0,0,0);
  P.displayText("Tes Selesai", PA_CENTER, 100, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
  while(!P.displayAnimate()){}
  P.print("");

}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(DEBUG_PIN, INPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  debug = !digitalRead(DEBUG_PIN) ? 1 : 0;

  randomSeed(analogRead(11));
  P.begin();
  P.setInvert(false);
  // P.setFont(myFont);

  if(REV)
  for(int i = 0; i <MAX_DEVICES; i++){
    P.setZoneEffect(i, true, PA_FLIP_UD);
    P.setZoneEffect(i, true, PA_FLIP_LR);
    }


  // P.setTextAlignment(PA_CENTER);
  P.setCharSpacing(1);
  P.setIntensity(1);
  // P.print("TES");
  P.displayText("FUNTOYA", PA_LEFT, 100, 1000, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
  while (!P.displayAnimate()) { /* do animation empty loop */ };
  P.print("");
  if(debug) startCheck();
  simpleGame(NO_KEY);
}


void keypadRoutine() {
  if (kpd.getKeys()) {
    bool allPressed = true;

    // Check if all keys are pressed
    for (int i = 0; i < 16; i++) {
      if (kpd.key[i].kstate != PRESSED) {
        allPressed = false;
        break;
      }
    }

    // Determine if we should use PRESSED or RELEASED state based on allPressed
    bool usePressed = !allPressed;

    // Handle key state changes
    for (int i = 0; i < 26; i++) {
      if (kpd.key[i].stateChanged) {
        if ((usePressed && kpd.key[i].kstate == PRESSED) || (!usePressed && kpd.key[i].kstate == RELEASED)) {
          position = getKeyIndex(kpd.key[i].kchar); // Get the index of the key

          if (position != -1) {
            state[position] = !state[position]; // Toggle the state

            if (state[position]) {
              P.print(kpd.key[i].kchar);
              Serial.printf("Button %c at index %d is ON\n", kpd.key[i].kchar, position);
              // simonSaysGame(kpd.key[i].kchar); // Call the Simon Says game logic
              // if(debug) setLED(getKeyIndex(kpd.key[i].kchar), 45, 0, 0);
              // if(!debug) simonSaysGame(kpd.key[i].kchar); // Call the Simon Says game logic
               simpleGame(kpd.key[i].kchar);

            } 
          }
        }else if((usePressed && kpd.key[i].kstate == RELEASED) || (!usePressed && kpd.key[i].kstate == PRESSED)){
              setLED(position, 0, 0, 0); // Turn off the LED
              state[position] = 0;
              P.print("");
              Serial.printf("Button %c at index %d is OFF\n", kpd.key[i].kchar, position);
            }
      }
    }
  }
}

void loop() {
  keypadRoutine();
}
